#pragma once
#include "UiElement.h"

#include <SFML/Graphics/Text.hpp>

namespace KOD {
namespace GUI {

class Label : public KOD::GUI::UiElement
{
public:
	GUI_API Label();
	GUI_API Label(const char* str);
	GUI_API void setSize(unsigned int size);
	GUI_API void setText(const char* str);
	GUI_API void setPosition(sf::Vector2f position);
	GUI_API sf::Vector2f getPosition();
	GUI_API void draw(sf::RenderWindow& window) override;

private:
	void handleUpdateSettings() override;
	sf::Text m_text;
};

using Label_ptr = std::unique_ptr<KOD::GUI::Label>;

} // namespace GUI
} // namespace KOD
