#pragma once

#include"ThreadHolderBase.h"
#include "Dispather.h"
#include <queue>

struct SheaduledTask
{
	Task task;
	size_t timeout;
};

struct Compare
{
	bool operator()(const SheaduledTask l, const SheaduledTask r) const { return l.timeout > r.timeout; }
};

class Scheduler : public ThreadHolder<Scheduler>
{
public:
	Scheduler() = delete;

	Scheduler(Dispatcher& dispather);

	void threadMainLoop();

	void addSheaduledTask(TaskFunc taskFunc, size_t timeout);

	void stop();
private:
	void removeAllTasks();

	uint64_t getEpochTime();

	std::mutex sheadulerMutex;
	std::priority_queue<SheaduledTask, std::vector<SheaduledTask>, Compare> sheaduledTasks;
	Dispatcher& dispather;
};

