#include "Task.h"

#include <iostream>
#include <mutex>
#include <syncstream>

Task::Task(TaskFunc&& task)
{
	this->task = std::move(task);
	id = g_id.load();
	g_id.store(++id);
}

void Task::execute()
{
	if (task) {
		task();
	}
}

size_t Task::getId()
{
	return id;
}
