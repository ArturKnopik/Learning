#pragma once
#include <SFML/System/Vector2.hpp>

namespace KOD {
namespace GUI {

struct BoundingBox
{
	sf::Vector2f m_position = {0, 0};
	sf::Vector2f m_size = {0, 0};
};

} // namespace GUI
} // namespace KOD