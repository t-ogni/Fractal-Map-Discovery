// Created by moonlin on 27.05.2021.

#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>

typedef std::complex<float> complex;
struct Coord {  float x, y; };

int main() {
    auto mode = sf::VideoMode(600, 600);
    sf::RenderWindow window(mode, "FMD");

    size_t max_iteration = 128;
    float width = 3; // scale = width ^ (-1)
    complex center = {-1,0};
    Coord size = {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
    float step = width / size.x;

    while (window.isOpen()) {
        sf::Event event {};
        while (window.pollEvent(event)){
            if (event.type == event.Closed){
                window.close();
                return 0;
            }  else if (event.type == sf::Event::Resized)
            {
                std::cout << "new width: " << event.size.width << std::endl;
                std::cout << "new height: " << event.size.height << std::endl;
            } else if (event.type == event.MouseButtonPressed){
                float x = center.real() + (static_cast<float>(event.mouseButton.x) - size.x / 2) * step;
                float y = center.imag() + (static_cast<float>(event.mouseButton.y) - size.y / 2) * step;
                center = {x, y};
                if(event.mouseButton.button == sf::Mouse::Left){
                    width /= 5;
                } else if(event.mouseButton.button == sf::Mouse::Right){
                    width *= 5;
                }
            } else if (event.type == sf::Event::MouseWheelScrolled) {

                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    if(event.mouseWheelScroll.delta > 0)
                        max_iteration *= 2;
                    else
                        max_iteration /= 2;    // 1/2 = 0.5 = 0
                    if(max_iteration < 1) max_iteration = 1;
                }
            }
        }
        size = {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
        step = width / size.x;
        window.clear(sf::Color::Black);
        std::cout << "center: " << center  << "\t width: " << width << "\t iter: " << max_iteration << std::endl;
#pragma omp parallel for
        for (int x = 0; x < size.x; ++x) {
            float a = center.real() + ((float)x - size.x / 2) * step;
            for (int y = 0; y < size.y; ++y) {
                float b = center.imag() + ((float)y - size.y / 2) * step;
                complex C = {a, b}, Z = {0.0f, 0.0f};
                int iter = 0;
                while (iter < max_iteration) {
                    Z = Z*Z + C;
                    if(Z.real() * Z.real() + Z.imag() * Z.imag() >= 4.0f) break;
                    iter++;
                }
                if (iter < max_iteration) {
                    sf::Vertex line[] =
                        {
                                sf::Vertex(sf::Vector2f(x, y)),
                                sf::Vertex(sf::Vector2f(x, y+1))
                        };

                    // how to make colors more beautiful?
                    if (iter == max_iteration) iter = 0;
                    double mu = static_cast<double>(iter) / max_iteration;
                    auto clr = sf::Color(int(mu * 1234) % 255, int(mu * 1579) % 255, int(mu*2942) % 255);
                    line->color = clr;
                    window.draw(line, 2, sf::Lines);
                }
            }
        }
        window.display();
    }
    return 0;
}