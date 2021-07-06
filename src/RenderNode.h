// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_RENDERNODE_H
#define FRACTAL_MAP_DISCOVERY_RENDERNODE_H

#include <SFML/Graphics.hpp>


#ifdef FL128
    #include <quadmath.h>
    typedef __float128 float128;
#else
    typedef float float128;
#endif //FL128

class RenderNode {
protected:
    sf::RenderWindow *window = nullptr;
    struct { float128 x, y; } size;
    explicit RenderNode(sf::RenderWindow *renderWindow) : window(renderWindow),
                                size({static_cast<float>(window->getSize().x),
                                      static_cast<float>(window->getSize().y)}) { };

public:
    virtual void draw() = 0;
    virtual RenderNode* eventPoll(sf::Event &event) = 0;
    // you can change the current Rendering area to a new one by returning a new RenderNode pointer, or just return zero
    virtual ~RenderNode() = default;
};

#endif //FRACTAL_MAP_DISCOVERY_RENDERNODE_H