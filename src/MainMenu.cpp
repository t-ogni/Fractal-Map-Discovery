// Created by moonlin on 23.06.2021.

#include "MainMenu.h"

RenderNode* MainMenu::eventPoll(sf::Event &event) {
    switch (event.type) {
        // keyboard buttons
        case (sf::Event::KeyPressed): {
            switch (event.key.code) {
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
                    return new JuliaSet(window);
                }
                default: {}
            }
            break;
        }
        // Mouse scrolling
        case (sf::Event::MouseWheelScrolled): {
            if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                scroll += event.mouseWheelScroll.delta * 20;
        }
        // other cases
        default: {
            break;
        }
    }
    return nullptr;
}

void MainMenu::draw() {
    // gradient light blue background
    sf::Vertex rectangle[] =
            {
                    sf::Vertex({0, 0}, sf::Color(249,254,255)),
                    sf::Vertex({0, static_cast<float>(window->getSize().y)}, sf::Color(229,251,255)),
                    sf::Vertex({static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)}, sf::Color(190,244,255)),
                    sf::Vertex({static_cast<float>(window->getSize().x), 0}, sf::Color(171,241,255))
            };
    window->draw(rectangle, 4, sf::Quads);

    // 1 / 10 spacing graphic tiles
    // n - screen width,  x, y - space between buttons,  a - buttons width
    // x / a = 0.1  <=>  a = 10x
    // 2x + 3a = n  <=>  a = (n - 3x)/2
    // 10x = (n-3x)/2  <=>  x = n / 23

    auto x = static_cast<float>(size.x / 23);
    auto y = static_cast<float>(size.y / 23);

    for (int i = 0; i < 9; ++i) {

        const sf::Vertex preview [] = {
                sf::Vertex({x * (1 + 11 * (i & 1)), y * (1 + 11 * int(i / 2)) + scroll}, sf::Color(249,0,0)),
                sf::Vertex({(11 * x) * (1 + (i & 1)), y * (1 + 11 * int(i / 2)) + scroll}, sf::Color(229,0,5)),
                sf::Vertex({(11 * x) * (1 + (i & 1)), (11 * y) * (1 + int(i / 2)) + scroll}, sf::Color(190,5,5)),
                sf::Vertex({x * (1 + 11 * (i & 1)), (11 * y) * (1 + int(i / 2)) + scroll}, sf::Color(171,5,5))
        };
        window->draw(preview, 4, sf::Quads);
    }

}