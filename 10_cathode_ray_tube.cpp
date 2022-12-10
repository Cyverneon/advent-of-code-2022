#include <iostream>
#include <fstream>
#include <sstream>

class CRT
{
public:
    CRT() {}

    ~CRT() {}

    void cycle()
    {
        int current_pos = (cycles % 40);
        if (current_pos == 0)
            std::cout << "\n";
        if (current_pos >= sprite_pos - sprite_offset && current_pos <= sprite_pos + sprite_offset)
            std::cout << "#";
        else
            std::cout << ".";
        cycles++;
    }

    void noop()
    {
        cycle();
    }

    void addX(int v)
    {
        cycle();
        cycle();
        sprite_pos += v;
    }

private:
    int sprite_pos = 1;
    int sprite_width = 3;
    // if the sprite width is 3, it extends 1 before and beyond the sprite position
    // just for readability
    int sprite_offset = 1;
    int cycles = 0;
};

std::string filename = "10_cathode_ray_tube.txt";

int main()
{
    std::ifstream input;
    input.open(filename, std::ios::in);

    if (!input)
        std::cout << "Could not open input file\n";
    else
    {
        CRT crt;

        std::string line;
        while(std::getline(input, line))
        {
            std::istringstream stream(line);

            std::string instruction;
            stream >> instruction;

            if (instruction == "noop")
                crt.noop();
            else if (instruction == "addx")
            {
                int v = 0;
                stream >> v;
                crt.addX(v);
            }
        }
    }

    return 0;
}