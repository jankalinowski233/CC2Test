#pragma once

#include <string>
#include <fstream>

class Q1
{
private:

public:
	Q1();
	void answer(const std::string& filepath, const std::string& outputFilepath);
	void calculate(std::string& first, std::string& second, const std::string& operation);

	int add(int f, int s);
	int subtract(int f, int s);
	int multiply(int f, int s);
	int* split(int total);

	void write(const std::string& filepath, const std::string& str);
};