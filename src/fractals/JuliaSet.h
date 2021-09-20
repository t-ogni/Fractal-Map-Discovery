// Created by moonlin on 04.07.2021.

#ifndef FRACTAL_MAP_DISCOVERY_JULIASET_H
#define FRACTAL_MAP_DISCOVERY_JULIASET_H

#include <chrono>
#include <complex>
#include <iostream>
#include "../AbstractFractalViewer.h"

class JuliaSet : public AbstractFractalViewer {

public:
    explicit JuliaSet(sf::RenderWindow *renderWindow) : AbstractFractalViewer(renderWindow) {};

    void draw() override;
};




#endif //FRACTAL_MAP_DISCOVERY_JULIASET_H
