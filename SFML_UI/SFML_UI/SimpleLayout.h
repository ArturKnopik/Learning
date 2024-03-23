#pragma once
#include "Layout_Base.h"
#include "UiElementHolder.h"

namespace KOD {
namespace GUI {

class SimpleLayout : public KOD::GUI::Layout_Base
{
public:
	GUI_API SimpleLayout(const sf::RenderWindow& window);

	GUI_API void handleEvent(const sf::Event& event) override;
	GUI_API void draw(sf::RenderWindow& window) override;
	GUI_API void onMousePressed(float x, float y) override;

private:
	// for mouse position related to window
	const sf::RenderWindow& m_window;
};

} // namespace GUI
} // namespace KOD