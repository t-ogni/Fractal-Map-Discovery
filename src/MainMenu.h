// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_MAINMENU_H
#define FRACTAL_MAP_DISCOVERY_MAINMENU_H

#include "MandelbrotSet.h"
#include "RenderNode.h"
#include "JuliaSet.h"
#include <string>
#include <vector>
#include <memory>

struct FractalMenuTile {
    std::string title;
    std::string previewImage;
    std::shared_ptr<RenderNode> node;
    FractalMenuTile(std::string t, std::string i, std::shared_ptr<RenderNode> n){
        title = t;
        previewImage = i;
        node = n;
    }
};

class MainMenu : public RenderNode {
    std::vector <FractalMenuTile> fractals {};
    int scroll = 0;
public:
    explicit MainMenu(sf::RenderWindow *renderWindow) : RenderNode(renderWindow) {

        fractals.push_back(
                {
                    "Mandelbrot set",
                    "resources/mandelbrot.png",
                    std::make_shared<MandelbrotSet>(renderWindow)
                }
        );
        fractals.push_back(
                {
                    "Julia set",
                    "resources/julia.jpg",
                    std::make_shared<JuliaSet>(renderWindow)
                }
        );
    };

    void draw() override;
    std::shared_ptr<RenderNode> eventPoll(sf::Event &) override;

    ~MainMenu() = default;
};


#endif //FRACTAL_MAP_DISCOVERY_MAINMENU_H
