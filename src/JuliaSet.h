// Created by moonlin on 04.07.2021.

#ifndef FRACTAL_MAP_DISCOVERY_JULIASET_H
#define FRACTAL_MAP_DISCOVERY_JULIASET_H

#include <chrono>
#include <complex>
#include <iostream>
#include "RenderNode.h"

typedef std::complex<bigfloat> complex;

class JuliaSet : public RenderNode {
    size_t max_iteration = 256;
    bigfloat width = 3;
    complex center = {0, 0};
    struct  { bigfloat x, y; } size = {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
    bigfloat step = width / size.x;

public:
    explicit JuliaSet(sf::RenderWindow *renderWindow) : RenderNode(renderWindow) {};

    std::shared_ptr<RenderNode> eventPoll(sf::Event &event) override;
    void draw() override;
};




#endif //FRACTAL_MAP_DISCOVERY_JULIASET_H
