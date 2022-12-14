#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// https://adventofcode.com/2022/day/8

std::string input_file = "8_tree_house.txt";

std::vector<std::vector<int>> trees;
std::vector<std::vector<bool>> visible;

int check_visible(int x, int y, int tallest_tree)
{
	if (trees[x][y] > tallest_tree)
	{
		visible[x][y] = true;
		return trees[x][y];
	}
	return tallest_tree;
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
			visible.push_back({});
			for (int i = 0; i < line.length(); i++)
			{
				trees[line_count].push_back(std::stoi(line.substr(i, 1)));
				visible[line_count].push_back(false);
			}
			line_count++;
		}
	}
}

int main()
{
	get_trees_from_input(input_file);

	int height = trees.size() - 1;
	int width = trees[0].size() - 1;

	int tallest_forward = -1;
	int tallest_backward = -1;
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			tallest_forward = check_visible(i, j, tallest_forward);
			tallest_backward = check_visible(i, width-j, tallest_backward);
		}
		tallest_forward = -1;
		tallest_backward = -1;
	}

	for (int j = 0; j <= width; j++)
	{
		for (int i = 0; i <= height; i++)
		{
			tallest_forward = check_visible(i, j, tallest_forward);
			tallest_backward = check_visible(height - i, j, tallest_backward);
		}
		tallest_forward = -1;
		tallest_backward = -1;
	}

	int visible_trees_count = 0;
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (visible[i][j])
				visible_trees_count++;
		}
	}

	std::cout << "visible trees: " << visible_trees_count << "\n";

	int top_scenic_score = 0;
	for (int i = 0; i <= height; i++)
	{
		for (int j = 0; j <= width; j++)
		{
			if (get_tree_scenic_score(i, j) > top_scenic_score)
			{
				top_scenic_score = get_tree_scenic_score(i, j);
			}
		}
	}

	std::cout << "highest scenic score: " << top_scenic_score << "\n";

	return 0;
}
