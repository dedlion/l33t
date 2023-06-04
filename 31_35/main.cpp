#include <iostream>
#include "routine.h"

using namespace std;


class Solution {
public:

    //https://leetcode.com/problems/next-permutation/
    //#31 MEDIUM
    //we sort digits with swap bcs they are reverse sorted
    void reverseSort(vector<int>& nums, int leftBorder) //routine function
    {
        int rightBorder = nums.size()-1;
        while (rightBorder>leftBorder)
        {
            swap(nums[rightBorder],nums[leftBorder]);
            rightBorder--;
            leftBorder++;
        }

    }

    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if (len<2) return;
        //find digit which bigger the next. 1 2 >3< change to 1 >3< 2

        //62873651  ->  62875631
        //123       ->  132
        for (int i=len-2; i>=0; i--)
        {
            if (nums[i]<nums[i+1])
            {
                //i-1 -> must be changed
                for (int l=len-1; l>i; l--)
                {
                    if (nums[l]>nums[i])
                    {
                        swap(nums[i],nums[l]);
                        reverseSort(nums,i+1);  //just sort digits [i+1:nums.size()-1]
                        return;
                    }
                }

            }
        }
        //this is max poss value. just sort ALL digits
        reverseSort(nums,0);

        return;
    }

    pair<int,int> checkSubString(string & s, bool reverse, int len)
    {
        const char openBracket = (!reverse)?'(':')';

        int resultValue = 0;
        int openBracketsCounter =0;
        int fullBrackets =0;
        int lastCharIndex=s.size()-1;
        int i=0;
        while (i<len)
        {
            const char & c = (reverse)?s.at(lastCharIndex-i):s.at(i);
            if (c==openBracket)
            {
                openBracketsCounter++;
            } else
            {
                if (openBracketsCounter>0)
                {
                    fullBrackets++;
                    openBracketsCounter--;
                } else
                {
                    resultValue=max(resultValue,fullBrackets*2);
                    fullBrackets=0;
                }
            }
            i++;
        }
        if (openBracketsCounter==0) //no spare letters
        {
            //substring is valid. no need to recheck
            resultValue=max(resultValue,fullBrackets*2);
            return {resultValue,0};
        }
        else
        {
            if (fullBrackets*2<resultValue)
                return {resultValue,0}; //who cares? in this substring in BEST variant still have not enoigh brackets
            else
                return {resultValue,openBracketsCounter+fullBrackets*2};    //may we need to recheck this substr
        }

    }

    int longestValidParentheses(string s) {

        pair <int,int> result = checkSubString(s,false,s.size());
        if (result.second==0) return result.first;

        //reverse search for last lastSubstrLen characters/
        //bcs exists string like ()(() . Right answer is 0
        //can be written subfunc.... with A LOT OF if: change character, change while direction, change starting point
        pair <int,int> reverseResult = checkSubString(s,true,result.second);

        return max(result.first,reverseResult.first);
    }

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
            currIndex = round((maxIndex + minIndex)/2.0f);  //new middle index. Can use ceil - doesnt matter

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
    //31
    vector<int> data_31{6,2,8,7,3,6,5,1};
    //vector<int> data_31{1,3,2};
    cout << "pr#31 input   ";
    routine::showVector(data_31);
    sol.nextPermutation(data_31);
    cout << "output  ";
    routine::showVector(data_31);

    //32
    cout << "brackets " << sol.longestValidParentheses("()()(())))((()(()()()(())()()()((()((((") << endl;

    //34
    vector<int> data_34{2,2};
    routine::showVector(sol.searchRange(data_34,2));

    //35
    vector<int> data_35{1,3,5,6};
    cout << " Index insert " << sol.searchInsert(data_35,2);
    return 0;
}

