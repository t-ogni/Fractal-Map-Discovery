// Created by moonlin on 23.06.2021.

#include "MandelbrotSet.h"

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
uint min=999, max=0, avg=0;
    #pragma omp parallel for
    for (int x = 0; x <= size.x; ++x) {
        bigdouble a = center.real() + ((double) x - size.x / 2) * step;
        for (int y = 0; y <= size.y; ++y) {
            bigdouble b = center.imag() + ((double) y - size.y / 2) * step;

            C = {a, b}, Z = {0.0f, 0.0f};
			double smoothColor = 0;

            int iter = 0;
            while (iter < max_iteration) {
                Z = Z * Z + C;
                if (Z.real() * Z.real() + Z.imag() * Z.imag() >= 4.0f) break;
				smoothColor += abs(Z);
                iter++;
            }

            if (iter < max_iteration) {
                sf::Vertex line[] =
                        {
                                sf::Vertex(sf::Vector2f(x, y)),
                                sf::Vertex(sf::Vector2f(x, y+1))
                        };

//				smoothColor = 360 * smoothColor ;
                line->color = HSVtoRGB(static_cast<float>(smoothColor), 50, 30);
                window->draw(line, 2, sf::Lines);
            }
        }
    }

    std::cout << min << ':' << max << '\n';
    sf::Font font;
    font.loadFromFile("resources/SFUI.ttf");
    sf::Text text(debug.str(), font);
    text.setCharacterSize(12);
    text.setFillColor(sf::Color::White);
    window->draw(text);
}