#include "SimpleLayout.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

KOD::GUI::SimpleLayout::SimpleLayout() {}

void KOD::GUI::SimpleLayout::handleEvent(sf::Event& event) {}

void KOD::GUI::SimpleLayout::draw(sf::RenderWindow& window)
{
	for (auto& element : getUiElements()) {
		element->draw(window);
	}
}
