#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

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

		renderWindow.clear();
		renderWindow.display();
	}

	return 0;
}