#pragma once
#include "export.h"
#include "UiElementHolder.h"

#include <SFML/Graphics/RenderWindow.hpp>

namespace KOD {
namespace GUI {

class Layout_Base : public KOD::GUI::UiElementHolder
{
public:
	GUI_API Layout_Base();
	GUI_API virtual ~Layout_Base();

	GUI_API virtual void handleEvent(sf::Event& event);

	GUI_API virtual void draw(sf::RenderWindow& window);
	GUI_API virtual void onMouseEnter();
	GUI_API virtual void onMouseLeave();
	GUI_API virtual void onMouseMoved(float x, float y);
	GUI_API virtual void onMousePressed(float x, float y);
	GUI_API virtual void onMouseReleased(float x, float y);
	GUI_API virtual void onMouseWheelMoved();
};

} // namespace GUI
} // namespace KOD
