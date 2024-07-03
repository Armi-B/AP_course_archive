#include <iostream>
#include <vector>
#include <string>
#define LEFT 7
#define UP 8
#define RIGHT 9
#define DOWN 10
#define ASCII 41
using namespace std;

bool way_to_win(vector<string>& board, int num_of_n, vector<int> &output);

int main()
{
    vector<int> output;
    vector<string> board;
    char temp;
    int num_of_n = 0;
    for (int i = 0; i < 7; i++)
    {
        string row;
        for (int j = 0; j < 7; j++)
        {
            cin >> temp;
            row.push_back(temp);
            if (temp == 'N')
            {
                num_of_n++;
            }
        }
        board.push_back(row);
    }
    if(!way_to_win(board, num_of_n, output))
    {
        cout<<"Loser\n";
        return 0;
    }
    for(int i=0; i<size(output); i++)
    {
        if(output[i]==LEFT)
        {
            cout<<" LEFT\n";
        }
        else if(output[i]==UP)
        {
            cout<<" UP\n";
        }
        else if(output[i]==RIGHT)
        {
            cout<<" RIGHT\n";
        }
        else if(output[i]==DOWN)
        {
            cout<<" DOWN\n";
        }
        else
        {
            char temp=(char)(output[i]+ASCII);
            cout<<temp;
            i++;
            cout<<output[i];
        }
    }
    return 0;
}

bool way_to_win(vector<string>& board, int num_of_n, vector<int> &output)
{
    if (num_of_n == 1 && (board[3][3] == 'N'))
    {
        return true;
    }
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            if (board[i][j] == 'N')
            {
                if (j > 1)
                {
                    if ((board[i][j - 1] == 'N') && (board[i][j - 2] == 'O'))
                    {
                        board[i][j] = 'O';
                        board[i][j - 1] = 'O';
                        board[i][j - 2] = 'N';
                        output.push_back(i);
                        output.push_back(j);
                        output.push_back(LEFT);
                        if (way_to_win(board, num_of_n - 1, output))
                        {
                            return true;
                        }
                        board[i][j] = 'N';
                        board[i][j - 1] = 'N';
                        board[i][j - 2] = 'O';
                        for(int l=0; l<3; l++)
                        {
                            output.pop_back();
                        }
                    }
                }
                if(i>1)
                {
                   if ((board[i+1][j] == 'N') && (board[i+2][j] == 'O'))
                    {
                        board[i][j] = 'O';
                        board[i+1][j] = 'O';
                        board[i+2][j] = 'N';
                        output.push_back(i);
                        output.push_back(j);
                        output.push_back(UP);
                        if (way_to_win(board, num_of_n - 1, output))
                        {
                            return true;
                        }
                        board[i][j] = 'N';
                        board[i+1][j] = 'N';
                        board[i+2][j] = 'O';
                        for(int l=0; l<3; l++)
                        {
                            output.pop_back();
                        }
                    } 
                }
                if(j<5)
                {
                    if ((board[i][j + 1] == 'N') && (board[i][j + 2] == 'O'))
                    {
                        board[i][j] = 'O';
                        board[i][j + 1] = 'O';
                        board[i][j + 2] = 'N';
                        output.push_back(i);
                        output.push_back(j);
                        output.push_back(RIGHT);
                        if (way_to_win(board, num_of_n - 1, output))
                        {
                            return true;
                        }
                        board[i][j] = 'N';
                        board[i][j + 1] = 'N';
                        board[i][j + 2] = 'O';
                        for(int l=0; l<3; l++)
                        {
                            output.pop_back();
                        }
                    }
                }
                if(i<5)
                {
                    if ((board[i-1][j] == 'N') && (board[i-2][j] == 'O'))
                    {
                        board[i][j] = 'O';
                        board[i-1][j] = 'O';
                        board[i-2][j] = 'N';
                        output.push_back(i);
                        output.push_back(j);
                        output.push_back(UP);
                        if (way_to_win(board, num_of_n - 1, output))
                        {
                            return true;
                        }
                        board[i][j] = 'N';
                        board[i-1][j] = 'N';
                        board[i-2][j] = 'O';
                        for(int l=0; l<3; l++)
                        {
                            output.pop_back();
                        }
                    } 
                }
            }
        }
    }
    return false;
}