// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_SCREENMODE_H
#define FRACTAL_MAP_DISCOVERY_SCREENMODE_H

#include <SFML/Graphics.hpp>

class ScreenMode {
protected:
    sf::RenderWindow *window = nullptr;
    explicit ScreenMode(sf::RenderWindow *renderWindow) : window(renderWindow) { };

public:
    virtual void draw() = 0;
    virtual void event() = 0;
};

#endif //FRACTAL_MAP_DISCOVERY_SCREENMODE_H
