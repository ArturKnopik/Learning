#pragma once
#include "BoundingBox.h"
#include "UiElement.h"

#include <memory>
#include <vector>
namespace KOD {
namespace GUI {

class UiElementHolder
{
public:
	UiElementHolder();
	void addUiElement(std::unique_ptr<KOD::GUI::UiElement> uiElement);
	void removeUiElement(size_t uid);
	std::vector<std::unique_ptr<KOD::GUI::UiElement>> &getUiElements();

public:
	std::vector<std::unique_ptr<UiElement>> m_uiElements;
};

} // namespace GUI
} // namespace KOD
