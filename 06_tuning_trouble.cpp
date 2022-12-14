#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

// https://adventofcode.com/2022/day/6

// the amount of characters of each these markers
int packet_marker = 4;
int message_marker = 14;

// look for a sequence of length marker_length in a string line
// returns the amount of characters processed/the character the sequence ends at
// 0 means appropriate sequence was not found
int find_marker(std::string line, int marker_length)
{
	for (int i = marker_length - 1; i < line.length(); i++)
	{
		std::set<char> marker;
		for (int j = 0; j < marker_length; j++)
		{
			marker.insert(line[i - j]);
		}
		if (marker.size() == marker_length)
		{
			return i + 1;
		}
	}
	return 0;
}

int main()
{
	std::ifstream input;
	input.open("6_tuning_trouble.txt", std::ios::in);

	if (!input)
	{
		std::cout << "Couldn't open input file\n";
	}
	else
	{
		std::string line;
		std::getline(input, line);

		std::cout << "start-of-packet marker processed at character " << find_marker(line, packet_marker) << "\n";
		std::cout << "start-of-message marker processed at character " << find_marker(line, message_marker) << "\n";
	}

	return 0;
}
