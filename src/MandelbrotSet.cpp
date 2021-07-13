// Created by moonlin on 23.06.2021.

#include "MandelbrotSet.h"
#include "MainMenu.h"

std::shared_ptr<RenderNode> MandelbrotSet::eventPoll(sf::Event &event) {
    switch (event.type) {
        case (sf::Event::KeyPressed):{
            switch(event.key.code){
                case(sf::Keyboard::Escape): {
                    return std::make_shared<MainMenu>(window);
                }
                case (sf::Keyboard::I): {
                    float Cr, Ci, W;
                    std::cout << "Description [Default]: value" << std::endl;
                    std::cout << "Enter center Re coord [-1]: ";
                    std::cin >> Cr;
                    std::cout << "Enter center Im coord [0]: ";
                    std::cin >> Ci;
                    std::cout << "Enter center Width [3]: ";
                    std::cin >> W;
                    width = W;
                    center = {Cr, Ci};
                    break;
                }
                case (sf::Keyboard::S): {
                    sf::Vector2u windowSize = window->getSize();
                    sf::Texture texture;
                    texture.create(windowSize.x, windowSize.y);
                    texture.update(*window);
                    sf::Image screenshot = texture.copyToImage();
                    screenshot.saveToFile("screenshots/mandelbrot_" + std::to_string(time(0)) + ".bmp"); //сохраняет в файл
                    break;
                }
                default: {}
            }
            break;
        }
        case (sf::Event::MouseButtonPressed): {
            bigfloat x = center.real() + (static_cast<bigfloat>(event.mouseButton.x) - size.x / 2) * step;
            bigfloat y = center.imag() + (static_cast<bigfloat>(event.mouseButton.y) - size.y / 2) * step;
            center = {x, y};
            if (event.mouseButton.button == sf::Mouse::Left)
                width /= 5;
            else if (event.mouseButton.button == sf::Mouse::Right)
                width *= 5;
            break;
        }
        case (sf::Event::MouseWheelScrolled): {
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (event.mouseWheelScroll.delta > 0)
                    max_iteration *= 2;
                else
                    max_iteration /= 2;    // 1/2 = 0.5 = 0

                if (max_iteration < 1) max_iteration = 1;
            }
            break;
        }


        default:
            break;
    }
    return nullptr;
}

void MandelbrotSet::draw() {
    // calculating variables
    size = {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
    step = width / size.x;
    complex C, Z;

    // debug info
    std::stringstream debug;
    debug << "center: (" << static_cast<float>(center.real()) << ',' << static_cast<float>(center.imag()) << ')'
              << "\t width: " << static_cast<float>(width)
              << "\t iter: " << max_iteration << std::endl;

    window->clear(sf::Color::Black);

    #pragma omp parallel for
    for (int x = 0; x < size.x; ++x) {
        bigfloat a = center.real() + ((float)x - size.x / 2) * step;
        for (int y = 0; y < size.y; ++y) {
            bigfloat b = center.imag() + ((float)y - size.y / 2) * step;

            C = {a, b}, Z = {0.0f, 0.0f};
            int iter = 0;
            while (iter < max_iteration) {
                Z = Z * Z + C;
                if (Z.real() * Z.real() + Z.imag() * Z.imag() >= 4.0f) break;
                iter++;
            }

            if (iter < max_iteration) {
                sf::Vertex line[] =
                        {
                                sf::Vertex(sf::Vector2f(x, y)),
                                sf::Vertex(sf::Vector2f(x, y+1))
                        };

                // colors list

                // the color will switch when iterations are close to the maximum
                float absZ = Z.real() * Z.real() + Z.imag() * Z.imag();
                absZ = log(log(absZ));
                double fraction = static_cast<double>(iter) / max_iteration * static_cast<double>(colors.size() - 1);
                auto color1 = colors[fraction];
                auto color2 = colors[fraction+1];

                // linear color interpolation //     c = c1 + ((c2 - c1) * fraction)
                sf::Color result; // sf::Color not supports multiplication
                result.r = (color2.r - color1.r) * fraction;
                result.g = (color2.g - color1.g) * fraction;
                result.b = (color2.b - color1.b) * fraction;

                line->color = result + color1;
                window->draw(line, 2, sf::Lines);
            }
        }
    }
    sf::Font font;
    font.loadFromFile("resources/SFUI.ttf");
    sf::Text text(debug.str(), font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    window->draw(text);
}