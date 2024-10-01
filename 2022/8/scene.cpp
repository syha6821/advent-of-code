#include "std_lib_facilities.h"
#include <fstream>

const int ASCII_FOR_NUM = 48;
/* const string SAMPLE = "input_test.txt"; */
const string SAMPLE = "input.txt";
vector<vector<int>> read_square(string file_name);
vector<int> read_line(string line);
int best_score(vector<vector<int>> square);

int main()
{
    auto square = read_square(SAMPLE);
    cout << best_score(square) << '\n';
    return 0;
}

int best_score(vector<vector<int>> square)
{
    int highest_score = 0;
    for (int i = 1; i < square.size() - 1; i++) // ignore edge
    {
        int score = 0;
        for (int j = 1; j < square[i].size() - 1; j++)
        {
            int count = 0;
            int target_height = square[i][j];
            //look left
            int left_score = 0;
            int left_edge_distance = j;
            while(count != left_edge_distance)
            {
                left_score++;
                if(target_height <= square[i][j - (count + 1)])
                {
                    break;
                }
                count++;
            }
            count = 0;
            //look right
            int right_score = 0;
            int right_edge_distance = square[i].size()-1 - j;
            while(count != right_edge_distance)
            {
                right_score++;
                if(target_height <= square[i][j + (count + 1)]) break;
                count++;
            }
            count = 0;
            //look up
            int up_score = 0;
            int up_edge_distance = i;
            while(count != up_edge_distance)
            {
                up_score++;
                if(target_height <= square[i - count - 1][j]) break;
                count++;
            }
            count = 0;
            //look down
            int down_score = 0;
            int down_edge_distance = square.size() - 1 - i;
            while(count != down_edge_distance)
            {
                down_score++;
                if(target_height <= square[i + 1 + count][j]) break;
                count++;
            }
            count = 0;
            score = left_score * right_score * up_score * down_score;
            if (score > highest_score) highest_score = score;
        }
    }
    return highest_score;
}

vector<vector<int>> read_square(string file_name)
{
    vector<vector<int>> square;
    ifstream ifs;
    ifs.open(file_name);
    string a;
    while(getline(ifs,a))
    {
        square.push_back(read_line(a));
    }
    return square;
}

vector<int> read_line(string line)
{
    vector<int> digits;
    for(const char& ch : line)
    {
        digits.push_back(ch - ASCII_FOR_NUM);
    }
    return digits;
}