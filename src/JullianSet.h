// Created by moonlin on 04.07.2021.

#ifndef FRACTAL_MAP_DISCOVERY_JULLIANSET_H
#define FRACTAL_MAP_DISCOVERY_JULLIANSET_H

#include "RenderNode.h"
#include "MainMenu.h"

class JullianSet : public RenderNode {

public:
    explicit JullianSet(sf::RenderWindow *renderWindow) : RenderNode(renderWindow) {};

    RenderNode *eventPoll(sf::Event &event) override;
    void draw() override;
};


#endif //FRACTAL_MAP_DISCOVERY_JULLIANSET_H
