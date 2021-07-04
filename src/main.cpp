// Created by moonlin on 27.05.2021.

#include "MainMenu.h"

#include <SFML/Graphics.hpp>
#include <thread>

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "FMD");
    // we dont need to draw 120 frames per sec, etc.
    window.setFramerateLimit(0);
    window.setVerticalSyncEnabled(true);

    RenderNode *RenderingArea = new MainMenu(&window);

    while (window.isOpen()) {
        sf::Event event = {};
        while (window.pollEvent(event)) {
            // system events will be processed ...
            switch (event.type) {
                case (event.Closed): {
                    window.close();
                    return 0;
                }
                // ... and other events will be passed to the current drawing area
                default: {
                    auto switchedArea = RenderingArea->eventPoll(event);
                    if(switchedArea) {   // switch area if eventPoll callback returned new
                        delete RenderingArea;
                        RenderingArea = switchedArea;
                    }
                }
            }
        }
        // refresh screen
//        window.clear();
        RenderingArea->draw();
        window.display();
    }

    return 0;
}