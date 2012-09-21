////////////////////////////////////////////////////////////////////////////////
// main.cpp
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include "Source/XiaolinWusLineAlgorithm.hpp"
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// Entry point of application
////////////////////////////////////////////////////////////////////////////////
int main()
{
	sf::RenderWindow renderWindow(sf::VideoMode(800,600), "Xiaolin Wu's Line Algorithm");

	std::vector<sf::Vector2f> points;
	std::vector<std::shared_ptr<sf::RenderTexture>> textures;

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
				if(event.key.code == sf::Keyboard::Space)
				{
					// Don't add a new layer unless there's some points in the current layer
					if(!points.empty())
					{
						// Create a new layer
						textures.push_back(std::shared_ptr<sf::RenderTexture>(new sf::RenderTexture()));
						int index = textures.size() - 1;
						textures[index]->create(renderWindow.getSize().x, renderWindow.getSize().y);

						// Add the last point to the current layer
						points.push_back(sf::Vector2f(x, y));

						// Draw all current points to the new layer
						for(std::size_t i = 0; i < points.size() - 1; ++i)
							drawLine(*textures[index], points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, sf::Color::White);

						textures[index]->display();
						points.clear();
					}
				}
			}

			if(event.type == sf::Event::MouseButtonPressed)
			{
				// Add a point to the current layer
				if(event.mouseButton.button == sf::Mouse::Left)
					points.push_back(sf::Vector2f(x,y));
				if(event.mouseButton.button == sf::Mouse::Right)
				{
					// Remove a point from the current layer
					if(points.empty())
					{
						// If there's no points left on the current layer
						// then start removing layers
						if(!textures.empty())
							textures.pop_back();
					}
					else
						points.pop_back();
				}
			}
		}

		renderWindow.clear();
		
		// Render all the layers
		for(std::size_t i = 0; i < textures.size(); ++i)
			renderWindow.draw(sf::Sprite(textures[i]->getTexture()));

		// Render all points from the current layer
		for(std::size_t i = 0; i < points.size() - 1 && points.size() > 1; ++i)
			drawLine(renderWindow, points[i].x, points[i].y, points[i + 1].x, points[i + 1].y, sf::Color::White);

		// Render a line between the last point of the current layer to the mouse position
		if(!points.empty())
			drawLine(renderWindow, points[points.size() - 1].x, points[points.size() - 1].y, x , y, sf::Color::White);

		renderWindow.display();
	}

	return 0;
}