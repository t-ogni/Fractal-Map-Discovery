// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_MAINMENU_H
#define FRACTAL_MAP_DISCOVERY_MAINMENU_H

#include "RenderNode.h"
#include "MandelbrotSet.h"
#include "JullianSet.h"
//#include <SFML/Text.hpp>

class MainMenu : public RenderNode {
//    std::vector<std::tuple<RenderNode *, std::string>> resources; // not working
public:
    explicit MainMenu(sf::RenderWindow *renderWindow) : RenderNode(renderWindow) { };

    void draw() override;
    RenderNode* eventPoll(sf::Event &) override;

    ~MainMenu() = default;
};


#endif //FRACTAL_MAP_DISCOVERY_MAINMENU_H
