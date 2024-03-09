#pragma once

#include "export.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>

namespace KOD {
namespace GUI {

class Gui;
class UiElement;

struct Settings
{
public:
	GUI_API Settings(sf::Font font);
	GUI_API ~Settings();

	sf::Color m_innerColor = sf::Color::White;
	sf::Color m_borderColor = sf::Color::Black;
	sf::Color m_textColor = sf::Color::Black;
	float m_outlineThickness = 1.0;
	sf::Font m_font;

private:
	GUI_API Settings();

	friend class KOD::GUI::Gui;
	friend class KOD::GUI::UiElement;
};

} // namespace GUI
} // namespace KOD
