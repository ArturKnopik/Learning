#include "Gui.h"

#include <iostream>

KOD::GUI::Gui::Gui(sf::RenderWindow& window, KOD::GUI::Settings settings) : m_settings(settings), m_window(window)
{
	m_layout = std::make_unique<KOD::GUI::SimpleLayout>();
}

void KOD::GUI::Gui::handle(sf::Event& event) {}
void KOD::GUI::Gui::draw() { m_layout->draw(m_window); }

void KOD::GUI::Gui::addElement(std::unique_ptr<UiElement> element)
{
	if (!element) {
		return;
	}

	if (!element->m_isCustomSettings) {
		element->m_settings = m_settings;
		element->handleUpdateSettings();
	}

	if (m_layout) {
		m_layout->addUiElement(std::move(element));
	}
}
