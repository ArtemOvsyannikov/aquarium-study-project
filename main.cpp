#define _CRT_SECURE_NO_WARNINGS
#define size_x 72
#define size_y 144
#define number_of_fish 300
#define number_of_predatory_fish 250
#define number_of_plankton 1000

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Aqua.h"

using namespace sf;

int main()
{
    srand((unsigned int)time(NULL));
    int step = 0, n_fish = number_of_fish, n_pr_fish = number_of_predatory_fish, n_pl = number_of_plankton;
    part** aquarium = (part**)calloc(size_x, sizeof(part*));
    for (int i = 0;i < size_x;++i) aquarium[i] = (part*)calloc(size_y, sizeof(part));
    generation(aquarium, size_x, size_y, number_of_fish, number_of_predatory_fish, number_of_plankton);

    const int  window_X = 1910;
    const int  window_Y = 900;
    const int gridSize1 = size_y;
    const int gridSize2 = size_x;
    const float cellSize = 12.50;

    RenderWindow window(VideoMode(window_X, window_Y), "SFML window");

    std::vector<std::vector<sf::RectangleShape>> cells;
    cells.resize(gridSize1, std::vector<sf::RectangleShape>(gridSize2));

    sf::Font font;
    font.loadFromFile("C:/shrift.ttf");
    sf::Font fontik;
    fontik.loadFromFile("C:/shriftik.ttf");

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(18);
    text.setFillColor(sf::Color(255, 255, 255));

    sf::Text pl;
    pl.setFont(font);
    pl.setCharacterSize(18);
    pl.setFillColor(sf::Color(255, 255, 255));
    sf::Text pl_old;
    pl_old.setFont(font);
    pl_old.setCharacterSize(18);
    pl_old.setFillColor(sf::Color(255, 255, 255));

    sf::Text fish;
    fish.setFont(font);
    fish.setCharacterSize(18);
    fish.setFillColor(sf::Color(255, 255, 255));
    sf::Text fish_old;
    fish_old.setFont(font);
    fish_old.setCharacterSize(18);
    fish_old.setFillColor(sf::Color(255, 255, 255));

    sf::Text pr_fish;
    pr_fish.setFont(font);
    pr_fish.setCharacterSize(18);
    pr_fish.setFillColor(sf::Color(255, 255, 255));
    sf::Text pr_fish_old;
    pr_fish_old.setFont(font);
    pr_fish_old.setCharacterSize(18);
    pr_fish_old.setFillColor(sf::Color(255, 255, 255));

    sf::Text textik;
    textik.setFont(font);
    textik.setCharacterSize(200);
    textik.setFillColor(sf::Color(230, 25, 25));
    int stepp = 0, flagg = 0;

    for (int i = 0; i < gridSize1; i++)
    {
        for (int j = 0; j < gridSize2; j++)
        {
            cells[i][j].setSize(sf::Vector2f(cellSize, cellSize));
            cells[i][j].setFillColor(sf::Color(0, 0, 255));
            cells[i][j].setPosition(i * cellSize, j * cellSize);
        }
    }

    int greenX[size_x * size_y + 1] = { 0 };
    int greenY[size_x * size_y + 1] = { 0 };
    int redX[size_x * size_y + 1] = { 0 };
    int redY[size_x * size_y + 1] = { 0 };
    int yellowX[size_x * size_y + 1] = { 0 };
    int yellowY[size_x * size_y + 1] = { 0 };

    int greenX_1[size_x * size_y + 1] = { 0 };
    int greenY_1[size_x * size_y + 1] = { 0 };
    int redX_1[size_x * size_y + 1] = { 0 };
    int redY_1[size_x * size_y + 1] = { 0 };
    int yellowX_1[size_x * size_y + 1] = { 0 };
    int yellowY_1[size_x * size_y + 1] = { 0 };
    int green_id = 0, red_id = 0, yellow_id = 0, green1_id = 0, red1_id = 0, yellow1_id = 0;

    sf::CircleShape greenCircle;
    greenCircle.setRadius(cellSize / 2);
    greenCircle.setFillColor(sf::Color(0, 255, 0));
    sf::CircleShape redCircle;
    redCircle.setRadius(cellSize / 2);
    redCircle.setFillColor(sf::Color(255, 0, 0));
    sf::CircleShape yellowCircle;
    yellowCircle.setRadius(cellSize / 2);
    yellowCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape green1Circle;
    green1Circle.setRadius(cellSize / 2);
    green1Circle.setFillColor(sf::Color(0, 128, 0));
    sf::CircleShape red1Circle;
    red1Circle.setRadius(cellSize / 2);
    red1Circle.setFillColor(sf::Color(128, 0, 0));
    sf::CircleShape yellow1Circle;
    yellow1Circle.setRadius(cellSize / 2);
    yellow1Circle.setFillColor(sf::Color(128, 128, 0));


    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        if (flagg) {
            greenCircle.setFillColor(sf::Color(0, 255, 0, 125));
            redCircle.setFillColor(sf::Color(255, 0, 0, 125));
            yellowCircle.setFillColor(sf::Color(255, 255, 0, 125));
            green1Circle.setFillColor(sf::Color(0, 128, 0, 175));
            red1Circle.setFillColor(sf::Color(128, 0, 0, 175));
            yellow1Circle.setFillColor(sf::Color(128, 128, 0, 175));
        }
        for (int i = 0; i < gridSize1; ++i) {
            for (int j = 0; j < gridSize2; ++j) {
                if (flagg) cells[i][j].setFillColor(sf::Color(0, 0, 255, 125));
                window.draw(cells[i][j]);
            }
        }

        for (int i = 0; i <= gridSize1; i++)
        {
            sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(i * cellSize, 0)),
                    sf::Vertex(sf::Vector2f(i * cellSize, (long long)(window_X * 180 / 191)))
            };
            window.draw(line, 2, sf::Lines);
            line[0] = sf::Vertex(sf::Vector2f(0, i * cellSize));
            line[1] = sf::Vertex(sf::Vector2f((long long)(window_X * 180 / 191), i * cellSize));
            window.draw(line, 2, sf::Lines);
        }

        green_id = red_id = yellow_id = green1_id = red1_id = yellow1_id = 0;

        for (int i = 0; i < size_x; ++i)
        {
            for (int j = 0; j < size_y; ++j) {
                if (aquarium[i][j].creature == plankt) {
                    if (aquarium[i][j].plank->age > 10) {
                        greenX_1[green1_id] = j;
                        greenY_1[green1_id] = i;
                        ++green1_id;
                    }
                    else {
                        greenX[green_id] = j;
                        greenY[green_id] = i;
                        ++green_id;
                    }
                }
                if (aquarium[i][j].creature == pred_fish) {
                    if (aquarium[i][j].p_f->age > 38) {
                        redX_1[red1_id] = j;
                        redY_1[red1_id] = i;
                        ++red1_id;
                    }
                    else {
                        redX[red_id] = j;
                        redY[red_id] = i;
                        ++red_id;
                    }
                }
                if (aquarium[i][j].creature == common_fish) {
                    if (aquarium[i][j].f->age > 28) {
                        yellowX_1[yellow1_id] = j;
                        yellowY_1[yellow1_id] = i;
                        ++yellow1_id;
                    }
                    else {
                        yellowX[yellow_id] = j;
                        yellowY[yellow_id] = i;
                        ++yellow_id;
                    }
                }
            }
        }

        for (int i = 0; i < green_id; ++i)
        {
            greenCircle.setPosition(greenX[i] * cellSize, greenY[i] * cellSize);
            window.draw(greenCircle);
        }

        greenCircle.setRadius(cellSize);
        greenCircle.setFillColor(sf::Color(0, 255, 0));
        greenCircle.setPosition(1805, 40);
        window.draw(greenCircle);
        greenCircle.setRadius(cellSize / 2);
        if (flagg) greenCircle.setFillColor(sf::Color(0, 255, 0, 125));

        for (int i = 0; i < green1_id; ++i)
        {
            green1Circle.setPosition(greenX_1[i] * cellSize, greenY_1[i] * cellSize);
            window.draw(green1Circle);
        }

        green1Circle.setRadius(cellSize);
        green1Circle.setFillColor(sf::Color(0, 128, 0));
        green1Circle.setPosition(1805, 85);
        window.draw(green1Circle);
        green1Circle.setRadius(cellSize / 2);
        if (flagg) green1Circle.setFillColor(sf::Color(0, 128, 0, 175));

        for (int i = 0; i < red_id; ++i)
        {
            redCircle.setPosition(redX[i] * cellSize, redY[i] * cellSize);
            window.draw(redCircle);
        }

        redCircle.setRadius(cellSize);
        redCircle.setFillColor(sf::Color(255, 0, 0));
        redCircle.setPosition(1805, 130);
        window.draw(redCircle);
        redCircle.setRadius(cellSize / 2);
        if (flagg) redCircle.setFillColor(sf::Color(255, 0, 0, 125));

        for (int i = 0; i < red1_id; ++i)
        {
            red1Circle.setPosition(redX_1[i] * cellSize, redY_1[i] * cellSize);
            window.draw(red1Circle);
        }

        red1Circle.setRadius(cellSize);
        red1Circle.setFillColor(sf::Color(128, 0, 0));
        red1Circle.setPosition(1805, 175);
        window.draw(red1Circle);
        red1Circle.setRadius(cellSize / 2);
        if (flagg) red1Circle.setFillColor(sf::Color(128, 0, 0, 175));

        for (int i = 0; i < yellow_id; ++i)
        {
            yellowCircle.setPosition(yellowX[i] * cellSize, yellowY[i] * cellSize);
            window.draw(yellowCircle);
        }

        yellowCircle.setRadius(cellSize);
        yellowCircle.setFillColor(sf::Color(255, 255, 0));
        yellowCircle.setPosition(1805, 220);
        window.draw(yellowCircle);
        yellowCircle.setRadius(cellSize / 2);
        if (flagg) yellowCircle.setFillColor(sf::Color(255, 255, 0, 125));

        for (int i = 0; i < yellow1_id; ++i)
        {
            yellow1Circle.setPosition(yellowX_1[i] * cellSize, yellowY_1[i] * cellSize);
            window.draw(yellow1Circle);
        }

        yellow1Circle.setRadius(cellSize);
        yellow1Circle.setFillColor(sf::Color(128, 128, 0));
        yellow1Circle.setPosition(1805, 265);
        window.draw(yellow1Circle);
        yellow1Circle.setRadius(cellSize / 2);
        if (flagg) yellow1Circle.setFillColor(sf::Color(128, 128, 0, 175));

        text.setString("Step: " + std::to_string(stepp));
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width + 10, textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(window_X, window_Y / 2.0f));
        window.draw(text);

        pl.setString("Plankton");
        pl.setPosition(sf::Vector2f(1835, 38));
        window.draw(pl);
        pl_old.setString("  Old\nplankton");
        pl_old.setPosition(sf::Vector2f(1835, 75));
        window.draw(pl_old);

        pr_fish.setString("Imposter");
        pr_fish.setPosition(sf::Vector2f(1835, 128));
        window.draw(pr_fish);
        pr_fish_old.setString("  Old\nimposter");
        pr_fish_old.setPosition(sf::Vector2f(1835, 165));
        window.draw(pr_fish_old);

        fish.setString("Fish");
        fish.setPosition(sf::Vector2f(1850, 218));
        window.draw(fish);
        fish_old.setString("Old\nfish");
        fish_old.setPosition(sf::Vector2f(1850, 255));
        window.draw(fish_old);

        if (!flagg) {
            ++stepp;
            if (biocenosis(&aquarium, size_x, size_y, &n_fish, &n_pr_fish, &n_pl, &step)) flagg = 1;
        }
        else {
            textik.setString("AQUARIUM\n  DIED");
            sf::FloatRect textikRect = textik.getLocalBounds();
            textik.setOrigin(textikRect.left + textikRect.width / 2.0f, textikRect.top + textikRect.height / 2.0f);
            textik.setPosition(sf::Vector2f(1900 / 2.0f, 900 / 2.0f));
            window.draw(textik);
        }
        window.display();
        //sf::sleep(sf::milliseconds(3000));
    }
    for (int i = 0;i < size_x;++i) for (int j = 0;j < size_y;++j) del(&aquarium[i][j]);
    return 0;
}