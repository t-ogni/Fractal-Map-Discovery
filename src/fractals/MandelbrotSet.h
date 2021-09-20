// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_MANDELBROTSET_H
#define FRACTAL_MAP_DISCOVERY_MANDELBROTSET_H

#include <chrono>
#include <iostream>
#include "../AbstractFractalViewer.h"


class MandelbrotSet : public AbstractFractalViewer {

    const std::vector<sf::Color> colors {
            {0,   0,   0},
            {14,  35,  187},
            {14,  122, 187},
            {79,  122,  187},
            {79,  187, 166},
            {80,   116, 103}

    };

public:
    explicit MandelbrotSet(sf::RenderWindow *renderWindow) : AbstractFractalViewer(renderWindow) {};

    void draw() override;
};


#endif //FRACTAL_MAP_DISCOVERY_MANDELBROTSET_H
