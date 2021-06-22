// Created by moonlin on 27.05.2021.

#include "MainMenu.h"

#include <SFML/Graphics.hpp>
#include <iostream>
#include <complex>
#include <thread>
#include <chrono>
extern "C" {
    #include <quadmath.h> // __float128
}

typedef __float128 float128;
//typedef float float128;
typedef std::complex<float128> complex;
struct Coord { float128 x, y; };

int main() {

    sf::RenderWindow window(sf::VideoMode(600, 600), "FMD");

    ScreenMode *main = new MainMenu(&window);


    while (window.isOpen()) {
        sf::Event event = {};
        while (window.pollEvent(event)) {
            // all system events would be
            switch (event.type) {
                case (event.Closed): {
                    window.close();
                    return 0;
                }
                default: {
                    main->event();
                }
            }
        }
        window.clear();
        main->draw();
        window.display();
    }
    /*
    size_t max_iteration = 128;
    float128 width = 3; //0.00000000000024; // scale = width ^ (-1)
    complex center = {-1, 0};//{-1.88488933694469, 0.00000000081387};
    Coord size = {static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)};
    float128 step = width / size.x;

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            switch (event.type) {
                case (event.MouseButtonPressed): {
                    float128 x = center.real() + (static_cast<float128>(event.mouseButton.x) - size.x / 2) * step;
                    float128 y = center.imag() + (static_cast<float128>(event.mouseButton.y) - size.y / 2) * step;
                    center = {x, y};
                    if (event.mouseButton.button == sf::Mouse::Left)
                        width /= 5;
                    else if (event.mouseButton.button == sf::Mouse::Right)
                        width *= 5;
                    break;
                }
                case (event.MouseWheelScrolled): {
                    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                        if (event.mouseWheelScroll.delta > 0)
                            max_iteration *= 2;
                        else
                            max_iteration /= 2;    // 1/2 = 0.5 = 0

                        if (max_iteration < 1) max_iteration = 1;
                    }
                    break;
                }
                case (event.KeyPressed): {
                    switch (event.key.code) {
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
                        }
                        default: {
                        }
                    }
                }
                default: {
                }
            }
        }

        // calculating variables
        size = {static_cast<float128>(window.getSize().x), static_cast<float128>(window.getSize().y)};
        step = width / size.x;

        // debug info
        std::cout << "center: (" << static_cast<float>(center.real()) << ',' << static_cast<float>(center.imag()) << ')'
                    << "\t width: " << static_cast<float>(width) << "\t iter: " << max_iteration << std::endl;

        // Calculate the time spent
        auto start = std::chrono::high_resolution_clock::now();
        auto stop = start;

        // draw image on screen
        window.clear(sf::Color::Black);
        #pragma omp parallel for
        for (int x = 0; x < size.x; ++x) {
            float128 a = center.real() + ((float)x - size.x / 2) * step;
            for (int y = 0; y < size.y; ++y) {
                float128 b = center.imag() + ((float)y - size.y / 2) * step;
                complex C = {a, b}, Z = {0.0f, 0.0f};
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
                    static const std::vector<sf::Color> colors{
                            {0,0,0},
                            {213,67,31},
                            {251,255,121},
                            {62,223,89},
                            {43,30,218},
                            {0,255,247}
                    };
                    // the color will switch when iterations are close to the maximum
                    double fraction = static_cast<double>(iter) / max_iteration * static_cast<double>(colors.size() - 1);
                    auto color1 = colors[fraction];
                    auto color2 = colors[fraction+1];

                    // linear color interpolation //     c = c1 + ((c2 - c1) * fraction)
                    sf::Color result;
                    result.r = (color2.r - color1.r) * fraction;
                    result.g = (color2.g - color1.g) * fraction;
                    result.b = (color2.b - color1.b) * fraction;
                    result += color1;

                    line->color = result;
                    window.draw(line, 2, sf::Lines);
                }
            }
        }
        window.display();

        // Calculate the time spent
        stop = std::chrono::high_resolution_clock::now();
        std::cout << "calculated in " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count()
                << "ms"<< std::endl << "-----------" << std::endl;
    }
    */
    return 0;
}