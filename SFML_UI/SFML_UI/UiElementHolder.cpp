#include "UiElementHolder.h"

KOD::GUI::UiElementHolder::UiElementHolder() {}

void KOD::GUI::UiElementHolder::addUiElement(std::unique_ptr<KOD::GUI::UiElement> element)
{
	if (!element) {
		return;
	}

	auto el = std::find(m_uiElements.begin(), m_uiElements.end(), element);
	if (el != m_uiElements.end()) {
		return;
	}

	m_uiElements.push_back(std::move(element));
}

void KOD::GUI::UiElementHolder::removeUiElement(std::unique_ptr<KOD::GUI::UiElement> element)
{
    auto el = std::find(m_uiElements.begin(), m_uiElements.end(), element);
    if (el == m_uiElements.end()) {
        return;
    }
    m_uiElements.erase(el);
}

std::vector<std::unique_ptr<KOD::GUI::UiElement>>& KOD::GUI::UiElementHolder::getUiElements() { return m_uiElements; }