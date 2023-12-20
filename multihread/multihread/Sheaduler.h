#pragma once

#include"ThreadHolderBase.h"
#include "Dispather.h"

struct SheaduledTask
{
	Task task;
	size_t timeout;
};

class Scheduler : public ThreadHolder<Scheduler>
{
public:
	Scheduler() = delete;

	Scheduler(Dispatcher& dispather);

	void threadMain();

	void addSheaduledTask(TaskFunc taskFunc, size_t timeout);

	void stop();
private:
	void removeAllTasks();

	uint64_t getEpochTime();

	std::mutex sheadulerMutex;
	std::vector<SheaduledTask> sheaduledTasks;
	Dispatcher& dispather;
};

