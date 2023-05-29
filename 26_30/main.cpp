#include <iostream>
#include "routine.h"

using namespace std;

class Solution {
public:
    //https://leetcode.com/problems/remove-duplicates-from-sorted-array
    //#26 EASY
    int removeDuplicates(vector<int>& nums) {
        int totalPoints = nums.size();
        if (totalPoints<2) return totalPoints;  //if size==0 || size==1 cant contain duplicates
        int readPointer =1;                     //first element is uniques 100% skip it
        int savePointer =1;                     //first element is uniques 100% skip it
        while (readPointer<totalPoints) {       //read all elements
            if (nums[readPointer]!=nums[readPointer-1]) //if unique
            {
                nums[savePointer] = nums[readPointer];  //save it
                savePointer++;
            }
            readPointer++;
        }
        return savePointer;
    }
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
