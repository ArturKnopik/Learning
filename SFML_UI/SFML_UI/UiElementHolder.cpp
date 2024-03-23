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

bool compareUid(size_t elementUid, size_t searchingUid) { return elementUid == searchingUid; }

void KOD::GUI::UiElementHolder::removeUiElement(size_t uid)
{
	size_t index = 0;
	bool found = false;

	for (size_t i = 0; i < m_uiElements.size(); ++i) {
		if (compareUid(m_uiElements[i]->getUid(), uid)) {
			index = i;
			found = true;
		}
	}

	if (found) {
		m_uiElements.erase(m_uiElements.begin() + index);
	}
}

std::vector<std::unique_ptr<KOD::GUI::UiElement>>& KOD::GUI::UiElementHolder::getUiElements() { return m_uiElements; }
