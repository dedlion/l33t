#include <iostream>
#include "routine.h"

using namespace std;


class Solution {
public:
    int countNegatives(vector<vector<int>>& grid) {
        int height = grid.size();
        int width = grid.at(0).size();  //grid[x][y]

        int x=width-1;
        int y=height-1;
        int res=0;
        //find bottom keft positive value
        while (x>=0)
        {
            if (grid[y][x]>=0)
            {
                break;
            } else
            {
                res++;
            }
            x--;
        }
        y--;
        if (x==-1) x=0; //if all numbers are negative


        //we go zig-zag till we find negaive number
        while (y>=0)    //move up
        {
            while (x<width) //move right
            {
                if (grid[y][x]<0)
                {
                    res++;
                    break;   //positive
                }
                x++;//move right
            }
            if (x==width) return res;    //if all numbers is positive
            res+=width-x-1;
            y--;//move up
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> data_1351 = {{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}};
    vector<vector<int>> data_1351_2 = {{7,-5}};
    cout << " negatives count " << sol.countNegatives(data_1351_2) << endl;

    cout << "Hello World!" << endl;
    return 0;
}

