// Created by moonlin on 23.06.2021.

#include "MainMenu.h"

void MainMenu::draw() {
    // background
    sf::Vertex rectangle[] =
            {
                    sf::Vertex({0, 0}, sf::Color::Magenta),
                    sf::Vertex({0, 200}, sf::Color::Green),
                    sf::Vertex({200, 200}, sf::Color::Cyan),
                    sf::Vertex({200, 0}, sf::Color::Blue)
            };

    window->draw(rectangle, 4, sf::Quads);
}