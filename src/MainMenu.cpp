// Created by moonlin on 23.06.2021.

#include "MainMenu.h"
#include <SFML/Graphics/Sprite.hpp>

std::shared_ptr<RenderNode> MainMenu::eventPoll(sf::Event &event) {

    auto x = static_cast<float>(window->getSize().x / 23);
    auto y = static_cast<float>(window->getSize().y / 43);
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
                    return std::make_shared<MandelbrotSet>(window);
                }
                case (sf::Keyboard::Num2): {
                    window->clear(sf::Color::Black);
                    window->display();
                    return std::make_shared<JuliaSet>(window);
                }
                default: {}
            }
            break;
        }
        // Mouse scrolling

        case(sf::Event::MouseButtonPressed): {
            if (event.mouseButton.button != sf::Mouse::Left) break;
            for (int i = 0; i < fractals.size(); ++i) {
                const double previewCoords [] =  // { x0, y0, x1, y1 }
                    {
                            x * (1 + 11 * (i & 1)), y * (1 + 21 * int(i / 2)) + scroll, // pos of the top left tile
                            (11 * x) * (1 + (i & 1)), (21 * y) * (1 + int(i / 2)) + scroll // pos of the lower right tile
                    };
                if  (
                        previewCoords[0] < event.mouseButton.x &&  // start < mousePos
                        previewCoords[1] < event.mouseButton.y &&
                        event.mouseButton.x < previewCoords[2] &&  // mousePos < end
                        event.mouseButton.y < previewCoords[3]
                    ) {
                    return fractals[i].node;
                }
            }
            break;
        }
        case (sf::Event::MouseWheelScrolled): {
            if(event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                scroll += event.mouseWheelScroll.delta * 20;
            if (scroll > 0) scroll = 0;
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
    window->clear();
    // gradient light blue background
    sf::Vertex background[] =
            {
                    sf::Vertex({0, 0}, sf::Color(249, 254, 255)),
                    sf::Vertex({0, static_cast<float>(window->getSize().y)}, sf::Color(229, 251, 255)),
                    sf::Vertex({static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)},
                               sf::Color(190, 244, 255)),
                    sf::Vertex({static_cast<float>(window->getSize().x), 0}, sf::Color(171, 241, 255))
            };
    window->draw(background, 4, sf::Quads);


    // I think, this part of the code is difficult to understand and wrote some tips
    // scale depends on the width
    // tiles and space ratio for x: 1/10, for y: 1/20
    // the bottom part of the image will be hidden
    /*
        n - screen width, x, y - space between tiles,  a - tiles width
        x / a = 1/10  <=>  a = 10x
        2x + 3a = n  <=>  a = (n - 3x)/2
        10x = (n-3x)/2  <=>  x = n / 23

        y = n / 43
    */

    auto x = static_cast<float>(window->getSize().x / 23);
    auto y = static_cast<float>(window->getSize().y / 43);
    for (int i = 0; i < fractals.size(); ++i) { // 'i' means the tile number in order from left to right
        sf::Texture texture;
        sf::Sprite sprite;
        texture.loadFromFile(fractals[i].previewImage);
        sprite.setTexture(texture);

        // scale to tiles width
        auto scale = 10 * x / texture.getSize().x;
        sf::Vector2<float> textureSize = {texture.getSize().x * scale, texture.getSize().y * scale};

        sprite.setPosition(
                {
                    (x * (1 + 11 * (i & 1))),
                    y + ((y + ((textureSize.y < 20 * y) ? textureSize.y : 20 * y)) * int(i / 2) ) + scroll // spacing between tiles not more than img height
                }
        );
        // scale image to window size
        sprite.scale(scale, scale);

        // crop image so as not to overlap other tiles
        sprite.setTextureRect(
                {
                    0,
                    0,
                    static_cast<int>(texture.getSize().x),
                    static_cast<int>(((texture.getSize().y < 20 * y / scale) ? texture.getSize().y : 20 * y / scale)) // dividing by scale returns number to original value

                }
        );

        window->draw(sprite);

        sf::RectangleShape titleBlur(sf::Vector2f(10 * x, 2 * y));
        titleBlur.move(
                (x * (1 + 11 * (i & 1))),
                19 * y + ((y + ((textureSize.y < 20 * y) ? textureSize.y : 20 * y)) * int(i / 2)) + scroll
        );
        titleBlur.setFillColor(sf::Color(50, 50, 50, 180));  // transparent gray
        window->draw(titleBlur);

        sf::Font font;
        font.loadFromFile("resources/SFUI.ttf");
        sf::Text text(fractals[i].title, font);
        text.setCharacterSize(18);
        text.setFillColor(sf::Color::White);
        text.setPosition(
                (x * (1.5 + 11 * (i & 1))),
                19 * y + ((y + ((textureSize.y < 20 * y) ? textureSize.y : 20 * y)) * int(i / 2)) + scroll
        );
        window->draw(text);
    }
}