#include "../include/Q3.h"

#include <iostream>

Q3::Q3()
{
}

void Q3::answer(const std::string & filepath, const std::string & outputFilepath)
{
	// Open and read the file
	std::ifstream file(filepath);

	std::string text = "";
	std::string output = "";

	while (file >> text)
	{
		// If text is not separator
		if (text.compare("========") != 0)
		{
			output += text + "\n";
			manipulateString(text, output);
			output += "\n";
		}
	}

	write(outputFilepath, output);
}

void Q3::manipulateString(std::string& str, std::string& output)
{
	// "Walk" the string
	for (int i = 0; i < str.length(); i++)
	{
		// Keep track of how many open brackets we'd seen
		int counter = 0;

		if (str[i] == '(') // If current character is an open bracket
		{
			// Walk the string to find matching bracket
			for (int j = i + 1; j < str.length(); j++)
			{
				if (str[j] == '(') // If we see another open bracket
				{
					counter++; // Increase counter
				}
				else if (str[j] == ')' && counter > 0) // If we see a closing bracket, but we had seen more open brackets before
				{
					counter = 0; // Reset counter
					break; // Break the loop
							// By using 'break', the program removes innermost brackets. Use 'continue' to remove outermost brackets instead.
				}
				else if (str[j] == ')' && counter == 0) // If we see a closing bracket and we hadn't seen any open bracket, we have a match
				{
					// Erase brackets
					str.erase(i, 1);
					str.erase(j - 1, 1);

					// Add to output
					output += str + "\n";

					// Continue recursively
					manipulateString(str, output);
				}
			}
		}
	}
}

void Q3::write(const std::string & filepath, const std::string & str)
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