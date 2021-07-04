// Created by moonlin on 04.07.2021.

#include "JullianSet.h"

void JullianSet::draw() {

}

RenderNode *JullianSet::eventPoll(sf::Event &event) {
    switch (event.type) {
        case (sf::Event::KeyPressed):{
            switch(event.key.code){
                case(sf::Keyboard::Escape): {
                    return new MainMenu(window);
                }
            }
        }
    }
    return nullptr;
}
