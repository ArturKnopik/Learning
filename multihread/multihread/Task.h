#pragma once

#include <functional>
#include <atomic>

using TaskFunc = std::function<void(void)>;

static std::atomic<size_t> g_id = 0;

class Task {
public:
	Task() = delete;
	~Task() = default;
	Task(TaskFunc&& task);
	void execute();
	size_t getId();
private:
	std::function<void(void)> task;
	size_t id;
};