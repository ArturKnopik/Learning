#include "Task.h"

#include <iostream>
#include <mutex>
#include <syncstream>

Task::Task(TaskFunc&& task)
{
	this->task = std::move(task);
	id = g_id.load();
	g_id.store(++id);
	std::osyncstream(std::cout) << "TASK: " << id << "\n";
}

void Task::execute()
{
	if (task) {
		std::osyncstream(std::cout) << "Executing task, id: " << id << "\n";
		task();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}
}

size_t Task::getId()
{
	return id;
}
