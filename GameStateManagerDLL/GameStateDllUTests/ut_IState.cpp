#include "gtest/gtest.h"
#include <KOD/GSM/IState.h>

class UtState : public KOD::GSM::IState
{
public:
	UtState() = delete;
	UtState(KOD::GSM::StateManager& stateManager) : IState(stateManager) {}

	void draw() override { }
	void update(const size_t dt) override {  }
	void input() override { }
	// helper function
	KOD::GSM::StateManager& getStateManager() {
		return m_gameStateManager;
	};
};

// TESTS

TEST(IState, IState_IState) {
	KOD::GSM::StateManager sm;
	UtState utState(sm);
	EXPECT_EQ(&utState.getStateManager(), &sm);
}
