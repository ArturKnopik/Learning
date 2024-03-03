#pragma once

#include "StateManager.h"
#include "export.h"
#include "StateManager.h"

#include <memory>

namespace KOD {
namespace GSM {

class IState
{
public:
	KOD_GSM_DLL IState() = delete;
	KOD_GSM_DLL IState(KOD::GSM::StateManager &stateManager);
	KOD_GSM_DLL virtual ~IState();
	
	KOD_GSM_DLL virtual void draw() = 0;
	KOD_GSM_DLL virtual void update(const size_t dt) = 0;
	KOD_GSM_DLL virtual void input() = 0;

private:
protected:
	KOD::GSM::StateManager &m_gameStateManager;
};

} // namespace GSM
} // namespace KOD