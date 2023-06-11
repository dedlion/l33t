#include <iostream>
#include "routine.h"

using namespace std;


class Solution {
public:

    //https://leetcode.com/problems/first-missing-positive/
    //#41 HARD
int firstMissingPositive(vector<int>& nums) {
    //another straightforward solution
    const int MAX_MISSED_VAL  =  10e5+1; //in worst case scenario we need this amount of memory
    //create map of recieved numbers
    std::vector<bool> map;
    map.resize(MAX_MISSED_VAL); //constatnt memory size
    map[0]=true; //zero is not positive autoskip
    for (auto i : nums)
    {
        if (i>0 && i<MAX_MISSED_VAL)
            map[i]=true;   //skip this value
    }
    return distance( begin(map), find_if( begin(map), end(map), [](int x) { return x == false; })); //first zero is missed int
}


int jump(vector<int>& nums) {
    int len = nums.size();  //total vector size
    if (len == 1) return 0; //unique solution
    int startPoint = 0;     //starting point to leap
    int leapsNum = 0;       //total count of leaps
    int leapLen = nums[0];  //len of current cealp

    //we find best leap. Condition -> next leap is MAX
    int maxLeapLen = -1;    //starting impossible value
    int maxLeanIndex = -1;
    while (startPoint + leapLen + 1 < len)
    {
        for (int i=0; i<leapLen+1; i++) //check next leap max len
        {
            if (nums[i+startPoint]+i > maxLeapLen)  //max len = leps where we leap + len of leap
            {
                maxLeapLen=nums[i+startPoint]+i;
                maxLeanIndex =i + startPoint;
            }
        }

        leapsNum++; //+1 leap
        leapLen = nums[maxLeanIndex];   //next leap value
        startPoint = maxLeanIndex;      //next leap starting point
        maxLeapLen = -1;                //clear tmp value
        maxLeanIndex = -1;              //clear tmp value
    }

    return leapsNum+1;
}
};

int main()
{
    Solution sol;
    vector<int> data41 {7,8,9,11,12};
    cout  << "missed int " << sol.firstMissingPositive(data41) << endl;

    vector<int> data45 {3,6,7,1,4,2,2,2,3,5,7,6,5,1,1,1,1,3};
    cout << "max jumps " << sol.jump(data45) << endl;

    return 0;
}

