#pragma once
#include "Layout_Base.h"
#include "UiElementHolder.h"

namespace KOD {
namespace GUI {

class SimpleLayout : public KOD::GUI::Layout_Base
{
public:
	GUI_API SimpleLayout();

	GUI_API void handleEvent(sf::Event& event) override;
	GUI_API void draw(sf::RenderWindow& window) override;

private:
};

} // namespace GUI
} // namespace KOD