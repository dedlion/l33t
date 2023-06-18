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
};

int main()
{
    Solution sol;
    vector<int> probl53 {-2,1,-3,4,-1,2,1,-5,4};
    cout << "pr53 best positive sum " << sol.maxSubArray(probl53) << endl;
    return 0;
}

