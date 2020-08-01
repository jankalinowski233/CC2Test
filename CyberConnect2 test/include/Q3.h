#pragma once

#include <string>
#include <fstream>

class Q3
{
private:

public:
	Q3();
	void answer(const std::string& filepath, const std::string& outputFilepath);
	void manipulateString(std::string& str, std::string& output);
	void write(const std::string& filepath, const std::string& str);
};