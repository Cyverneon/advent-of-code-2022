#include <iostream>
#include <vector>
#include <set>
#include <fstream>
#include <sstream>

// https://adventofcode.com/2022/day/9

class Rope
{
public:
    Rope(int length, std::vector<int> initial_pos)
    {
        knots = std::vector<std::vector<int>>(length, initial_pos);
    }

    ~Rope() {}

    void move(char direction)
    {
        // R - right, positive horizontal movement
        // L - left, negative horizontal movement
        // U - up, positive vertical movement
        // D - down, negative vertical movement
        switch(direction)
        {
            case 'R':
                knots[0][0] += 1;
                break;
            
            case 'L':
                knots[0][0] -= 1;
                break;
            
            case 'U':
                knots[0][1] += 1;
                break;
            
            case 'D':
                knots[0][1] -= 1;
                break;
        }

        for (int i = 1; i < knots.size(); i++)
        {
            moveTailKnot(i);
        }
    }

    void moveTailKnot(int index)
    {
        // get the horizntal and vertical difference from the previous knot
        int difference_h = knots[index-1][0] - knots[index][0];
        int difference_v = knots[index-1][1] - knots[index][1];

        // if the knot is on the same column and too far away on the row, move horizontally
        if (difference_v == 0 && abs(difference_h) == 2)
        {
            // either move right or left depending if the difference is positive or negative
            knots[index][0] += (difference_h > 0) ? 1 : -1;
        }
        
        // if the knot is on the same row and too far away on the column, move vertically
        else if (difference_h == 0 && abs(difference_v) == 2)
        {
            // either move up or down depending if the difference is positive or negative
            knots[index][1] += (difference_v > 0) ? 1 : -1;
        }

        // if the knot is on neither the same row or column and too far away on one (or both) of them, move diagonally
        else if ((difference_v != 0 && difference_h != 0) && (abs(difference_h) == 2 || abs(difference_v) == 2))
        {
            // moving diagonally is just moving both horizontally and vertically
            knots[index][0] += (difference_h > 0) ? 1 : -1;
            knots[index][1] += (difference_v > 0) ? 1 : -1;
        }
    }

    int getRopeLength()
    {
        return(knots.size());
    }

    std::vector<int> getKnotPos(int index)
    {
        return knots[index];
    }

private:
    std::vector<std::vector<int>> knots;
    
};

int main()
{
    std::ifstream input;
    input.open("9_rope_bridge.txt", std::ios::in);

    if (!input)
        std::cout << "Couldn't open input file\n";
    else
    {
        Rope short_rope(2, {0, 0});
        std::set<std::vector<int>> short_tail_visited = {};

        Rope long_rope(10, {0, 0});
        std::set<std::vector<int>> long_tail_visited = {};

        std::string line;
        while (std::getline(input, line))
        {
            std::istringstream stream(line);
            char direction;
            int steps;

            stream >> direction >> steps;
            
            for (int i = 0; i < steps; i++)
            {
                short_rope.move(direction);
                short_tail_visited.insert(short_rope.getKnotPos(short_rope.getRopeLength()-1));

                long_rope.move(direction);
                long_tail_visited.insert(long_rope.getKnotPos(long_rope.getRopeLength()-1));
            }
        }
        
        std::cout << "the last knot of a rope of length 2 will visit " << short_tail_visited.size() << " positions\n";
        std::cout << "the last knot of a rope of length 9 will visit " << long_tail_visited.size() << " positions\n";
    }

    return 0;
}