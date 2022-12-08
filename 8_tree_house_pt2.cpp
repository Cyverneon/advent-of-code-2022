#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// https://adventofcode.com/2022/day/8

std::string input_file = "8_tree_house.txt";

std::vector<std::vector<int>> trees;

bool check_tree_visible(int y, int x)
{
	int height = trees.size();
	int width = trees[0].size();

	// check left of tree
	int count = 0;
	for (int new_x = 0; new_x < x; new_x++)
	{
		if (trees[y][new_x] >= trees[y][x])
			break;
		count++;
	}
	if (count == x)
		return true;
	
	// check right of tree
	count = 0;
	for (int new_x = x+1; new_x < width; new_x++)
	{
		if (trees[y][new_x] >= trees[y][x])
			break;
		count++;
	}
	if (x+count == width-1)
		return true;

	// check above tree
	count = 0;
	for (int new_y = 0; new_y < y; new_y++)
	{
		if (trees[new_y][x] >= trees[y][x])
			break;
		count++;
	}
	if (count == y)
		return true;
	
	// check right of tree
	count = 0;
	for (int new_y = y+1; new_y < height; new_y++)
	{
		if (trees[new_y][x] >= trees[y][x])
			break;
		count++;
	}
	if (y+count == height-1)
		return true;
	
	return false;
}

int get_tree_scenic_score(int y, int x)
{
	int height = trees.size();
	int width = trees[0].size();

	// check left of tree
	int left_count = 0;
	for (int new_x = x-1; new_x >= 0; new_x--)
	{
		left_count++;
		if (trees[y][new_x] >= trees[y][x])
			break;
	}
	
	// check right of tree
	int right_count = 0;
	for (int new_x = x+1; new_x < width; new_x++)
	{
		right_count++;
		if (trees[y][new_x] >= trees[y][x])
			break;
	}

	// check above tree
	int above_count = 0;
	for (int new_y = y-1; new_y >= 0; new_y--)
	{
		above_count++;
		if (trees[new_y][x] >= trees[y][x])
			break;
	}
	
	// check below tree
	int below_count = 0;
	for (int new_y = y+1; new_y < height; new_y++)
	{
		below_count++;
		if (trees[new_y][x] >= trees[y][x])
			break;
	}
	return left_count * right_count * above_count * below_count;
}

void get_trees_from_input(std::string filename)
{
	std::ifstream input;
	input.open(filename, std::ios::in);

	if (!input)
	{
		std::cout << "couldn't open input file";
	}
	else
	{
		std::string line;
		int line_count = 0;
		while (std::getline(input, line))
		{
			trees.push_back({});
			for (int i = 0; i < line.length(); i++)
			{
				trees[line_count].push_back(std::stoi(line.substr(i, 1)));
			}
			line_count++;
		}
	}
}

int main()
{
	get_trees_from_input(input_file);

	int visible_trees_count = 0;
	int top_scenic_score = 0;
	for (int i = 0; i < trees.size(); i++)
	{
		for (int j = 0; j < trees[0].size(); j++)
		{
			if (check_tree_visible(i, j))
				visible_trees_count++;
			if (get_tree_scenic_score(i, j) > top_scenic_score)
			{
				top_scenic_score = get_tree_scenic_score(i, j);
			}
		}
	}

	std::cout << "visible trees: " << visible_trees_count << "\n";
	std::cout << "highest scenic score: " << top_scenic_score << "\n";

	return 0;
}