#include <iostream>
#include "routine.h"
#include "memory"

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

//https://leetcode.com/problems/product-of-the-last-k-numbers/
//#1352 MEDIUM
class ProductOfNumbers {
public:
    vector <int> memory;
    const bool V2 = true;
    //we will save not numbers but possible results
    ProductOfNumbers() {

    }

    void add(int num) {
        if (num==0)
        {
            //X * 0 == 0... no need to save data anymore
            memory.clear();
        } else
        {
            //mult everything by input
            //adding data is slow BUT getProduct will be FAST
            if (num!=1)
            {
                for (auto & i : memory)
                {
                    i = i*num;
                }
            }
            memory.push_back(num);  //self*1
        }
    }

    int getProduct(int k) {
        if (k>memory.size()) return 0;
        int reverseIndex = memory.size()-k; //k==1 -> reverseIndex==memory.size()-1
        return memory[reverseIndex];
    }
};


int main()
{
    Solution sol;
    vector<vector<int>> data_1351 = {{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}};
    vector<vector<int>> data_1351_2 = {{7,-5}};
    cout << " negatives count " << sol.countNegatives(data_1351_2) << endl;

    ProductOfNumbers pr;
    pr.add(1);
    pr.add(3);
    pr.add(0);
    cout << "product value " <<pr.getProduct(3) << endl;
    return 0;
}

