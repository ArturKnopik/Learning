#pragma once
#include <vector>
#include <mutex>
#include "ThreadHolderBase.h"
#include "Task.h"

class Dispatcher : public ThreadHolder<Dispatcher>
{
public:
	Dispatcher();

	void threadMain();

	void addTask(Task task);

	void stop();
private:
	std::mutex mutex;
	std::condition_variable signal;
	std::vector<Task> taskList;
};

