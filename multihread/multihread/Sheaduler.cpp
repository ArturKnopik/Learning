#include "Sheaduler.h"
#include <iostream>
#include <syncstream>

using time_stamp = std::chrono::time_point<std::chrono::system_clock,
	std::chrono::microseconds>;

constexpr uint8_t THREAD_SLEEP_TIME = 50;

Scheduler::Scheduler(Dispatcher& dispatcher)
	:dispather(dispatcher) {
}

void Scheduler::stop()
{
	removeAllTasks();
	ThreadHolder::stop();
}

void Scheduler::threadMainLoop()
{
	std::unique_lock<std::mutex> uniqueLock(sheadulerMutex, std::defer_lock);
	while (getState() == ThreadState::THREAD_STATE_RUNNING)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(THREAD_SLEEP_TIME));
		uniqueLock.lock();
		while (!sheaduledTasks.empty())
		{
			if (sheaduledTasks.top().timeout < getEpochTime())
			{
				dispather.addTask(std::move(sheaduledTasks.top().task));
				sheaduledTasks.pop();
			}
			else
			{
				break;
			}
		}

		uniqueLock.unlock();
	}
}

void Scheduler::removeAllTasks()
{
	std::lock_guard<std::mutex> lock(sheadulerMutex);
	while (!sheaduledTasks.empty())
	{
		sheaduledTasks.pop();
	}
}

void Scheduler::addSheaduledTask(TaskFunc taskFunc, size_t timeout)
{
	std::lock_guard<std::mutex> lock(sheadulerMutex);
	if (getState() != THREAD_STATE_RUNNING)
	{
		return;
	}
	sheaduledTasks.push(SheaduledTask(Task(std::move(taskFunc)), getEpochTime() + timeout));

}

uint64_t Scheduler::getEpochTime()
{
	auto timepoint = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(timepoint.time_since_epoch()).count();
}
