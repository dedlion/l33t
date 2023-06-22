#include <iostream>
#include "routine.h"
using namespace std;


class Solution {
public:
   //https://leetcode.com/problems/maximum-subarray/description/
   //#53 MEDIUM
   int maxSubArray(vector<int>& nums) {
        int bestSum = nums[0];
        int currSum = nums[0];
        int len = nums.size();
        bool positiveStreak = (currSum>=0); //last number is positive or negative
        for (int i=1; i<len; i++)
        {
            if (positiveStreak)
            {
                //if next number is positive just add it.
                if (nums[i]<0)
                {
                    //oh no. we should chek may we can endure this negative digit array
                    positiveStreak=false;
                    bestSum = max(bestSum,currSum); //may be this is the end of BEST array
                }
            } else
            {
                //prev value was negative
                if (nums[i]>0)
                {
                    //if curr value is positive. we should check may be negative arra was less then prev positive array so we can "win"
                    if (currSum < 0)
                    {
                        //negative arr > prev positive arr. Should start new good arr
                        currSum = 0;
                    }
                    positiveStreak = true;
                }
            }
            currSum = currSum + nums[i];    //just update current sum
        }
        bestSum = max(bestSum,currSum); //if we end with positive streak we should check last currSum
        //if there is NO positive values... we just find best single number
        if (bestSum<0)
        {
            bestSum = *max_element(nums.begin(),nums.end());
        }
        return bestSum;
    }

   //https://leetcode.com/problems/spiral-matrix/
   //#54 MEDIUM
   vector<int> spiralOrder(vector<vector<int>>& matrix) {
       int y_max = matrix.size();
       int x_max = matrix.at(0).size();
       int totalLen = x_max*y_max;
       vector <int> res(totalLen);
       int left = 0;
       int right = x_max-1;
       int top = 0;
       int bottom = y_max-1;

       int x =0;
       int y =0;
       int index = 0;
       res[0]=matrix[0][0];

       while (index<totalLen)
       {

           while (x<right)    //left -> right
           {
               x++;
               index++;
               res[index] = matrix[y][x];
           }
           top++;

           if (index==totalLen-1) return res;
           while (y<bottom)    //top -> bottom
           {
               y++;
               index++;
               res[index] = matrix[y][x];
           }
           right--;

           if (index==totalLen-1) return res;
           while (x>left)    // right -> left
           {
               x--;
               index++;
               res[index] = matrix[y][x];
           }
           bottom--;

           if (index==totalLen-1) return res;
           while (y>top)    //bottom -> top
           {
               y--;
               index++;
               res[index] = matrix[y][x];
           }
           left++;


       }
       return res;
   }

    //https://leetcode.com/problems/jump-game/
   //#55 MEDIUM
   bool canJump(vector<int>& nums) {
       if (nums.size()==1) return true; //already done
       int len  = nums.size();
       int fuel = nums.at(0); //how far away i can jump

       int i=0; //lets start from 1st stone
       while (fuel >0) {    //while i have "strength" to jump i will jump
           if (i==len-1) return true;   //ok im at the end WIN
           fuel--;                      //we have used 1 "fuel"
           fuel = max(fuel,nums[i]);    //may be if will stop here - we can get additional "fuel"
           i++;                         //go to next index
       }

       return false;
   }
};

int main()
{
    Solution sol;
    vector<int> probl53 {-2,1,-3,4,-1,2,1,-5,4};
    cout << "pr53 best positive sum " << sol.maxSubArray(probl53) << endl;

    vector<vector<int>> prob54 {{1,2,3},{4,5,6},{7,8,9}};
    routine::showVector(sol.spiralOrder(prob54));

    vector<int> prob55 {1,1,1,1,1,4};
    cout << "can jump " << sol.canJump(prob55) << endl;

    return 0;
}

