//
// Created by moonlin on 20.09.2021.
//
#include "AbstractFractalViewer.h"
#include "MainMenu.h"

// 0 <= H <= 360, 0 <= S,V <= 100
sf::Color HSVtoRGB(float H, float S, float V){
	float s = S/100;
	float v = V/100;
	float C = s*v;
	float X = C*(1-abs(fmod(H/60.0, 2)-1));
	float m = v-C;
	float r,g,b;
	if(H >= 0 && H < 60){
		r = C,g = X,b = 0;
	}
	else if(H >= 60 && H < 120){
		r = X,g = C,b = 0;
	}
	else if(H >= 120 && H < 180){
		r = 0,g = C,b = X;
	}
	else if(H >= 180 && H < 240){
		r = 0,g = X,b = C;
	}
	else if(H >= 240 && H < 300){
		r = X,g = 0,b = C;
	}
	else{
		r = C,g = 0,b = X;
	}
	sf::Uint8 R = (r+m)*255;
	sf::Uint8 G = (g+m)*255;
	sf::Uint8 B = (b+m)*255;
	return {R, G, B};
}

std::shared_ptr<AbstractRenderNode> AbstractFractalViewer::eventHandler(sf::Event &event) {
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
			screenshot.saveToFile("screenshots/mandelbrot_" + std::to_string(time(nullptr)) + ".bmp"); //сохраняет в файл
			break;
		}
		default: {}
		}
		break;
	}
	case (sf::Event::MouseButtonPressed): {
		bigdouble x = center.real() + (static_cast<bigdouble>(event.mouseButton.x) - size.x / 2) * step;
		bigdouble y = center.imag() + (static_cast<bigdouble>(event.mouseButton.y) - size.y / 2) * step;
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
