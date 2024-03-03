
# GameStateManagerDLL
GameStateManagerDLL is a dynamic-link library (DLL) that offers a basic state manager for game engine development.

This library aims to simplify the management of different states within a game, such as menus, gameplay, settings, etc. It provides functionalities to push, pop, and handle states, allowing developers to focus on implementing individual game states without worrying about the state management logic.

Key features:

* State pushing and popping: Easily switch between different states during runtime.
* State handling: Update and draw the current state based on the elapsed time.
* Flexible integration: Can be integrated into various game engines and frameworks.

GameStateManagerDLL serves as a foundational tool for organizing game logic into distinct states, improving code organization and maintainability in game development projects.

# Projects

#### GameStateManagerDLL
This project contains the DLL library for managing game states.

#### GameStateManagerExample
An example project demonstrating the usage of the GameStateManagerDLL library.

#### GameStateDllUTests
A project containing unit tests for the GameStateManagerDLL library.

# Usage

```cpp
#include <KOD/GSM/IState.h>
#include <KOD/GSM/StateManager.h>
#include <iostream>

class ExampleState : public KOD::GSM::IState
{
public:
	ExampleState() = delete;
	ExampleState(KOD::GSM::StateManager& stateManager) : IState(stateManager) {}

	void draw() override { std::cout << "ExampleState::draw" << std::endl; }
	void update(const size_t dt) override { std::cout << "ExampleState::update " << dt << std::endl; }
	void input() override { std::cout << "ExampleState::input" << std::endl; }
};

class AnotherExampleState : public KOD::GSM::IState
{
public:
	AnotherExampleState() = delete;
	AnotherExampleState(KOD::GSM::StateManager stateManager) : IState(stateManager) {}

	void draw() override { std::cout << "AnotherExampleState::draw" << std::endl; }
	void update(const size_t dt) override { std::cout << "AnotherExampleState::update " << dt << std::endl; }
	void input() override { std::cout << "AnotherExampleState::input" << std::endl; }
};

int main()
{
	KOD::GSM::StateManager sm;

	sm.pushState(std::make_shared<ExampleState>(sm));
	sm.handle();
	sm.pushState(std::make_shared<AnotherExampleState>(sm));
	sm.handle();
	sm.popState();
	sm.handle();
	sm.popState();
	sm.handle();
}
```

# Output
```
ExampleState::input
ExampleState::draw
ExampleState::update 12700
AnotherExampleState::input
AnotherExampleState::draw
AnotherExampleState::update 8600
ExampleState::input
ExampleState::draw
ExampleState::update 1600
KOD::GSM::StateManager::handle: invalid state
```