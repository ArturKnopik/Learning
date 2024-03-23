#include "UiElement.h"

size_t KOD::GUI::UiElement::s_uid = 0;

KOD::GUI::UiElement::UiElement() : m_settings(KOD::GUI::Settings())
{
	m_uid = s_uid;
	s_uid++;
}

void KOD::GUI::UiElement::setSettings(KOD::GUI::Settings settings)
{
	m_isCustomSettings = true;
	m_settings = settings;
}

void KOD::GUI::UiElement::draw(sf::RenderWindow &window) {}

size_t KOD::GUI::UiElement::getUid() { return m_uid; }

void KOD::GUI::UiElement::onMouseEnter() {}

void KOD::GUI::UiElement::onMouseLeave() {}

void KOD::GUI::UiElement::onMouseMoved(float x, float y) {}

void KOD::GUI::UiElement::onMousePressed(float x, float y) {}

void KOD::GUI::UiElement::onMouseReleased(float x, float y) {}

void KOD::GUI::UiElement::onMouseWheelMoved() {}

void KOD::GUI::UiElement::handleUpdateSettings() {}