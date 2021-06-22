// Created by moonlin on 23.06.2021.

#ifndef FRACTAL_MAP_DISCOVERY_MAINMENU_H
#define FRACTAL_MAP_DISCOVERY_MAINMENU_H

#include "ScreenMode.h"

class MainMenu : public ScreenMode {
public:
    explicit MainMenu(sf::RenderWindow *renderWindow) : ScreenMode(renderWindow) { };

    void draw() override;
    void event() override {};
};


#endif //FRACTAL_MAP_DISCOVERY_MAINMENU_H
