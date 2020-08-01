#include "../include/Q1.h"

// ATTEMPT //
// Due to the constraints (not assigning numbers to usual data types & simply because the numbers are too big to
// deal with in the usual manner), the idea here was to perform column addition/subtraction/multiplication
// by walking both string from the end to the beginning. I ran out of time and therefore I was unable to complete
// the algorithm. It would also require some further refining, such as moving check for an operator to answer function,
// rather than checking it with every iteration in for loop, as well as splitting possible operations (addition, subtraction,
// multiplication) into separate functions.

#include <iostream>
#include <vector>
#include <algorithm>

Q1::Q1()
{
}

void Q1::answer(const std::string & filepath, const std::string & outputFilepath)
{
	// Open and read file
	std::ifstream file(filepath);

	std::string text;
	std::string answer;

	while (file >> text)
	{
		if (text.compare("========") != 0)
		{
			std::string f, s, op;

			f = text;
			file >> s;
			file >> op;
			
			calculate(f, s, op);
		}
	}

	write(outputFilepath, answer);
}

void Q1::calculate(std::string& first, std::string& second, const std::string& operation)
{
	std::string strResult; // Init output result

	// Check which string is longer
	int max = std::max(first.length(), second.length());
	int min = std::min(first.length(), second.length());
	int difference = max - min;

	// Append strings accordingly. Due to the fact I have to walk both strings, and that I incorporated a column addition approach,
	// I simply add zeroes in front of all the other digits in a shorter string. That way I don't get an exception of subscript
	// being out of range and it doesn't affect final result.
	if (first.length() > second.length())
	{
		second.insert(1, difference, '0');
	}
	else
	{
		first.insert(1, difference, '0');
	}

	// Init some data
	char op1 = first[0];
	char op2 = second[0];
	int remainder = 0;
	int* temp;
	
	// Iterate over a string
	for (int i = first.length() - 1; i > 0; i--)
	{
		// Check what numbers do we see
		int firstDigit = first[i] - '0';
		int secondDigit = second[i] - '0';
		std::string tempStr = "";

		// If we're supposed to add numbers (TODO move to the answer function for a simple check)
		if (operation.compare("PLUS") == 0)
		{
			// Check if we're adding positive or negative numbers
			if (op1 == '-')
			{
				firstDigit *= -1;
			}
			if (op2 == '-')
			{
				secondDigit *= -1;
			}

			int result = add(firstDigit, secondDigit); // Get result

			if (remainder > 0) // Check if there's any remainder from previous iteration
			{
				result += remainder;
				remainder = 0;
			}

			// If the result is greater or equal to 10 OR less than or equal to -10
			if (result >= 10 || result <= -10)
			{
				temp = split(result); // Split into separate digits
				remainder = temp[1]; // Store reminder for further reuse
				tempStr = std::to_string(std::abs(temp[0])); // Convert number to string

				strResult.insert(0, 1, tempStr[0]); // Insert to the resulting string
			}
			else
			{
				tempStr = std::to_string(std::abs(result));
				strResult.insert(0, 1, tempStr[0]);
			}
		}
	}
	std::cout << strResult << std::endl;
}

// Simple helpers for basic mathematical operations
int Q1::add(int f, int s)
{
	return f + s;
}

int Q1::subtract(int f, int s)
{
	return f - s;
}

int Q1::multiply(int f, int s)
{
	return f * s;
}

int * Q1::split(int total)
{
	// Split numbers into individual digits.
	// As I wouldn't deal with numbers longer than 2 digits (highest result I could possibly obtain
	// is from multiplication (9 * 9 = 81), it simply returns an array of 2 numbers.

	int digits[2] = { 0, 0 };

	int i = 0;
	while (total > 0)
	{
		int digit = total % 10;
		digits[i] = digit;

		total /= 10;
		i++;
	}

	return digits;
}

void Q1::write(const std::string & filepath, const std::string & str)
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
