// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_MAINMENU_H
#define FRACTAL_MAP_DISCOVERY_MAINMENU_H

#include "AbstractRenderNode.h"

#include "fractals/MandelbrotSet.h"
#include "fractals/JuliaSet.h"

#include <string>
#include <utility>
#include <vector>
#include <memory>

struct FractalMenuTile {
    std::string title;
    std::string previewImage;
    std::shared_ptr<AbstractRenderNode> node;
    FractalMenuTile(std::string t, std::string i, std::shared_ptr<AbstractRenderNode> n){
        title = std::move(t);
        previewImage = std::move(i);
        node = std::move(n);
    }
};

class MainMenu : public AbstractRenderNode {
    std::vector <FractalMenuTile> fractals {};
    int scroll = 0;
public:
    explicit MainMenu(sf::RenderWindow *renderWindow) :AbstractRenderNode(renderWindow) {

        fractals.emplace_back(
                    "Mandelbrot set",
                    "resources/mandelbrot.png",
                    std::make_shared<MandelbrotSet>(renderWindow)

        );
        fractals.emplace_back(
                    "Julia set",
                    "resources/julia.jpg",
                    std::make_shared<JuliaSet>(renderWindow)

        );
    };

    void draw() override;
    std::shared_ptr<AbstractRenderNode> eventHandler(sf::Event &) override;
};


#endif //FRACTAL_MAP_DISCOVERY_MAINMENU_H
