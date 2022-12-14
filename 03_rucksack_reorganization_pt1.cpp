#include <iostream>
#include <fstream>
#include <vector>

// challenge explanation:
// https://adventofcode.com/2022/day/3

int main()
{
    std::ifstream rucksacks;
    rucksacks.open("3_rucksack_reorganization.txt", std::ios::in);
    if (!rucksacks)
    {
        std::cout << "Could not open rucksacks file\n";
    }
    else
    {
        int priorities_sum = 0;

        std::string line;
        while (std::getline(rucksacks, line))
        {
            // because for each rucksack both compartments have the same amount of items,
            // compartment 2 starts at the midpoint of the line
            int midpoint = line.length() / 2;

            // tracking found common items to avoid duplicates
            std::vector<char> common_items;

            for (int i = 0; i < midpoint; i++)
            {
                for (int j = midpoint; j < line.length(); j++)
                {
                    if (line[i] == line[j])
                    {
                        // make sure we didn't already account for this common item
                        bool no_duplicate = true;
                        for (int k = 0; k < common_items.size(); k++)
                        {
                            if (line[i] == common_items[k])
                            {
                                no_duplicate = false;
                            }
                        }
                        if (no_duplicate)
                        {
                            common_items.push_back(line[i]);
                            // uppercase items have priorities 27 through 52, while the ascii values range 65 to 90
                            // so we subtract 38
                            if (std::isupper(line[i]))
                            {
                                priorities_sum += int(line[i]) - 38;
                            }
                            // lowercase items have priorities 1 through 26, while the ascii values range from 97 to 122
                            // so we subtract 96
                            else
                            {
                                priorities_sum += int(line[i]) - 96;
                            }
                        }
                    }
                }
            }
        }

        std::cout << priorities_sum << "\n";
    }

    return 0;
}
