// Created by moonlin on 27.05.2021.

#include "MainMenu.h"

#include <SFML/Graphics.hpp>
#include <thread>

#include <sys/types.h>
#include <sys/stat.h>
//#define FL128

int main() {

    // create screenshots folder
    #if defined(_WIN32)
        _mkdir("screenshots");
    #else
        mkdir("screenshots", 0744); // rwx r-- r--
    #endif

    sf::RenderWindow window;
    window.create(sf::VideoMode(1280, 960), "FMD");
    // we dont need to draw 120 frames per sec, etc.
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);

    std::shared_ptr<AbstractRenderNode> RenderingArea = std::make_shared<MainMenu>(&window);

    while (window.isOpen()) {
        sf::Event event = {};
        while (window.pollEvent(event)) {
            // system events will be processed ...
            switch (event.type) {
                case (event.Closed): {
                    window.close();
                    return 0;
                }
                case (event.Resized): {
                    sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                    window.setView(sf::View(visibleArea));
                }
                // ... and other events will be passed to the current drawing area
                default: {
                    auto switchedArea = RenderingArea->eventHandler(event);
                    if(switchedArea) {
                        RenderingArea = switchedArea;
                    }
                }
            }
        }
        // refresh screen
        RenderingArea->draw();
        window.display();
    }

    return 0;
}