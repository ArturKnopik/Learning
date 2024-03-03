#pragma once
#include "export.h"

#include <chrono>
#include <memory>
#include <vector>

namespace KOD {
namespace GSM {

class IState;

class StateManager
{
public:
	KOD_GSM_DLL StateManager();
	KOD_GSM_DLL virtual ~StateManager();
	
	KOD_GSM_DLL void pushState(std::shared_ptr<IState> state);
	KOD_GSM_DLL void popState();
	KOD_GSM_DLL std::shared_ptr<IState> currentState();
	KOD_GSM_DLL virtual void handle();
	KOD_GSM_DLL size_t getDt();

private:
	std::vector<std::shared_ptr<IState>> m_states;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
};
} // namespace GSM
} // namespace KOD