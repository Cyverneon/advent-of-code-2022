#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

// a map with vectors of x and y coordinates and their corresponding nested vector of the connected nodes coordinates
std::map<std::vector<int>, std::vector<std::vector<int>>> map;

std::vector<int> start_pos = { 0, 0 };
std::vector<std::vector<int>> all_start_pos = {};
std::vector<int> end_pos = { 0, 0 };

void getMapFromFile(std::string filename)
{
	std::ifstream input;
	input.open(filename, std::ios::in);

	if (!input)
		std::cout << "Could not open input file\n";
	else
	{
		std::vector<std::string> lines;
		std::string line;
		while (std::getline(input, line))
		{
			lines.push_back(line);
		}
		int height = lines.size();
		// input is given as a grid - so the length of the first line will be the same as all 
		int width = lines[0].length();

		// find the start/end positions, save them then replace with appropriate altitude
		// 'a' for the start and 'z' for the end
		for (int y = 0; y < lines.size(); y++)
		{
			for (int x = 0; x < lines[y].length(); x++)
			{
				if (lines[y][x] == 'S')
				{
					start_pos = { x, y };
					all_start_pos.push_back({ x, y });
					lines[y][x] = 'a';
				}
				if (lines[y][x] == 'a')
				{
					all_start_pos.push_back({ x, y });
				}
				if (lines[y][x] == 'E')
				{
					end_pos = { x, y };
					lines[y][x] = 'z';
				}
			}
		}

		for (int y = 0; y < lines.size(); y++)
		{
			for (int x = 0; x < lines[y].length(); x++)
			{
				std::vector<std::vector<int>> valid_adjacent_nodes;
				if (x > 0)
					if (int(lines[y][x - 1]) <= int(lines[y][x]) + 1)
						valid_adjacent_nodes.push_back({ x - 1, y });
				if (x < width-1)
					if (int(lines[y][x + 1]) <= int(lines[y][x]) + 1)
						valid_adjacent_nodes.push_back({ x + 1, y });
				if (y > 0)
					if (int(lines[y - 1][x]) <= int(lines[y][x]) + 1)
						valid_adjacent_nodes.push_back({ x, y - 1 });
				if (y < height - 1)
					if (int(lines[y + 1][x]) <= int(lines[y][x]) + 1)
						valid_adjacent_nodes.push_back({ x, y + 1 });
				
				map.insert({ { x, y }, valid_adjacent_nodes });
			}
		}
	}
}


// https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm#Algorithm
int DijkstraSearchMap(std::vector<std::vector<int>> start_nodes, std::vector<int> end_node)
{
	// we can't have infinity (or we can, but it behaves weirdly?)
	// so instead we have the biggest number that can fit in an int
	int max_distance = 2147483647;


	// put every node in a set of unvisited nodes, and assign them all distance of infinity (our max distance)
	std::set<std::vector<int>> unvisited;
	std::map<std::vector<int>, int> distances;

	for (auto itr = map.begin(); itr != map.end(); ++itr)
	{
		unvisited.insert(itr->first);
		distances.insert({ itr->first, max_distance });
	}

	// every starting node will have a distance 0
	for (int i = 0; i < start_nodes.size(); i++)
	{
		distances[start_nodes[i]] = 0;
	}

	// doesn't matter which start node we start with, so let's just do the first one
	std::vector<int> current_node = start_nodes[0];

	while (!unvisited.empty())
	{
		// check all the nodes connected to the current node
		std::vector<std::vector<int>> connections = map.at(current_node);
		for (int i = 0; i < connections.size(); i++)
		{
			if (distances[current_node] + 1 < distances[connections[i]])
			{
				// every node is a square on a grid, the distance between each of them is always 1
				distances[connections[i]] = distances[current_node] + 1;
			}
		}

		unvisited.erase(current_node);
		// this means we have visited every node and are done
		if (unvisited.empty())
			break;

		// select a node from the unvisited nodes with the shortest distance
		std::vector<int> new_node_temp = *unvisited.begin();
		int smallest_distance = distances[new_node_temp];
		for (auto itr = unvisited.begin(); itr != unvisited.end(); ++itr)
		{
			if (distances[*itr] < smallest_distance)
			{
				smallest_distance = distances[*itr];
				new_node_temp = *itr;
			}
		}
		current_node = new_node_temp;
		
		// this means we got stuck with a node unconnected to the other nodes
		if (distances[current_node] == max_distance)
			break;
		//we found the target node so don't need to finish the search
		if (current_node == end_node)
			break;
	}

	return distances[end_node];
}

int main()
{
	getMapFromFile("12_hill_climbing.txt");

	// this could probably be optimised so we don't run the algorithm twice
	// but it works and did not take too long, so I'm keeping it as is
	std::cout << "shortest route from the start point to the end point " << DijkstraSearchMap({start_pos}, end_pos) << "\n";
	std::cout << "shortest route from any point at elevation 'a' to the end point: " << DijkstraSearchMap(all_start_pos, end_pos) << "\n";

	return 0;
}