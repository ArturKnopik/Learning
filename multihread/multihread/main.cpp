#include <iostream>
#include "Dispather.h"
#include "Sheaduler.h"
#include <chrono>
#include <thread>
#include <syncstream>
#include <cstdlib>


constexpr size_t REPEAT = 500;
constexpr size_t THREAD_COUNT = 5;

Dispatcher g_dispatcher;
Scheduler g_scheduler(g_dispatcher);

void addTasksToDispatcher()
{
	//for (size_t i = 0; i < REPEAT; i++)
	while (true)
	{
		g_dispatcher.addTask(Task([]() {
			std::osyncstream(std::cout) << "## Dispatcher Task\n";
			}
		));
	}
}

void addTasksToSheaduler()
{
	//for (size_t i = 0; i < REPEAT; i++)
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 50));
		g_scheduler.addSheaduledTask([]()
			{

				std::osyncstream(std::cout) << "## Scheduler Task\n";
			}, 3000);
	}
}

int main()
{
	srand((unsigned)time(NULL));
	// Testing code
	size_t x = 5;

	g_dispatcher.start();
	g_scheduler.start();

	std::cout << "DISPATCHER" << std::endl;;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	g_dispatcher.addTask(Task([]() { std::cout << "Dispatcher Some Task 1..." << std::endl; }));
	g_dispatcher.addTask(Task([x]() { std::cout << "Dispatcher Some Task 2..." << x << std::endl; }));
	g_dispatcher.addTask(Task([x]() { std::cout << "Dispatcher Some Task 3..." << x << std::endl; }));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "Add " << REPEAT << " tasks to dispather" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	std::thread threads[10];

	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		//threads[i] = std::thread(addTasksToDispatcher);
	}

	for (size_t i = 0; i < THREAD_COUNT; i++)
	{
		//threads[i].join();
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::cout << "SHEADULER" << std::endl;
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	{
		std::cout << "SHEADULER 2 " << std::endl;
		for (size_t i = 0; i < THREAD_COUNT; i++)
		{
			threads[i] = std::thread(addTasksToSheaduler);
		}

		for (size_t i = 0; i < THREAD_COUNT; i++)
		{
			threads[i].join();
		}
	}
	std::cout << "FIN!\n";

	std::this_thread::sleep_for(std::chrono::milliseconds(30000));
	std::cout << "Stop Dispather Thread!\n";

	g_scheduler.stop();
	std::cout << "Stop sheaduler Thread!\n";
	g_dispatcher.stop();

	g_scheduler.join();
	g_dispatcher.join();
}
