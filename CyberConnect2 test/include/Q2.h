#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define NM2CM 1e-7
#define CM2NM 10000000

class Q2
{
private:

public:
	Q2();
	void answer(const std::string& filepath, const std::string& outputFilepath);
	void processData(int distToCover, std::vector<int>& data, std::string & output);
	void write(const std::string& filepath, const std::string& str);

};