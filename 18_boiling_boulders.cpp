#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <vector>

std::vector<int> addVectors(std::vector<int> vector1, std::vector<int> vector2)
{
    std::vector<int> return_vector;
    for (int i = 0; i < vector1.size(); i++)
    {
        return_vector.push_back(vector1[i] + vector2[i]);
    }

    return return_vector;
}

std::set<std::vector<int>> getLavaCoords(std::string filename)
{
    std::set<std::vector<int>> lava_coords;

    std::ifstream input;
    input.open(filename, std::ios::in);

    if (input)
    {
        std::string line; 
        while(std::getline(input, line))
        {
            std::vector<int> coords;
            std::stringstream stream(line);
            std::string split;
            while (std::getline(stream, split, ','))
            {
                coords.push_back(stoi(split));
            }
            lava_coords.insert(coords);
        }
    }

    return lava_coords;
}

std::set<std::vector<int>> floodFill(std::vector<int> starting_coords, std::set<std::vector<int>> lava_coords, std::vector<int> min_xyz, std::vector<int> max_xyz, std::vector<std::vector<int>> adjacent_cubes)
{
    std::set<std::vector<int>> outside_coords;

    // we only want to check every node once
    // this holds nodes already checked and ones that are in the queue to be checked
    // so that duplicate nodes don't get added to the queue
    std::set<std::vector<int>> examined;

    std::vector<std::vector<int>> queue;
    queue.push_back(starting_coords);

    std::vector<int> current_node;
    while(queue.size() > 0)
    {
        current_node = *queue.begin();
        outside_coords.insert(current_node);
        queue.erase(queue.begin());

        std::vector<int> next_node;
        for (int i = 0; i < adjacent_cubes.size(); i++)
        {
            next_node = addVectors(current_node, adjacent_cubes[i]);
            // make sure it within bounds
            if (next_node[0] < min_xyz[0] || next_node[0] > max_xyz[0])
                continue;
            if (next_node[1] < min_xyz[1] || next_node[1] > max_xyz[1])
                continue;
            if (next_node[2] < min_xyz[2] || next_node[2] > max_xyz[2])
                continue;

            // make sure its not a lava node
            if (lava_coords.find(next_node) != lava_coords.end())
                continue;
            
            // make sure we didn't check it/are planning to check it already 
            if (examined.find(next_node) == examined.end())
            {
                examined.insert(next_node);
                queue.push_back(next_node);
            }
        }
    }

    return outside_coords;
}

int main()
{
    std::set<std::vector<int>> lava_coords = getLavaCoords("18_boiling_boulders.txt");;

    // i'm lazy, so we're just gonna loop through these every time we need to
    std::vector<std::vector<int>> adjacent_cubes =
    {
        {-1, 0, 0},
        {1, 0, 0},
        {0, -1, 0},
        {0, 1, 0},
        {0, 0, -1},
        {0, 0, 1},
    };

    // checking for a non-lava cube for each side of every lava cube, and incrementing the surface area if so
    int total_surface_area = 0;
    for (auto itr = lava_coords.begin(); itr != lava_coords.end(); ++itr)
    {
        std::vector<int> current_coords = *itr;
        for (int i = 0; i < adjacent_cubes.size(); i++)
        {
            std::vector<int> test_coords = addVectors(adjacent_cubes[i], current_coords);
            if (lava_coords.find(test_coords) == lava_coords.end())
            {
                total_surface_area++;
            }
        }
    }

    // min and max just set to the highest and lowest value that fits in an int, so the comparisions work
    std::vector<int> min_xyz = {2147483647, 2147483647, 2147483647};
    std::vector<int> max_xyz = {-2147483647, -2147483647, -2147483647};

    for (auto itr = lava_coords.begin(); itr != lava_coords.end(); ++itr)
    {
        std::vector<int> coords = *itr;
        if (coords[0] < min_xyz[0])
            min_xyz[0] = coords[0];
        if (coords[0] > max_xyz[0])
            max_xyz[0] = coords[0];
        
        if (coords[1] < min_xyz[1])
            min_xyz[1] = coords[1];
        if (coords[1] > max_xyz[1])
            max_xyz[1] = coords[1];
        
        if (coords[2] < min_xyz[2])
            min_xyz[2] = coords[2];
        if (coords[2] > max_xyz[2])
            max_xyz[2] = coords[2];
    }

    // add a tiny amount of space, just in case the floodfill can't get passed otherwise
    min_xyz = addVectors(min_xyz, {-1, -1, -1});
    max_xyz = addVectors(max_xyz, {1, 1, 1});

    // start the floodfill off at min_xyz
    // since we added this extra space, this point is definitely not a lava cube
    std::set<std::vector<int>> outside_coords = floodFill(min_xyz, lava_coords, min_xyz, max_xyz, adjacent_cubes);

    // check each adjacent cube for every outside cube, and increment the outside surface area if it's a lava
    int outside_surface_area = 0;
    for (auto itr = outside_coords.begin(); itr != outside_coords.end(); ++itr)
    {
        std::vector<int> current_coords = *itr;
        for (int i = 0; i < adjacent_cubes.size(); i++)
        {
            std::vector<int> test_coords = addVectors(adjacent_cubes[i], current_coords);
            if (lava_coords.find(test_coords) != lava_coords.end())
            {
                outside_surface_area++;
            }
        }
    }

    std::cout << "total surface area: " << total_surface_area << "\n";
    std::cout << "outside surface area: " << outside_surface_area << "\n";
}