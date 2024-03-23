#pragma once
#include "BoundingBox.h"
#include "Settings.h"

#include <SFML/Graphics/RenderWindow.hpp>
#include <functional>

namespace KOD {
namespace GUI {

class UiElement
{
public:
	UiElement();
	void setSettings(KOD::GUI::Settings settings);
	virtual void draw(sf::RenderWindow &window);
	GUI_API size_t getUid();

	virtual void onMouseEnter();
	virtual void onMouseLeave();
	virtual void onMouseMoved(float x, float y);
	virtual void onMousePressed(float x, float y);
	virtual void onMouseReleased(float x, float y);
	virtual void onMouseWheelMoved();

protected:
	virtual void handleUpdateSettings();
	KOD::GUI::Settings m_settings;

private:
	static size_t s_uid;
	bool m_isCustomSettings = false;
	size_t m_uid = 0;

	friend class KOD::GUI::Gui;
};

class UiElementCompareFunction
{
public:
	bool operator()(UiElement element, size_t uid) const { return element.getUid() == uid; }
};

using UiElement_ptr = std::unique_ptr<KOD::GUI::UiElement>;

} // namespace GUI
} // namespace KOD
