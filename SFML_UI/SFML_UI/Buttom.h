#pragma once
#include "Callable.h"
#include "Label.h"

#include <SFML/Graphics/RectangleShape.hpp>

namespace KOD {
namespace GUI {

class Buttom : public KOD::GUI::Label
{
public:
	GUI_API Buttom(const char* text);
	GUI_API void setPosition(sf::Vector2f position);
	GUI_API void setRectColor(sf::Color color);
	GUI_API void draw(sf::RenderWindow& window) override;
	GUI_API void handleUpdateSettings() override;
	GUI_API void setOnClickCallback(KOD::GUI::Callable callback);
	GUI_API void onMousePressed(float x, float y) override;

private:
	void updateLabelPosition();

	sf::RectangleShape m_rectangle;
	KOD::GUI::Callable m_callable;
};

using Buttom_ptr = std::unique_ptr<KOD::GUI::Buttom>;

} // namespace GUI
} // namespace KOD
