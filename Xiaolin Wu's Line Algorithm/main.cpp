#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Source/XiaolinWusLineAlgorithm.hpp"

#include <iostream>

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(800,600), "Xiaolin Wu's Line Algorithm");

	std::vector<sf::Vector2f> points;

	while(renderWindow.isOpen())
	{
		float x = static_cast<float>(sf::Mouse::getPosition(renderWindow).x);
		float y = static_cast<float>(sf::Mouse::getPosition(renderWindow).y);

		sf::Event event;
		while(renderWindow.pollEvent(event))
		{
			if(event.type == sf::Event::Closed)
				renderWindow.close();
			if(event.type == sf::Event::KeyPressed)
			{
				if(event.key.code == sf::Keyboard::Escape)
					renderWindow.close();
			}
			if(event.type == sf::Event::MouseButtonPressed)
			{
				if(event.mouseButton.button == sf::Mouse::Left)
					points.push_back(sf::Vector2f(x,y));
				if(event.mouseButton.button == sf::Mouse::Right)
				{
					if(!points.empty())
						points.pop_back();
				}
			}
		}

		renderWindow.clear();
		
		for(std::size_t i = 0; i < points.size() - 1 && points.size() > 1; ++i)
			drawLine(renderWindow, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, sf::Color::White);

		if(!points.empty())
			drawLine(renderWindow, points[points.size() - 1].x, points[points.size() - 1].y, x , y, sf::Color::White);

		std::cout << points.size() << std::endl;
		renderWindow.display();
	}

	return 0;
}