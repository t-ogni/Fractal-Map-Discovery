// Created by moonlin on 23.06.2021.

#include "JuliaSet.h"

void JuliaSet::draw() {
    // calculating variables
    size = {static_cast<float>(window->getSize().x), static_cast<float>(window->getSize().y)};
    step = width / size.x;
    complex Z, C {-0.8, 0.15};

    bigdouble r = (1 + sqrt( 1 + 4 * sqrt(pow(C.real(), 2) + pow(C.imag(), 2)) ) ) / 2;

    // debug info
    std::stringstream debug;
    debug << "center: (" << static_cast<float>(center.real()) << ',' << static_cast<float>(center.imag()) << ')'
          << "\t width: " << static_cast<float>(width)
          << "\t iter: " << max_iteration << std::endl;

    window->clear(sf::Color::Black);

#pragma omp parallel for
    for (int x = 0; x < size.x; ++x) {
        bigdouble a = center.real() + ((float)x - size.x / 2) * step;
        for (int y = 0; y < size.y; ++y) {
            bigdouble b = center.imag() + ((float)y - size.y / 2) * step;

            Z = {a, b};

            int iter = 0;
            while (iter < max_iteration) {
                if (Z.real() * Z.real() + Z.imag() * Z.imag() >= r) break;
                Z = Z * Z + C;
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
                        {0,   0,   0},
                        {14,  35,  187},
                        {79,  14,  187},
                        {14,  122, 187},
                        {14,  187, 166},
                        {9,   116, 103}

                };
                // the color will switch when iterations are close to the maximum
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