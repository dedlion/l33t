#include <iostream>
#include "routine.h"
#include "unordered_set"
using namespace std;



class Solution {
public:

    //https://leetcode.com/problems/valid-sudoku/
    //#36 MEDIUM
    const int SUDOKU_SIZE = 9;

    struct digiInfo
    {
        int row; int column; int square;
        bool operator==(const digiInfo & t) { return t.column==column || t.row==row || t.square==square;}
    };

    bool isValidSudoku(vector<vector<char>>& board) {
        vector<vector<digiInfo>> vec;
        vec.resize(10);
        for (int i=0; i<SUDOKU_SIZE; i++)
        {
            for (int l=0; l<SUDOKU_SIZE; l++)
            {
                if (board[i][l]!='.')
                {
                    int num = static_cast<int>(board[i][l]) - static_cast<int>('0');    //get number inside
                    if (num<0 || num>9) return false;                                   //check number is valid
                    int squareNum = floor(i/3)*3+l/3;                                   //get square number
                    digiInfo d {i,l, squareNum};                                        //create 'location' info
                    auto f = find(vec[num].begin(),vec[num].end(),d);                   //we have implemented == for this struct
                    if (f!=vec[num].end())
                    {
                        //there is 'same' info. Sudoku is broken
                        return false;
                    } else
                    {
                        //digit is valid - save it
                        vec[num].push_back(d);
                    }
                }
            }
        }
        return true;
    }


};



int main()
{
    Solution sol;
    vector<vector<char>> sudoku1 = {{'5','3','.','.','7','.','.','.','.'},
                                    {'6','.','.','1','9','5','.','.','.'},
                                    {'.','9','8','.','.','.','.','6','.'},
                                    {'8','.','.','.','6','.','.','.','3'},
                                    {'4','.','.','8','.','3','.','.','1'},
                                    {'7','.','.','.','2','.','.','.','6'},
                                    {'.','6','.','.','.','.','2','8','.'},
                                    {'.','.','.','4','1','9','.','.','5'},
                                    {'.','.','.','.','8','.','.','7','9'}};
    cout << "sudoku checker " <<sol.isValidSudoku(sudoku1) << endl;


    return 0;
}

