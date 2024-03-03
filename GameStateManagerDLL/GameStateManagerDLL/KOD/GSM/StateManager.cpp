#include "StateManager.h"

#include "IState.h"
#include <iostream>

KOD::GSM::StateManager::StateManager() {
	start = std::chrono::steady_clock::now();
	end = std::chrono::steady_clock::now();
}

KOD::GSM::StateManager::~StateManager() {}

void KOD::GSM::StateManager::pushState(std::shared_ptr<IState> state)
{
	if (state) {
		m_states.push_back(state);
	}
}

void KOD::GSM::StateManager::popState()
{
	if (!m_states.empty()) {
		m_states.pop_back();
	}
}

std::shared_ptr<KOD::GSM::IState> KOD::GSM::StateManager::currentState()
{
	if (!m_states.empty()) {
		return m_states.back();
	}
	return nullptr;
}

void KOD::GSM::StateManager::handle()
{
	end = std::chrono::steady_clock::now();
	size_t dt = static_cast<size_t>((end - start).count());

	if (currentState()) {
		currentState()->input();
		currentState()->draw();
		currentState()->update(dt);
	} else {
		std::cerr << "KOD::GSM::StateManager::handle: invalid state" << std::endl;
	}
	start = std::chrono::steady_clock::now();
}

KOD_GSM_DLL size_t KOD::GSM::StateManager::getDt() { return static_cast<size_t>((end - start).count()); }
