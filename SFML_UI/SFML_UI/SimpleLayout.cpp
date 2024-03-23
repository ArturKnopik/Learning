#include "SimpleLayout.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>

KOD::GUI::SimpleLayout::SimpleLayout(const sf::RenderWindow& window) : m_window(window) {}

void KOD::GUI::SimpleLayout::handleEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
		onMousePressed(sf::Mouse::getPosition(m_window).x, sf::Mouse::getPosition(m_window).y);
	}
}

void KOD::GUI::SimpleLayout::draw(sf::RenderWindow& window)
{
	for (auto& element : getUiElements()) {
		element->draw(window);
	}
}

void KOD::GUI::SimpleLayout::onMousePressed(float x, float y)
{
	for (auto& element : getUiElements()) {
		element->onMousePressed(x, y);
	}
}