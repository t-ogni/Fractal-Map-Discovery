// Created by moonlin on 27.05.2021.

#include <SFML/Graphics.hpp>
#include <complex>

#define MIN_WINDOW_WIDTH 500
#define MIN_WINDOW_HEIGHT 300
#define MAX_ITER 100

struct Coord { float x, y; };
typedef std::complex<float> complex;

int main() {

    enum {
        STATE_MENU,
        STATE_MANDELBROT
    } windowState;
    sf::RenderWindow window(sf::VideoMode(700, 500), "FMD");

    Coord graphStart {-2, 2};
    Coord graphEnd {2, -2};

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::Resized) {
                auto w = static_cast<float>(event.size.width);
                auto h = static_cast<float>(event.size.height);
                if (w < MIN_WINDOW_WIDTH)
                    w = MIN_WINDOW_WIDTH;
                if (h < MIN_WINDOW_HEIGHT)
                    h = MIN_WINDOW_HEIGHT;
                window.setSize(sf::Vector2u(w, h));
                window.setView(
                        sf::View(
                                sf::Vector2f(w / 2.0, h / 2.0),
                                sf::Vector2f(w, h)
                        )
                );
            }
        }

//        switch (windowState) {
//            case STATE_MENU:
//                window.clear(sf::Color(100,200,100));
//                window.d
//
//        }
        // step size of one window pixel
        window.clear(sf::Color(100,200,100));
        float stepX = (graphEnd.x - graphStart.x) / window.getSize().x;
        float stepY = (graphEnd.y - graphStart.y) / window.getSize().y;
        for (int winY = 0; winY < window.getSize().y; ++winY) {
            for (int winX = 0; winX < window.getSize().x; ++winX) {
                // (winX, winY) - window coordinates
                complex z(graphStart.x + stepX * winX, graphStart.y + stepY * winY);
                complex c = z;
                int iteration = 1;
                while(iteration < MAX_ITER) {
                    complex z2;
                    z2.real(z.real() * z.real() - z.imag() * z.imag());
                    z2.imag(2 * z.real() * z.imag());
                    z2.real(z2.real() + c.real());
                    z2.imag(z2.imag() + c.imag());
                    z = z2;
                    if (z.real() * z.real() + z.imag() * z.imag() > 4)
                        break;
                    iteration++;
                }

//                double iterationNorm = iteration / (double)MAX_ITER;
                if(iteration < MAX_ITER){
                    sf::VertexArray lines(sf::LinesStrip, 2);
                    lines[0].position = sf::Vector2f(winX, winY);
                    lines[1].position = sf::Vector2f(winX, winY + 1);
                    window.draw(lines);
                }
            }
        }
        window.display();
    }
    return 0;
}