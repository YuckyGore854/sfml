/*
#include<iostream>
using namespace std;
#include "SFML/Graphics.hpp"
#include "HSL.hpp"
#include <random>
#include <ctime>
const int HEIGHT = 1000;
const int WIDTH = 1000;
const std::string title = "fernny";


sf::RenderWindow renderWindow(sf::VideoMode(WIDTH, HEIGHT), title);
int main() {
    srand(time(NULL));
    float numbus;
    float xn = 0;
    float yn = 0;
    int movement; //f1,f2,etc
    int scale = HEIGHT / 10;
    sf::Event event;
    while (renderWindow.isOpen()) {
        while (renderWindow.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) renderWindow.close();
        }
        numbus = rand() % 100 + 1;
        if (numbus == 1) {
            xn = 0;
            yn = (.16 * yn);
        }
        else if (numbus <= 86) {
            xn = ((.85 * xn) + (.04 * yn));
            yn = ((-.04 * xn) + (.85 * yn) + 1.6);
        }
        else if (numbus <= 93) {
            xn = ((0.2 * xn) - (0.26 * yn));
            yn = ((.23 * xn) + (.22 * yn) + 1.6);
        }
        else {
            xn = ((-.15 * xn) + (.28 * yn));
            yn = (((.23 * xn) + (.24 * yn)) + .44);
        }
        sf::CircleShape a;
        
        int hue = int((xn * scale) + WIDTH / 2) % 360;
        HSL Rainbow(hue, 100, 50);
        a.setFillColor(Rainbow.TurnToRGB());
        a.setPosition(sf::Vector2f(((xn * scale) + WIDTH / 2), (HEIGHT - (yn * scale))));
        a.setRadius(1);
        renderWindow.draw(a);
        renderWindow.display();
    }

}
*/