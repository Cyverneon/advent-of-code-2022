#include <iostream>
#include <fstream>
#include <vector>

// challenge explanation:
// https://adventofcode.com/2022/day/3
// part 2 continuation

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

        std::vector<std::string> contents = {};

        std::string line;

        while (std::getline(rucksacks, line))
        {
            contents.push_back(line);
        }

        // a group is 3 elves
        for (int i = 0; i < contents.size(); i += 3)
        {
            bool found = false;
            for (int l1 = 0; l1 < contents[i].size(); l1++)
            {
                for (int l2 = 0; l2 < contents[i+1].size(); l2++)
                {
                    // compare character in first and second line
                    // if they're the same, check third line for further match
                    if (contents[i][l1] == contents[i+1][l2])
                    {
                        for (int l3 = 0; l3 < contents[i+2].size(); l3++)
                        {
                            // compare character in first and third line
                            // (second line must also be the same to reach this point)
                            if (contents[i][l1] == contents[i+2][l3])
                            {
                                // add the priority
                                
                                // uppercase items have priorities 27 through 52, while the ascii values range 65 to 90
                                // so we subtract 38
                                if (std::isupper(contents[i][l1]))
                                { priorities_sum += int(contents[i][l1]) - 38; }
                                // lowercase items have priorities 1 through 26, while the ascii values range from 97 to 122
                                // so we subtract 96
                                else
                                { priorities_sum += int(contents[i][l1]) - 96; }
                                found = true;
                                break;
                            }
                        }
                    }
                    if (found)
                    { break; }
                }
                if (found)
                { break; }
            }
        }
        std::cout << priorities_sum << "\n";
    }

    return 0;
}