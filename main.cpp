#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <chrono>
#include <fstream>

#include "file_writer.h"

using namespace std::chrono_literals;

std::atomic<bool> should_run = true;
std::atomic<bool> domain_ready = false;

std::queue<int> channel{};
std::condition_variable cv;
std::mutex mut;

void packet_capture(void) {
	int id = 0;

	std::cout << "[packet_capture] starting..." << std::endl;

	while (should_run) {
		{
			const std::lock_guard<std::mutex> lck(mut);
			channel.push(id);
			domain_ready = true;
			std::cout << "[packet_capture] sent " << id << " to channel\n";
		}

		cv.notify_all();

		std::this_thread::sleep_for(3s);
		id++;
	}

	cv.notify_all();
	std::cout << "[packet_capture] exiting..." << std::endl;
}

void domain_handler(void) {
	int id;

	std::cout << "[domain_handler] starting..." << std::endl;

	while (should_run) {
		std::unique_lock<std::mutex> lck(mut);

		cv.wait(lck, []
			{ return domain_ready == true || !should_run; });

		if (!should_run) {
			break;
		}

		domain_ready = false;

		if (!channel.empty())
		{
			id = channel.front();
			std::cout << "[domain_handler] got " << id << " from channel\n";
			channel.pop();
		}
	}

	std::cout << "[domain_handler] exiting..." << std::endl;
}

void logger(void)
{
	auto writer = FileWriter::create("log.txt");

	if (!writer){
		should_run = false;
		return;
	}

	while (should_run) {
		writer->write_line("ffffff");
		std::this_thread::sleep_for(5s);
	}
}

void some(void) {
	std::this_thread::sleep_for(5s);
	should_run = false;
}

int main(void) {
	std::thread t1(packet_capture);
	std::thread t2(domain_handler);
	std::thread t3(some);
	std::thread t4(logger);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
}