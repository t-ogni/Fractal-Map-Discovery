// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_RENDERNODE_H
#define FRACTAL_MAP_DISCOVERY_RENDERNODE_H

#include <SFML/Graphics.hpp>

class RenderNode {
protected:
    sf::RenderWindow *window = nullptr;
    RenderNode() = default;
    explicit RenderNode(sf::RenderWindow *renderWindow) : window(renderWindow) { };

public:
    virtual void draw() = 0;
    virtual RenderNode* eventPoll(sf::Event &event) = 0;
    // you can change the current Rendering area to a new one by returning a new RenderNode pointer, or just return zero
    virtual ~RenderNode() = default;
};

#endif //FRACTAL_MAP_DISCOVERY_RENDERNODE_H