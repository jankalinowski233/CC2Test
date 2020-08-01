#include "../include/Q2.h"
#include <algorithm>

Q2::Q2()
{
}

void Q2::answer(const std::string & filepath, const std::string & outputFilepath)
{
	// Open and init file
	std::ifstream file(filepath);

	std::vector<int> lengths;
	std::string outputText;
	std::string separator = "========";
	std::string text = "";

	// Init data
	int distance, numWires;

	// Read file
	while (file >> text)
	{
		file >> distance;
		distance *= CM2NM; // convert distance to NM

		// Number of wires available
		file >> numWires;

		// "Feed" vector
		lengths.reserve(lengths.size() + numWires);

		for (int i = 0, temp; i < numWires; i++)
		{
			file >> temp;
			lengths.push_back(temp);
		}

		// Calculate if distance can be covered
		processData(distance, lengths, outputText);
		lengths.clear();
	}

	write(outputFilepath, outputText);
}

void Q2::processData(int distToCover, std::vector<int>& data, std::string & output)
{
	// Init variables
	std::pair<int, int> pair = std::pair<int, int>(0, 0);
	int maxValue = INT_MIN;
	int abs = maxValue;

	// Compare each element to other elements
	for (int i = 0; i < data.size(); i++)
	{
		for (int j = i + 1; j < data.size(); j++)
		{
			// If their sum covers the distance
			if (data[i] + data[j] == distToCover)
			{
				// Read lower and higher value
				int lower = std::min(data[i], data[j]);
				int higher = std::max(data[i], data[j]);

				// Calculate absolute value of L1 - L2
				int temp = lower - higher;
				abs = std::abs(temp);

				if (abs > maxValue)
				{
					// "Feed" result
					pair = std::make_pair(lower, higher);
					maxValue = abs;
				}
			}
		}
	}

	// Output
	if (pair.first != 0 && pair.second != 0)
	{
		output += "yes " + std::to_string(pair.first) + " " + std::to_string(pair.second) + "\n";
	}
	else
	{
		output += "danger\n";
	}
}

void Q2::write(const std::string& filepath, const std::string& str)
{
	// Write to file
	std::ofstream file(filepath);
	file.clear();

	if (file.is_open())
	{
		file << str;
	}

	file.close();
}
