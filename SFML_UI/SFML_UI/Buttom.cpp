#include "Buttom.h"

#include <iostream>

KOD::GUI::Buttom::Buttom(const char* text) : Label(text), m_callable(KOD::GUI::Callable(nullptr))
{
	m_rectangle.setSize({100, 100});
}

void KOD::GUI::Buttom::setPosition(sf::Vector2f position)
{
	m_rectangle.setPosition(position);
	KOD::GUI::Label::setPosition({position.x, position.y});
}

void KOD::GUI::Buttom::setRectColor(sf::Color color) { m_rectangle.setFillColor(color); }

void KOD::GUI::Buttom::draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
	Label::draw(window);
}

void KOD::GUI::Buttom::handleUpdateSettings()
{
	Label::handleUpdateSettings();
	m_rectangle.setFillColor(m_settings.m_innerColor);
	m_rectangle.setOutlineColor(m_settings.m_innerColor);
}

void KOD::GUI::Buttom::setOnClickCallback(KOD::GUI::Callable callback)
{
	m_callable = std::move(callback);
}

void KOD::GUI::Buttom::onMousePressed(float x, float y)
{
	if (m_rectangle.getGlobalBounds().contains({x, y})) {
		m_callable.execute();
	}
}

void KOD::GUI::Buttom::updateLabelPosition() {}
