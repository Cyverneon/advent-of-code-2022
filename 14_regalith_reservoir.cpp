#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>

std::vector<std::string> split(std::string og_string, char delim)
{
    std::vector<std::string> split_string;
    std::stringstream stream(og_string);
    std::string split;
    while(std::getline(stream, split, delim))
    {
        split_string.push_back(split);
    }
    return split_string;
}

std::set<std::vector<int>> rock_coords;
std::set<std::vector<int>> sand_coords;

std::vector<int> sand_source = {500, 0};

int cave_bottom = 0;

void getRockCoords(std::string filename)
{
    std::ifstream input;
    input.open(filename, std::ios::in);
    if (!input)
        std::cout << "couldn't open input file\n";
    else
    {
        std::string line;
        while (std::getline(input, line))
        {
            std::vector<std::string> split_string = split(line, ' ');
            std::vector<std::string> coords;
            for (int i = 0; i < split_string.size(); i++)
            {
                // ignore the arrows, we don't need them
                if (split_string[i] != "->")
                {
                    coords.push_back(split_string[i]);
                }
            }
            for (int i = 1; i < coords.size(); i++)
            {
                std::vector<std::string> coords1 = split(coords[i-1], ',');
                int x1 = stoi(coords1[0]);
                int y1 = stoi(coords1[1]);
                std::vector<std::string> coords2 = split(coords[i], ',');
                int x2 = stoi(coords2[0]);
                int y2 = stoi(coords2[1]);

                // a pair of coordinates will either have the same y and different x or the same x and different y
                // it can be going either left or right / up or down, so we check which
                if (y1 == y2)
                {
                    int min_x = (x1 < x2) ? x1 : x2;
                    int max_x = (x1 > x2) ? x1 : x2;
                    for (int i = min_x; i <= max_x; i++)
                    {
                        rock_coords.insert({i, y1});
                    }
                }
                else if (x1 == x2)
                {
                    int min_y = (y1 < y2) ? y1 : y2;
                    int max_y = (y1 > y2) ? y1 : y2;
                    for (int i = min_y; i <= max_y; i++)
                    {
                        rock_coords.insert({x1, i});
                    }
                }

                // keep a track of the lowest rock y position.
                // for part 1, past this will mean a sand unit will fall infinitely into the void
                // for part 2, this is used to calculate where the floor is
                if (y1 > cave_bottom) 
                    cave_bottom = y1;
                if (y2 > cave_bottom)
                    cave_bottom = y2;
            }
        }
    }
}

// returns true if the sand came to rest and false if it would fall forever
bool dropSand(std::vector<int> source, int floor, bool solid_floor)
{
    std::vector<int> sand_pos = source;
    std::vector<int> try_pos = source;

    bool rested = false;

    while (true)
    {
        // for part 2, this means it reached the floor and must fall to rest
        // it needs checked here because the floor is infinitely long and therefor can't be stored in the rock_coords
        if (solid_floor)
        {
            if (sand_pos[1] == floor-1)
            {
                rested = true;
                break;
            }
        }
        // for part 1: this means it fell into the void. we are done tracking this unit of sand
        else
        {
            if (sand_pos[1] >= floor)
            {
                break;
            }
        }
        // move straight down if there is no sand and no rock in the way
        try_pos = {sand_pos[0], sand_pos[1]+1};
        if ((rock_coords.find(try_pos) == rock_coords.end()) && (sand_coords.find(try_pos) == sand_coords.end()))
        {
            sand_pos = try_pos;
            continue;
        }
        // if not, move to the left
        try_pos = {sand_pos[0]-1, sand_pos[1]+1};
        if ((rock_coords.find(try_pos) == rock_coords.end()) && (sand_coords.find(try_pos) == sand_coords.end()))
        {
            sand_pos = try_pos;
            continue;
        }
        // if not, move to the right
        try_pos = {sand_pos[0]+1, sand_pos[1]+1};
        if ((rock_coords.find(try_pos) == rock_coords.end()) && (sand_coords.find(try_pos) == sand_coords.end()))
        {
            sand_pos = try_pos;
            continue;
        }

        // the sand can't fall any further
        rested = true;
        break;
    }

    if (rested)
    {
        sand_coords.insert(sand_pos);
        if (sand_pos == source)
            return false;
    }
    
    return rested;
}

void drawCave(int top, int bottom, int left, int right)
{
    for (int y = top; y <= bottom; y++)
    {
        for (int x = left; x <= right; x++)
        {
            std::vector<int> coord = {x, y};
            if (rock_coords.find(coord) != rock_coords.end())
                std::cout << "#";
            else if (sand_coords.find(coord) != sand_coords.end())
                std::cout << "o";
            else if (sand_source == coord)
                std::cout << "+";
            else
                std::cout << ".";
        }
        std::cout << "\n";
    }
}

int main()
{
    getRockCoords("14_regalith_reservoir.txt");

    while(true)
    {
        if (!dropSand(sand_source, cave_bottom, false))
            break;
    }

    std::cout << "sand units in original simulation: " << sand_coords.size() << "\n";

    sand_coords.clear();

    while(true)
    {
        if (!dropSand(sand_source, cave_bottom+2, true))
            break;
    }

    std::cout << "sand units in updated simulation with floor: " << sand_coords.size() << "\n";
} 