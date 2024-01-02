#include "Dispather.h"
#include <iostream>
#include <syncstream>


void Dispatcher::threadMainLoop()
{
	std::vector<Task> taskListSwap;

	std::unique_lock<std::mutex> uniqueLock(mutex, std::defer_lock);

	while (getState() == ThreadState::THREAD_STATE_RUNNING)
	{
		uniqueLock.lock();

		if (taskList.empty())
		{
			signal.wait(uniqueLock);
		}

		std::swap(taskListSwap, taskList);
		uniqueLock.unlock();
		std::osyncstream(std::cout) << "Dispatcher::threadMain: executing "<< taskListSwap.size() << " tasks\n";
		for (auto& task : taskListSwap)
		{
			task.execute();
		}
		taskListSwap.clear();
	}
}

void Dispatcher::addTask(Task task)
{
	bool do_signal = false;

	mutex.lock();
	if (getState() == THREAD_STATE_RUNNING)
	{
		do_signal = taskList.empty();
		taskList.push_back(std::move(task));
		mutex.unlock();

		if (do_signal) {
			signal.notify_one();
		}
	}
}

void Dispatcher::stop()
{
	if (getState() == THREAD_STATE_RUNNING)
	{
		addTask(Task([this]() {
			ThreadHolder::stop();
			std::osyncstream(std::cout) << "Dispatcher::stop: stoping...\n";
			}));
	}
}
