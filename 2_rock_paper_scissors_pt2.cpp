#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    // input is given with each round on a line, with the opponents play (A, B, or C), then a space, then what the player should do (X, Y or Z)

    // X - Lose | Y - Draw | Z - Win
    std::vector<char> actions = {'X', 'Y', 'Z'};

    // A - Rock | B - Paper | C - Scissors
    std::vector<char> plays = {'A', 'B', 'C'};

    // indexes of what defeats and is defeated by what
    // rock defeats scissors, paper defeats rock, scissors defeat paper
    // rock defeated by paper, paper defeated by scissors, scissors defeated by rock
    std::vector<int> defeats = {2, 0, 1};
    std::vector<int> defeated_by = {1, 2, 0};

    // 1 point for rock, 2 points for paper, 3 points for scissors
    std::vector<int> points = {1, 2, 3};

    int total_score = 0;

    std::ifstream strategy_file;
    strategy_file.open("2_rock_paper_scissors.txt", std::ios::in);

    if (!strategy_file)
    {
        std::cout << "Strategy file does not exist.\n";
    }
    else
    {
        std::string line;
                
        while (std::getline(strategy_file, line))
        {
            std::istringstream stream(line);
            char opponent;
            char you;

            if (!(stream >> opponent >> you))
            {
                std::cout << "Wasn't able to get plays from strategy file, it might be formatted incorrectly.\n";
                break;
            }

            int opponent_index = 0;

            for (int i = 0; i < plays.size(); i++)
            {
                if (opponent == plays[i])
                {
                    opponent_index = i;
                }
            }

            // lose
            if (you == 'X')
            {
                // points value of the play that the opponent will defeat
                total_score += points[defeats[opponent_index]];
                // no points for losing
            }

            // draw
            if (you == 'Y')
            {
                // points value of the same play as the opponent
                total_score += points[opponent_index];
                // points for drawing
                total_score += 3;
            }

            // win
            if (you == 'Z')
            {
                // points value of the play that the opponent will be defeated by
                total_score += points[defeated_by[opponent_index]];
                // points for winning
                total_score += 6;
            }
        }
    }
    
    std::cout << total_score << "\n";

    return 0;
}