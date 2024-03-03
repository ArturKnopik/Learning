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