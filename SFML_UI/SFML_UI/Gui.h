#pragma once
#include "Layout_Base.h"
#include "Settings.h"
#include "SimpleLayout.h"
#include "export.h"

#include <memory>

namespace KOD {
namespace GUI {

class Gui
{
public:
	GUI_API Gui(sf::RenderWindow &window, KOD::GUI::Settings settings);
	GUI_API void handle(const sf::Event &event);
	GUI_API void draw();
	GUI_API void addElement(std::unique_ptr<UiElement> element);
	GUI_API void removeElement(size_t uid);

private:
	GUI_API Gui();
	KOD::GUI::Settings m_settings;
	std::unique_ptr<Layout_Base> m_layout;
	sf::RenderWindow &m_window;

	friend class KOD::GUI::UiElement;
};

} // namespace GUI
} // namespace KOD
