#include "gtest/gtest.h"
#include <KOD/GSM/StateManager.h>
#include <KOD/GSM/IState.h>

static bool isDrawCalled = false;
static bool isUpdateCalled = false;
static bool isInputCalled = false;

static void resetVariables()
{
	isDrawCalled = false;
	isUpdateCalled = false;
	isInputCalled = false;
}

class UtState : public KOD::GSM::IState
{
public:
	UtState() = delete;
	UtState(KOD::GSM::StateManager& stateManager) : IState(stateManager) {}

	void draw() override { isDrawCalled = true; }
	void update(const size_t dt) override { isUpdateCalled = true; }
	void input() override { isInputCalled = true; }
};

// TESTS

TEST(StateManager, StateManager_StateManager) {
	KOD::GSM::StateManager sm;
}

TEST(StateManager, StateManager_pushState_sanity) {
	KOD::GSM::StateManager sm;
	std::shared_ptr<UtState> utState = std::make_shared<UtState>(sm);
	sm.pushState(utState);
	EXPECT_EQ(sm.currentState(), utState);
}

TEST(StateManager, StateManager_pushState_nullptr) {
	KOD::GSM::StateManager sm;
	sm.pushState(nullptr);
	EXPECT_EQ(sm.currentState(), nullptr);
}

TEST(StateManager, StateManager_popState_sanity) {
	KOD::GSM::StateManager sm;
	std::shared_ptr<UtState> utState1 = std::make_shared<UtState>(sm);
	std::shared_ptr<UtState> utState2 = std::make_shared<UtState>(sm);
	sm.pushState(utState1);
	sm.pushState(utState2);
	EXPECT_EQ(sm.currentState(), utState2);
	sm.popState();
	EXPECT_EQ(sm.currentState(), utState1);
}

TEST(StateManager, StateManager_popState_noStateInList) {
	KOD::GSM::StateManager sm;
	std::shared_ptr<UtState> utState1 = std::make_shared<UtState>(sm);
	std::shared_ptr<UtState> utState2 = std::make_shared<UtState>(sm);
	sm.pushState(utState1);
	sm.pushState(utState2);
	EXPECT_EQ(sm.currentState(), utState2);
	sm.popState();
	EXPECT_EQ(sm.currentState(), utState1);
	sm.popState();
	EXPECT_EQ(sm.currentState(), nullptr);
	sm.popState();
	EXPECT_EQ(sm.currentState(), nullptr);
}

TEST(StateManager, StateManager_currentState_sanity) {
	KOD::GSM::StateManager sm;
	std::shared_ptr<UtState> utState = std::make_shared<UtState>(sm);
	sm.pushState(utState);
	EXPECT_EQ(sm.currentState(), utState);
}

TEST(StateManager, StateManager_currentState_nullptr) {
	KOD::GSM::StateManager sm;
	EXPECT_EQ(sm.currentState(), nullptr);
}

TEST(StateManager, StateManager_handle_sanity) {
	KOD::GSM::StateManager sm;
	std::shared_ptr<UtState> utState = std::make_shared<UtState>(sm);
	sm.pushState(utState);
	sm.handle();
	EXPECT_EQ(sm.currentState(), utState);
}

TEST(StateManager, StateManager_handle_noState) {
	KOD::GSM::StateManager sm;
	sm.handle();
	// no crash
}

TEST(StateManager, StateManager_handle_getDt) {
	KOD::GSM::StateManager sm;
	std::shared_ptr<UtState> utState = std::make_shared<UtState>(sm);
	sm.pushState(utState);
	sm.handle();
	EXPECT_NE(sm.getDt(), 0);
}


