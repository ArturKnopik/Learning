#pragma once
#include <thread>
#include <atomic>

enum ThreadState {
	THREAD_STATE_RUNNING,
	THREAD_STATE_CLOSING,
	THREAD_STATE_TERMINATED,
};

template <typename Derived>
class ThreadHolder
{
public:
	ThreadHolder() {}
	void start() {
		setState(THREAD_STATE_RUNNING);
		m_thread = std::thread(&Derived::threadMain, static_cast<Derived*>(this));
	}

	void stop() {
		setState(THREAD_STATE_CLOSING);
	}

	void join() {
		if (m_thread.joinable()) {
			m_thread.join();
		}
	}

protected:
	void setState(ThreadState newState) {
		m_threadState.store(newState);
	}

	ThreadState getState() const {
		return m_threadState.load();
	}

private:
	std::atomic<ThreadState> m_threadState{ THREAD_STATE_TERMINATED };
	std::thread m_thread;
};