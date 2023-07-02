#ifndef Aquarium_h
#define Aquarium_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

typedef enum creatures { plankt = 1, common_fish, pred_fish } creatures;
typedef enum gend { male, female } gend;

typedef struct plankton {
	int route1;
	int route2;
	int age;
}plankton;

typedef struct fish {
	int status_razmn;
	int route1;
	int route2;
	int age;
	int gender;
	int degree_of_satisfaction;
	int	steps_without_food;
}fish;

typedef struct predatory_fish {
	int status_razmn;
	int route1;
	int route2;
	int age;
	int gender;
	int degree_of_satisfaction;
	int	steps_without_food;
}predatory_fish;

typedef struct part {
	int creature;
	int status;
	plankton* plank;
	fish* f;
	predatory_fish* p_f;
}part;

void generation(part** aquarium, int x, int y, int number_fish, int number_predatory_fish, int number_plankton);
void filling(part** aquarium, creatures creature, int x, int y, int x1, int y1, int a, int x11, int x22);
int biocenosis(part*** aquarium,  int x, int y, int* fish, int* pr_fish, int* plan, int* step);

void processing_common_fish(part** aquarium, int i, int j, int* fish, int* pr_fish, int* plan, int x, int y, int fish_n, int pr_fish_n, int plan_n);
void processing_pred_fish(part** aquarium, int i, int j, int* fish, int* pr_fish, int* plan, int x, int y, int fish_n, int pr_fish_n, int plan_n);
void processing_plankt(part** aquarium,  int i, int j, int* fish, int* pr_fish, int* plan, int x, int y, int fish_n, int pr_fish_n, int plan_n);

int f_per(part** aquarium, int i, int j, int sizex, int sizey, int route1, int route2, int route, int f);
int p_f_per(part** aquarium, int i, int j, int sizex, int sizey, int route1, int route2, int route, int f);
	
void create_plankt(part* pl);
void create_fish(part* fi);
void create_predatory_fish(part* p_fi);
void del(part* fi);
void copy(part* part1, part* part2);

int search_s(part** aquarium, int i, int j, int x, int y, int sushestvo, int radius, part** sush, int* path, int f_ret);
part* path(part** aquarium, int i, int j, int sizex, int sizey, int route1, int route2, int route, int f);
void preob(int* route1, int* route2, int* route, int f);
int fr(int a, int f);

#endif 