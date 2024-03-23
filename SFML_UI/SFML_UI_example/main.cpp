#include <Buttom.h>
#include <Gui.h>
#include <Label.h>
#include <SFML/Graphics.hpp>
#include <Settings.h>
#include <iostream>

int main()
{
	sf::RenderWindow window{sf::VideoMode{800, 600}, "GUI-SFML Example"};

	sf::Font font;
	font.loadFromFile("Prototype.ttf");

	KOD::GUI::Settings s(font);
	s.m_textColor = sf::Color::Blue;
	s.m_innerColor = sf::Color::Red;

	KOD::GUI::Gui gui(window, s);

	KOD::GUI::Label_ptr label = std::make_unique<KOD::GUI::Label>("STR");
	label->setPosition({100, 100});

	KOD::GUI::Buttom_ptr buttom = std::make_unique<KOD::GUI::Buttom>("Buttom");
	buttom->setPosition({200, 100});
	buttom->setOnClickCallback(KOD::GUI::Callable([&gui, labelUid = label->getUid()]() { gui.removeElement(labelUid); }));

	gui.addElement(std::move(label));
	gui.addElement(std::move(buttom));

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();
			gui.handle(event);
		}

		window.clear(sf::Color(120, 120, 120));

		gui.draw();

		window.display();
	}

	return 0;
}