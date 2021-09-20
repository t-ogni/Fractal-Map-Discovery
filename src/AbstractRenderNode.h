// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_ABSTRACTRENDERNODE_H
#define FRACTAL_MAP_DISCOVERY_ABSTRACTRENDERNODE_H

#include <SFML/Graphics.hpp>
#include <memory>

typedef unsigned int uint;

class AbstractRenderNode {
protected:
    sf::RenderWindow *window = nullptr;
    struct { uint x, y; } size;
    explicit AbstractRenderNode(sf::RenderWindow *renderWindow) :
    	window(renderWindow),
		size( {window->getSize().x, window->getSize().y} ) {};

public:
    virtual void draw() = 0;

	// you can change the current Rendering area to a new one by returning a new RenderNode pointer, or just return zero
	virtual std::shared_ptr<AbstractRenderNode> eventHandler(sf::Event &event) = 0;

    virtual ~AbstractRenderNode() = default;
};

#endif //FRACTAL_MAP_DISCOVERY_ABSTRACTRENDERNODE_H