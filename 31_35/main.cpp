#include <iostream>
#include "routine.h"

using namespace std;


class Solution {
public:
    //https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
    //34 MEDIUM
    vector<int> searchRange(vector<int>& nums, int target) {
        if (nums.size()==0) return vector<int>{-1,-1};
        int minIndex = 0;
        int maxIndex = nums.size()-1;
        int currIndex = round((maxIndex - minIndex)/2.0f);  //we choose center between minIndex and MaxIndex

        while(nums[currIndex]!=target)  //while we have not found target
        {
            //bcs of non-decreasing order we can change border (left or right) to this index
            if (maxIndex==minIndex) return vector<int>{-1,-1}; //there is no target if two neighbor numbers are != target
            if (nums[currIndex]>target)
            {
                maxIndex=currIndex-1;   //currindex!=target so we can move border further
                if (maxIndex<0) return vector<int>{-1,-1};  //bcs of -1 in prev line. we should check here boundaries
            } else
            {
                minIndex=currIndex+1;   //currindex!=target so we can move border further
                if (minIndex>=nums.size()) return vector<int>{-1,-1};  //bcs of -1 in prev line. we should check here boundaries
            }
            currIndex = round((maxIndex + minIndex)/2.0f);  //new middle index
        }
        //check where is target starts
        vector<int> res;
        for (int i=currIndex-1; i>=0;i--)
        {
            if (nums[i]!=target)
            {
                res.push_back(i+1); //find index where is not target
                break;
            }
        }
        if (res.size()==0) res.push_back(0);    //first number is a target

        for (int i=currIndex+1; i<nums.size();i++)
        {
            if (nums[i]!=target)
            {
                res.push_back(i-1);//find index where is not target
                break;
            }
        }
        if (res.size()==1) res.push_back(nums.size()-1);    //last number is a target

        return res;
    }


    //https://leetcode.com/problems/search-insert-position
    //35 EASY
    int searchInsert(vector<int>& nums, int target) {

        if (nums.size()==0) return 0;
        if (nums.size()==1) return (target>nums.at(0))?1:0;

        if (target>nums.back()) return nums.size();
        if (target<nums.at(0)) return 0;

        int minIndex = 0;
        int maxIndex = nums.size()-1;
        int currIndex;  //we choose center between minIndex and MaxIndex

        while (maxIndex>=minIndex)  //while we have not found target)
        {
            currIndex = round((maxIndex + minIndex)/2.0f);  //new middle index

            if (nums[currIndex]==target) return currIndex;
            //bcs of non-decreasing order we can change border (left or right) to this index
            if (nums[currIndex]<target)
            {
                minIndex=currIndex+1;   //currindex!=target so we can move border further
            } else
            {
                maxIndex=currIndex-1;   //currindex!=target so we can move border further
            }
        }

        return minIndex;
    }

};

int main()
{
    Solution sol;
    //34
    vector<int> data_34{2,2};
    routine::showVector(sol.searchRange(data_34,2));

    //35
    vector<int> data_35{1,3,5,6};
    cout << " Index insert " << sol.searchInsert(data_35,2);
    return 0;
}

