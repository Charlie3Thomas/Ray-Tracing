#pragma once
#include <chrono>
#include <string>
#include <iostream>

class timer
{
public:
	timer(std::string str)
		:s(str)
	{
		start_time = std::chrono::system_clock::now();
		std::cout
			<< s
			<< " -> "
			<< "Timer started..."
			<< std::endl;
	}

	~timer()
	{
		end_time = std::chrono::system_clock::now();
		std::chrono::duration<double> diff = end_time - start_time;
		std::cout
			<< "Timer "
			<< s
			<< " took "
			<< diff
			<< " to complete."
			<< std::endl;
	}

private:
	std::chrono::system_clock::time_point start_time;
	std::chrono::system_clock::time_point end_time;
	std::string s;
};