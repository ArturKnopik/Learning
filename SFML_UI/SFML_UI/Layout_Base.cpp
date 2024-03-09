#include "Layout_Base.h"

#include <SFML/Graphics/RenderWindow.hpp>

KOD::GUI::Layout_Base::Layout_Base() {}

KOD::GUI::Layout_Base::~Layout_Base() {}

void KOD::GUI::Layout_Base::handleEvent(sf::Event& event) {}

void KOD::GUI::Layout_Base::draw(sf::RenderWindow& window) {}

void KOD::GUI::Layout_Base::onMouseEnter() {}

void KOD::GUI::Layout_Base::onMouseLeave() {}

void KOD::GUI::Layout_Base::onMouseMoved(float x, float y) {}

void KOD::GUI::Layout_Base::onMousePressed(float x, float y) {}

void KOD::GUI::Layout_Base::onMouseReleased(float x, float y) {}

void KOD::GUI::Layout_Base::onMouseWheelMoved() {}
