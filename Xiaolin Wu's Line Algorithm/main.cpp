#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include "Source/XiaolinWusLineAlgorithm.hpp"

int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(800,600), "Xiaolin Wu's Line Algorithm");



	while(renderWindow.isOpen())
	{
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
		}

		float x = sf::Mouse::getPosition(renderWindow).x;
		float y = sf::Mouse::getPosition(renderWindow).y;

		renderWindow.clear();
		drawLine(renderWindow,400,300,x,y,sf::Color::White);
		renderWindow.display();
	}

	return 0;
}