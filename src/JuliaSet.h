// Created by moonlin on 04.07.2021.

#ifndef FRACTAL_MAP_DISCOVERY_JULIASET_H
#define FRACTAL_MAP_DISCOVERY_JULIASET_H

#include "RenderNode.h"
#include "MainMenu.h"

class JuliaSet : public RenderNode {

public:
    explicit JuliaSet(sf::RenderWindow *renderWindow) : RenderNode(renderWindow) {};

    RenderNode *eventPoll(sf::Event &event) override;
    void draw() override;
};


#endif //FRACTAL_MAP_DISCOVERY_JULIASET_H
