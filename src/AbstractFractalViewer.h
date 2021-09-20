//
// Created by moonlin on 20.09.2021.
//

#ifndef FRACTAL_MAP_DISCOVERY_ABSTRACTFRACTALVIEWER_H
#define FRACTAL_MAP_DISCOVERY_ABSTRACTFRACTALVIEWER_H

#include "AbstractRenderNode.h"
#include <cmath>
#include <complex>

#ifdef FRACTAL_STD_DOUBLE
	typedef double bigdouble;
#else
	typedef long double bigdouble;
#endif

typedef std::complex<bigdouble> complex;

sf::Color HSVtoRGB(float H, float S, float V);

class AbstractFractalViewer : public AbstractRenderNode {
protected:
	size_t max_iteration = 256;
	bigdouble width = 3;
	complex center = {0, 0};
	struct { bigdouble x, y; } size {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
	bigdouble step {width / size.x};

public:
	explicit AbstractFractalViewer(sf::RenderWindow *renderWindow):AbstractRenderNode(renderWindow) {};

	std::shared_ptr<AbstractRenderNode> eventHandler(sf::Event &event) override;
};

#endif //FRACTAL_MAP_DISCOVERY_ABSTRACTFRACTALVIEWER_H
