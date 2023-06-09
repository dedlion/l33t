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
};

int main()
{
    Solution sol;
    vector<int> data41 {7,8,9,11,12};
    cout  << "missed int " << sol.firstMissingPositive(data41) << endl;

    return 0;
}

