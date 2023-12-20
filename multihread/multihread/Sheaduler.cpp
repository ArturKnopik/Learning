#include "Sheaduler.h"
#include <iostream>
#include <syncstream>

using time_stamp = std::chrono::time_point<std::chrono::system_clock,
	std::chrono::microseconds>;

constexpr uint8_t THREAD_SLEEP_TIME = 50;

Scheduler::Scheduler(Dispatcher& dispatcher)
	:dispather(dispatcher) {
	sheaduledTasks.reserve(1000);
}

void Scheduler::stop()
{
	removeAllTasks();
	//std::osyncstream(std::cout) << "Scheduler::stop(): stoping...\n";
	ThreadHolder::stop();
}

void Scheduler::threadMain()
{
	std::unique_lock<std::mutex> uniqueLock(sheadulerMutex, std::defer_lock);
	while (getState() == ThreadState::THREAD_STATE_RUNNING)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME));
		// remove expired task at the begining
		uniqueLock.lock();
		for (auto it = sheaduledTasks.begin(); it != sheaduledTasks.end();)
		{
			if (it->timeout < getEpochTime())
			{
				//std::osyncstream(std::cout) << "Scheduler::threadMain(): moving task to dispatcher...\n";
				dispather.addTask(std::move(it->task));
				it = sheaduledTasks.erase(it);
			}
			else
			{
				++it;
			}
		}

		uniqueLock.unlock();
	}
}

void Scheduler::removeAllTasks()
{
	std::lock_guard<std::mutex> lock(sheadulerMutex);
	sheaduledTasks.clear();
}

void Scheduler::addSheaduledTask(TaskFunc taskFunc, size_t timeout)
{
	std::lock_guard<std::mutex> lock(sheadulerMutex);
	if (getState() != THREAD_STATE_RUNNING)
	{
		return;
	}
	//std::osyncstream(std::cout) << "Scheduler::addSheaduledTask: adding task, current time" << getEpochTime() << ", timeout " << getEpochTime() + timeout << "\n";
	sheaduledTasks.push_back(SheaduledTask(Task(std::move(taskFunc)), getEpochTime() + timeout));

}

uint64_t Scheduler::getEpochTime()
{
	auto timepoint = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(timepoint.time_since_epoch()).count();
}
