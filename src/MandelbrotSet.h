// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_MANDELBROTSET_H
#define FRACTAL_MAP_DISCOVERY_MANDELBROTSET_H

#include <chrono>
#include <complex>
#include <iostream>
#include "RenderNode.h"


typedef std::complex<bigfloat> complex;

class MandelbrotSet : public RenderNode {
    size_t max_iteration = 256;
    bigfloat width = 3;
    complex center = {-1, 0};
    struct  { bigfloat x, y; } size = {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
    bigfloat step = width / size.x;
    const std::vector<sf::Color> colors {
            {0,   0,   0},
            {14,  35,  187},
            {14,  122, 187},
            {79,  122,  187},
            {79,  187, 166},
            {80,   116, 103}

    };

public:
    explicit MandelbrotSet(sf::RenderWindow *renderWindow) : RenderNode(renderWindow) {};

    std::shared_ptr<RenderNode> eventPoll(sf::Event &event) override;
    void draw() override;
};


#endif //FRACTAL_MAP_DISCOVERY_MANDELBROTSET_H
