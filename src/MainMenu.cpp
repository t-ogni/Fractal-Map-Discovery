// Created by moonlin on 23.06.2021.

#include "MainMenu.h"

RenderNode* MainMenu::eventPoll(sf::Event &ev) {
    switch (ev.type) {
        // keyboard buttons
        case (sf::Event::KeyPressed): {
            switch (ev.key.code) {
                case (sf::Keyboard::Num1): {
                    // draw a hint on the screen
                    window->clear(sf::Color::Black);
                    sf::Font font;
                    font.loadFromFile("resources/SFUI.ttf");
                    sf::Text text("wait until the image is calculated", font);
                    text.setCharacterSize(12);
                    text.setFillColor(sf::Color::White);
                    window->draw(text);
                    window->display();

                    return new MandelbrotSet(window);
                }
                case (sf::Keyboard::Num2): {
                    window->clear(sf::Color::Black);
                    sf::Font font;
                    font.loadFromFile("resources/SFUI.ttf");
                    sf::Text text("wait until the image is calculated", font);
                    text.setCharacterSize(12);
                    text.setFillColor(sf::Color::White);
                    window->draw(text);
                    window->display();
                    return new JullianSet(window);
                }
                default: {}
            }
            break;
        }
        // other cases
        default: {
            break;
        }
    }
    return nullptr;
}

void MainMenu::draw() {
    // gradient blue background
    sf::Vertex rectangle[] =
            {
                    sf::Vertex({0, 0}, sf::Color(176, 224, 230)),
                    sf::Vertex({0, static_cast<float>(window->getSize().y)}, sf::Color(176, 196, 222)),
                    sf::Vertex({static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)}, sf::Color(0, 191, 255)),
                    sf::Vertex({static_cast<float>(window->getSize().x), 0}, sf::Color(135, 206, 250))
            };

    window->draw(rectangle, 4, sf::Quads);

    // Create a text & Draw it
    sf::Font font;
    font.loadFromFile("resources/SFUI.ttf");
    sf::Text text("use \"1\" and \"2\" to open the fractals\n"
                        "and use \"esc\" to return to the menu", font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);

    window->draw(text);

}