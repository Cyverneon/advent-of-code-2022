#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main()
{
    // input is given with each round on a line, with the opponents play (A, B, or C), then a space, then the player's play (X, Y or Z)

    // for the player: X - Rock | Y - Paper | Z - Scissors
    // for the opponent: A - Rock | B - Paper | C - Scissors

    std::vector<char> plays = {'X', 'Y', 'Z'};
    std::vector<char> opponent_plays = {'A', 'B', 'C'};

    // rock defeats scissors, paper defeats rock, scissors defeat paper
    std::vector<char> defeats = {'C', 'A', 'B'};

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

            for (int i = 0; i < plays.size(); i++)
            {
                if (you == plays[i])
                {
                    // points for which option you played 
                    total_score += points[i];

                    // win?
                    if (opponent == defeats[i])
                    {
                        total_score += 6;
                    }
                    // draw?
                    else if (opponent == opponent_plays[i])
                    {
                        total_score += 3;
                    }
                    //losing gives no additional points

                    break;
                }
            }
        }
    }
    
    std::cout << total_score << "\n";

    return 0;
}