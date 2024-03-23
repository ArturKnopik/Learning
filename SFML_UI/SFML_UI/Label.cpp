#include "Label.h"

KOD::GUI::Label::Label() { handleUpdateSettings(); }

KOD::GUI::Label::Label(const char* str)
{
	handleUpdateSettings();
	m_text.setString(std::string(str));
}

void KOD::GUI::Label::setSize(unsigned int size) { m_text.setCharacterSize(size); }

void KOD::GUI::Label::setText(const char* str) { m_text.setString(str); }

void KOD::GUI::Label::setPosition(sf::Vector2f position) { m_text.setPosition(position); }

sf::Vector2f KOD::GUI::Label::getPosition() { return m_text.getPosition(); }

void KOD::GUI::Label::draw(sf::RenderWindow& window) { 
	window.draw(m_text); 
}

void KOD::GUI::Label::handleUpdateSettings()
{
	m_text.setFont(m_settings.m_font);
	m_text.setFillColor(m_settings.m_textColor);
	m_text.setOutlineColor(m_settings.m_textColor);
}
