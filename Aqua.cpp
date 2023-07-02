#define _CRT_SECURE_NO_WARNINGS
#define chance_reproduction_plankton 6
#define age_plankton 14
#define chance_reproduction_fish 4
#define age_fish 35
#define chance_reproduction_pred_fish 3
#define age_pred_fish 45
#define fish_view_radius 6
#define pred_fish_view_radius 12
#define steps_without_food_fish 27
#define steps_without_food_pred_fish 31

#include "Aqua.h"

void generation(part** aquarium, int size_x, int size_y, int number_of_fish, int number_of_predatory_fish, int number_of_plankton) {
	int x = 0, y = 0, a = 0, x1 = 0, x2 = 0;
	for (int i = 0;i < number_of_predatory_fish;++i) {
		if (!(i % 20)) {
			x1 = rand() % size_x;
			x2 = rand() % size_y;
		}
		filling(aquarium, pred_fish, x, y, size_x, size_y, a, x1, x2);
	}
	for (int i = 0;i < number_of_fish;++i) {
		if (!(i % 40)) {
			x1 = rand() % size_x;
			x2 = rand() % size_y;
		}
		filling(aquarium, common_fish, x, y, size_x, size_y, a, x1, x2);
	}
	for (int i = 0;i < number_of_plankton;++i) {
		if (!(i % 80)) {
			x1 = rand() % size_x;
			x2 = rand() % size_y;
		}
		filling(aquarium, plankt, x, y, size_x, size_y, a, x1, x2);
	}
}
void filling(part** aquarium, creatures creature, int x, int y, int size_x, int size_y, int a, int x1, int x2) {
	if (creature == common_fish) {
		x = (x1 + rand() % 26) % size_x;
		y = (x2 + rand() % 12) % size_y;
	}
	else if (creature == plankt) {
		x = (x1 + rand() % 45) % size_x;
		y = (x2 + rand() % 15) % size_y;
	}
	else if (creature == pred_fish) {
		x = (x1 + rand() % 20) % size_x;
		y = (x2 + rand() % 10) % size_y;
	}
	a = rand() % 2 ? 1 : -1;
	while (1) {
		if (!aquarium[x][y].creature) {
			if (creature == pred_fish) {
				create_predatory_fish(path(aquarium, x, y, size_x, size_y, 0, 0, 0, 0));
				break;
			}
			else if (creature == common_fish) {
				create_fish(path(aquarium, x, y, size_x, size_y, 0, 0, 0, 0));
				break;
			}
			else if (creature == plankt) {
				create_plankt(path(aquarium, x, y, size_x, size_y, 0, 0, 0, 0));
				break;
			}
			break;
		}
		y = (size_y + y + a) % size_y;
		if (a == 1) x = (x + !(y % size_y)) % size_x;
		else x = (size_x + x - (y % size_y == size_y - 1)) % size_x;
	}
}
int biocenosis(part*** aquarium, int x, int y, int* fish, int* pr_fish, int* plan, int* step) {
	++*step;
	for (int i = 0;i < x;++i) 
		for (int j = 0;j < y;++j) {
			(*aquarium)[i][j].status = 0;
			if ((*aquarium)[i][j].creature == common_fish)
				(*aquarium)[i][j].f->status_razmn = 0;
			else if ((*aquarium)[i][j].creature == pred_fish)
				(*aquarium)[i][j].p_f->status_razmn = 0;
		}
			
	int fish_n= *fish, pr_fish_n = *pr_fish, plan_n = *plan;

	for (int i = 0;i < x;++i) {
		for (int j = 0;j < y;++j)
			if ((*aquarium)[i][j].creature == pred_fish) processing_pred_fish(*aquarium, i, j, fish, pr_fish, plan, x, y, fish_n, pr_fish_n, plan_n);
	}
	for (int i = 0;i < x;++i) {
		for (int j = 0;j < y;++j)
			if ((*aquarium)[i][j].creature == common_fish) processing_common_fish(*aquarium, i, j, fish, pr_fish, plan, x, y, fish_n, pr_fish_n, plan_n);
	}
	for (int i = 0;i < x;++i) {
		for (int j = 0;j < y;++j)
			if ((*aquarium)[i][j].creature == plankt) processing_plankt(*aquarium, i, j, fish, pr_fish, plan, x, y, fish_n, pr_fish_n, plan_n);
	}

	if (!(*fish) || !(*pr_fish) || !(*plan)) return 1;
	return 0;
}


void processing_pred_fish(part** aquarium, int i, int j, int* fish, int* pr_fish, int* plan, int x, int y, int fish_n, int pr_fish_n, int plan_n) {
	if (aquarium[i][j].status) return;
	++(aquarium[i][j].p_f->age);
	if (aquarium[i][j].p_f->age > age_pred_fish || aquarium[i][j].p_f->steps_without_food >= steps_without_food_pred_fish) {
		--* pr_fish;
		del(&aquarium[i][j]);
		return;
	}
	part* opas_riba = NULL;
	int p1 = 0, kolvo = 0;

	int n = search_s(aquarium, i, j, x, y, pred_fish, 1, &opas_riba, &p1,0), f1 = 0;
	if (n && n <= 2 &&  (!(rand() % chance_reproduction_pred_fish) || pr_fish_n <= 100)) {
		if ((((aquarium[i][j].p_f->gender == male && opas_riba->p_f->gender == female) || (aquarium[i][j].p_f->gender == female && opas_riba->p_f->gender == male)) && aquarium[i][j].p_f->degree_of_satisfaction >= 5 && opas_riba->p_f->degree_of_satisfaction >= 5 && !aquarium[i][j].p_f->status_razmn && !opas_riba->p_f->status_razmn)) {
			for (int q = 1;q < 9;++q)
				if (!path(aquarium, i, j, x, y, 0, 0, q, 1)->creature) {
					create_predatory_fish(path(aquarium, i, j, x, y, 0, 0, q, 1));
					path(aquarium, i, j, x, y, 0, 0, q, 1)->status = 1;
					++* pr_fish;
					opas_riba->p_f->status_razmn = 1;
					aquarium[i][j].p_f->status_razmn = 1;
					break;
				}
		}
	}

	if (aquarium[i][j].p_f->degree_of_satisfaction >= 15 && aquarium[i][j].p_f->steps_without_food<=15 || (fish_n<=100 && rand() % 3)) {
		int k = rand() % 8 + 1, f2 = 0;
		aquarium[i][j].p_f->degree_of_satisfaction -= 2;
		++aquarium[i][j].p_f->steps_without_food;
		if (aquarium[i][j].p_f->degree_of_satisfaction < 0) aquarium[i][j].p_f->degree_of_satisfaction = 0;


		n = search_s(aquarium, i, j, x, y, common_fish, pred_fish_view_radius, &opas_riba, &p1,1);
		if (n) {
			preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &p1, 1);
			k = p1;
		}
		else {
			if (rand() % 10) preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &k, 0);
			else preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &k, 1);
		}
		


		if (!p_f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
			k = fr(k, 1);
			if (!p_f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
				k = fr(k, 0);
				k = fr(k, 0);
				p_f_per(aquarium, i, j, x, y, 0, 0, k, 1);
			}
		}

	}
	else {
		n = search_s(aquarium, i, j, x, y, common_fish, 1, &opas_riba, &p1,1);
		if (n) {
			del(opas_riba);
			--* fish;
			aquarium[i][j].p_f->degree_of_satisfaction += 10;
			aquarium[i][j].p_f->steps_without_food = 0;

			n = search_s(aquarium, i, j, x, y, common_fish, pred_fish_view_radius, &opas_riba, &p1,1);
			int k = rand() % 8 + 1;
			if (n) {
				preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &p1, 1);
				k = p1;
			}
			else {
				if (rand() % 10) preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &k, 0);
				else preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &k, 1);
			}
			


			if (!p_f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
				k = fr(k, 1);
				if (!p_f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
					k = fr(k, 0);
					k = fr(k, 0);
					p_f_per(aquarium, i, j, x, y, 0, 0, k, 1);
				}
			}

		}
		else {
			--aquarium[i][j].p_f->degree_of_satisfaction;
			if (rand() % 2) --aquarium[i][j].p_f->degree_of_satisfaction;
			if (aquarium[i][j].p_f->degree_of_satisfaction < 0) aquarium[i][j].p_f->degree_of_satisfaction = 0;
			++aquarium[i][j].p_f->steps_without_food;

			n = search_s(aquarium, i, j, x, y, common_fish, pred_fish_view_radius, &opas_riba, &p1,1);
			int k = rand() % 8 + 1;

			if (n) {
				preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &p1, 1);
				k = p1;
			}
			else {
				if (rand() % 10) preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &k, 0);
				else preob(&aquarium[i][j].p_f->route1, &aquarium[i][j].p_f->route2, &k, 1);
			}



			if (!p_f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
				k = fr(k, 1);
				if (!p_f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
					k = fr(k, 0);
					k = fr(k, 0);
					p_f_per(aquarium, i, j, x, y, 0, 0, k, 1);
				}
			}
		}
	}
}


void processing_common_fish(part** aquarium, int i, int j, int* fish, int* pr_fish, int* plan, int x, int y, int fish_n, int pr_fish_n, int plan_n) {
	if (aquarium[i][j].status) return;
	++(aquarium[i][j].f->age);
	if (aquarium[i][j].f->age > age_fish || aquarium[i][j].f->steps_without_food >= steps_without_food_fish) {
		--* fish;
		del(&aquarium[i][j]);
		return;
	}
	part* opas_riba = NULL;
	int p1 = 0, kolvo = 0;;
	kolvo = search_s(aquarium, i, j, x, y, pred_fish, fish_view_radius, &opas_riba, &p1,1);

	if (kolvo && (rand()%4)) {
		int k = 9 - p1;
		aquarium[i][j].f->degree_of_satisfaction-=2;
		if (aquarium[i][j].f->degree_of_satisfaction < 0) aquarium[i][j].f->degree_of_satisfaction = 0;



		if (search_s(aquarium, i, j, x, y, plankt, 1, &opas_riba, &p1, 0)) {
			aquarium[i][j].f->steps_without_food = 0;
			aquarium[i][j].f->degree_of_satisfaction += 5;
			del(opas_riba);
			--* plan;
		}
		else ++aquarium[i][j].f->steps_without_food;



		if (!f_per(aquarium, i, j, x, y, 0, 0, k, 1)){
			k = fr(k, 1);
			if (!f_per(aquarium, i, j, x, y, 0, 0, k, 1)){
				k = fr(k, 0);
				k = fr(k, 0);
				f_per(aquarium, i, j, x, y, 0, 0, k, 1);
			}
		}
	}
	else {
		int n = search_s(aquarium, i, j, x, y, common_fish, 1, &opas_riba, &p1,0), f1 = 0;
		if (n && n<=3 && ((rand() % chance_reproduction_fish) || *fish <= 100)) {
			if (((((aquarium[i][j].f->gender == male && opas_riba->f->gender == female) || (aquarium[i][j].f->gender == female && opas_riba->f->gender == male)) && !aquarium[i][j].f->status_razmn && !opas_riba->f->status_razmn)) && (fish_n <= pr_fish_n * 3.5 && pr_fish_n >= 100 ||  pr_fish_n < 100)) {
				for (int q = 1;q < 9;++q)
					if (!path(aquarium, i, j, x, y, 0, 0, q, 1)->creature) {
						create_fish(path(aquarium, i, j, x, y, 0, 0, q, 1));
						path(aquarium, i, j, x, y, 0, 0, q, 1)->status = 1;
						++* fish;
						opas_riba->f->status_razmn = 1;
						aquarium[i][j].f->status_razmn = 1;
						break;
					}
			}
		}
		n = search_s(aquarium, i, j, x, y, plankt, 1, &opas_riba, &p1,1);
		if (n) {
			aquarium[i][j].f->degree_of_satisfaction+=5;
			aquarium[i][j].f->steps_without_food = 0;
			del(opas_riba);
			--* plan;
		}
		else {
			--aquarium[i][j].f->degree_of_satisfaction;
			++aquarium[i][j].f->steps_without_food;
			if (!path(aquarium, i, j, x, y, aquarium[i][j].f->route1, aquarium[i][j].f->route2, 0, 0)) {
				int k = 1;
				preob(&aquarium[i][j].f->route1, &aquarium[i][j].f->route2, &k,0);
				f_per(aquarium, i, j, x, y, 0, 0, k, 1);
			}
			else {
				int k = 0;
				n = search_s(aquarium, i, j, x, y, plankt, fish_view_radius, &opas_riba, &p1, 1);
				if (n) k = p1;
				else {
					if (!(rand() % 10)) k = 1 + rand() % 8;
					else preob(&aquarium[i][j].f->route1, &aquarium[i][j].f->route2, &k, 0);
				}
				if (!f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
					k = fr(k, 1);
					if (!f_per(aquarium, i, j, x, y, 0, 0, k, 1)) {
						k = fr(k, 0);
						k = fr(k, 0);
						f_per(aquarium, i, j, x, y, 0, 0, k, 1);
					}
				}
			}
		}
	}
}


void processing_plankt(part** aquarium,  int i, int j, int* fish, int* pr_fish, int* plan, int x, int y, int fish_n, int pr_fish_n, int plan_n) {
	if (aquarium[i][j].status) return;
	++(aquarium[i][j].plank->age);
	if (aquarium[i][j].plank->age >= age_plankton) {
		--* plan;
		del(&aquarium[i][j]);
		return;
	}
	if ((aquarium[i][j].plank->age <= age_plankton - 2) && ((!(rand() % chance_reproduction_plankton)) || *plan <= 200)) {
		int a = 0;
		preob(&(aquarium[i][j].plank->route1), &(aquarium[i][j].plank->route2), &a, 0);
		for (int q = 0;q < 8;++q) {
			a = (a + 1) % 9;
			if (!a) ++a;
			if (!(path(aquarium, i, j, x, y, 0, 0, a, 1)->creature)) {
				create_plankt(path(aquarium, i, j, x, y, 0, 0, a, 1));
				path(aquarium, i, j, x, y, 0, 0, a, 1)->status = 1;
				++(*plan);
				break;
			}
		}
	}
	if (!(path(aquarium, i, j, x, y, aquarium[i][j].plank->route1, aquarium[i][j].plank->route2, 0, 0)->creature)) {
		int a = aquarium[i][j].plank->route1, b = aquarium[i][j].plank->route2;
		if (!(rand() % 8)) {
			int w = 1 + rand() % 8;
			preob(&(aquarium[i][j].plank->route1), &(aquarium[i][j].plank->route2), &w, 1);
		}
		copy(&aquarium[i][j], path(aquarium, i, j, x, y,a,b, 0, 0));
		path(aquarium, i, j, x, y, a, b, 0, 0)->status = 1;
	}
	else {
		if (!(rand() % 3)) {
			int w = 1 + rand() % 8;
			preob(&(aquarium[i][j].plank->route1), &(aquarium[i][j].plank->route2), &w, 1);
		}
	}
}


int f_per(part** aquarium, int i, int j, int size_x, int size_y, int route1, int route2, int route, int f) {
	if (!path(aquarium, i, j, size_x, size_y, route1, route2, route, f)->creature) {
		preob(&(aquarium[i][j].f->route1), &(aquarium[i][j].f->route2), &route, 1);
		aquarium[i][j].status = 1;
		copy(&aquarium[i][j], path(aquarium, i, j, size_x, size_y, route1, route2, route, f));
		return 1;
	}
	return 0;
}
int p_f_per(part** aquarium, int i, int j, int size_x, int size_y, int route1, int route2, int route, int f) {
	if (!path(aquarium, i, j, size_x, size_y, route1, route2, route, f)->creature) {
		preob(&(aquarium[i][j].p_f->route1), &(aquarium[i][j].p_f->route2), &route, 1);
		aquarium[i][j].status = 1;
		copy(&aquarium[i][j], path(aquarium, i, j, size_x, size_y, route1, route2, route, f));
		return 1;
	}
	return 0;
}

part* path(part** aquarium, int i, int j, int size_x, int size_y, int route1, int route2, int route, int f) {
	if (f) preob(&route1, &route2, &route, 1);
	return &(aquarium[(size_x + i + route1) % size_x][(size_y + j + route2) % size_y]);
}
void preob(int* route1, int* route2, int* route, int f) {
	if (f)
		switch (*route) {
		case 1:
			*route1 = -1;*route2 = -1;
			break;
		case 2:
			*route1 = -1;*route2 = 0;
			break;
		case 3:
			*route1 = -1;*route2 = 1;
			break;
		case 4:
			*route1 = 0;*route2 = -1;
			break;
		case 5:
			*route1 = 0;*route2 = 1;
			break;
		case 6:
			*route1 = 1;*route2 = -1;
			break;
		case 7:
			*route1 = 1;*route2 = 0;
			break;
		case 8:
			*route1 = 1;*route2 = 1;
			break;
		default:
			*route1 = 0;*route2 = 0;
		}
	else 
		switch (*route1) {
		case -1:
			switch (*route2) {
			case -1:
				*route = 1;
				break;
			case 0:
				*route = 2;
				break;
			case 1:
				*route = 3;
				break;
			default:
				*route = 0;
			}
			break;
		case 0:
			switch (*route2) {
			case -1:
				*route = 4;
				break;
			case 1:
				*route = 5;
				break;
			default:
				*route = 0;
			}
			break;
		case 1:
			switch (*route2) {
			case -1:
				*route = 6;
				break;
			case 0:
				*route = 7;
				break;
			case 1:
				*route = 8;
				break;
			default:
				*route = 0;
			}
			break;
		default:
			*route = 0;
		}
}
int search_s(part** aquarium, int i, int j, int x, int y, int sushestvo, int radius, part** sush, int* path1,int f_ret) {
	int f = 0, count = 0;
	for (int m = 1;m <= radius;++m) {
		for (int k = 0;k < 2 * m + 1;++k)
			if (path(aquarium, i, j, x, y, -m, -m + k, 0, 0)->creature == sushestvo && !path(aquarium, i, j, x, y, -m, -m + k, 0, 0)->status) {
				++count;
				if (!f) {
					f = 1;
					if (m > k) *path1 = 1;
					else if (m == k) *path1 = 2;
					else *path1 = 3;
					*sush = path(aquarium, i, j, x, y, -m, -m + k, 0, 0);
					if (f_ret) return count;
				}
			}
		for (int k = 0;k < 2 * m + 1;++k)
			if (path(aquarium, i, j, x, y, m, -m + k, 0, 0)->creature == sushestvo && !path(aquarium, i, j, x, y, m, -m + k, 0, 0)->status) {
				++count;
				if (!f) {
					f = 1;
					if (m > k) *path1 = 6;
					else if (m == k) *path1 = 7;
					else *path1 = 8;
					*sush = path(aquarium, i, j, x, y, m, -m + k, 0, 0);
					if (f_ret) return count;
				}
			}
		for (int k = 1;k <= 2 * m - 1;++k)
			if (path(aquarium, i, j, x, y, -m + k, -m, 0, 0)->creature == sushestvo && !path(aquarium, i, j, x, y, -m + k, -m, 0, 0)->status) {
				++count;
				if (!f) {
					f = 1;
					if (m > k) *path1 = 1;
					else if (m == k) *path1 = 4;
					else *path1 = 6;
					*sush = path(aquarium, i, j, x, y, -m + k, -m, 0, 0);
					if (f_ret) return count;
				}
			}
		for (int k = 1;k <= 2 * m - 1;++k)
			if (path(aquarium, i, j, x, y, -m + k, m, 0, 0)->creature == sushestvo && !path(aquarium, i, j, x, y, -m + k, m, 0, 0)->status) {
				++count;
				if (!f) {
					f = 1;
					if (m > k) *path1 = 3;
					else if (m == k) *path1 = 5;
					else *path1 = 8;
					*sush = path(aquarium, i, j, x, y, -m + k, m, 0, 0);
					if (f_ret) return count;
				}
			}
	}
	return count;
}
int fr(int a, int f) {
	switch (a) {
	case 1:
		if (f) return 4;
		else return 2;
	case 2:
		if (f) return 1;
		else return 3;
	case 3:
		if (f) return 2;
		else return 5;
	case 4:
		if (f) return 6;
		else return 1;
	case 5:
		if (f) return 3;
		else return 8;
	case 6:
		if (f) return 7;
		else return 4;
	case 7:
		if (f) return 8;
		else return 6;
	case 8:
		if (f) return 5;
		else return 7;
	default:
		return 0;
	}
}

void create_plankt(part* pl) {
	pl->creature = plankt;
	plankton* plankton1 = (plankton*)malloc(sizeof(plankton));
	pl->plank = plankton1;
	pl->plank->age = 0;
	pl->status = 0;
	int a = 1;
	if (rand() % 2) a += rand() % 3;
	else a += 8 - rand() % 3;
	preob(&pl->plank->route1, &pl->plank->route2, &a, 1);
}
void create_predatory_fish(part* p_fi) {
	p_fi->creature = pred_fish;
	predatory_fish* predatory_fish1 = (predatory_fish*)malloc(sizeof(predatory_fish));
	p_fi->p_f = predatory_fish1;
	p_fi->p_f->status_razmn = 0;
	p_fi->p_f->age = 0;
	p_fi->status = 0;
	int a = 1;
	if (rand() % 5) a += rand() % 4;
	else a += 8 - rand() % 4;
	preob(&p_fi->p_f->route1, &p_fi->p_f->route2, &a, 1);
	p_fi->p_f->degree_of_satisfaction = 5;
	p_fi->p_f->gender = rand() % 2;
	p_fi->p_f->steps_without_food = 0;
}
void create_fish(part* fi) {
	fi->creature = common_fish;
	fish* fish1 = (fish*)malloc(sizeof(fish));
	fi->f = fish1;
	fi->f->status_razmn = 0;
	fi->f->age = 0;
	fi->status = 0;
	int a = 1;
	if (rand() % 5) a += rand() % 4;
	else a += 8 - rand() % 4;
	preob(&fi->f->route1, &fi->f->route2, &a, 1);
	fi->f->gender = rand() % 2;
	fi->f->degree_of_satisfaction = 10;
	fi->f->steps_without_food = 0;
}
void del(part* pl) {
	pl->creature = 0;
	if (pl->plank) {
		free(pl->plank);
		pl->plank = NULL;
	}
	if (pl->f) {
		free(pl->f);
		(pl->f) = NULL;
	}
	if (pl->p_f) {
		free(pl->p_f);
		pl->p_f = NULL;
	}
}
void copy(part* part1, part* part2) {
	part2->creature = part1->creature;
	part2->f = part1->f;
	part2->p_f = part1->p_f;
	part2->plank = part1->plank;
	part2->status = part1->status;
	part1->creature = 0;
	part1->f = NULL;
	part1->p_f = NULL;
	part1->plank = NULL;
	part1->status = 0;
}