#include "IState.h"

#include <iostream>

KOD::GSM::IState::IState(KOD::GSM::StateManager &stateManager) : m_gameStateManager(stateManager) {}

KOD::GSM::IState::~IState() = default;
