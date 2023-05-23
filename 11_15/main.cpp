#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
    //https://leetcode.com/problems/container-with-most-water/
    //Problem #11 MEDIUM
    int maxArea(vector<int>& height) {
        if (height.size()==0) return 0;
        auto left = height.begin(); //leftmost iterator
        auto right = height.end();  //rightmost iterator
        right--;    //make it valid
        int maxPoolSize = min((*left) , (*right)) *(right-left);    //startingValue in case vec.size()==1
        //idea here move iterator from the sides to center
        while (left!=right) //while there is no more combination
        {
            if (*left<*right)   //we move iterator with smaller value. If they == doesnt mater which one
            {
                left++;
            } else
            {
                right--;
            }
            //we can calculate only if newer value is big enough.
            //but math is simple - IMO faster to calc then check is there need to calc
            int poolSize = min((*left) , (*right)) *(right-left);
            maxPoolSize = max( poolSize , maxPoolSize);
        }
        return maxPoolSize;
    }

    //https://leetcode.com/problems/longest-common-prefix/
    //Problem #14 EASY
    string longestCommonPrefix(vector<string>& strs) {

    if (strs.size()==0) return 0;   //empty vector
    string firstWord = strs.at(0);
    int firstWordLen = firstWord.size();
    if (strs.size()==1) return firstWord;   //only 1 word solution
    int totalWords = strs.size();
    int letters =0;
    for (int i=0; i<firstWordLen;i++)   //check all letters
    {
        for(int w=1; w<totalWords; w++) //check all words
        {
            if (strs[w][i] != firstWord[i]) //check letter in word
            {
                return firstWord.substr(0,letters); //if not eq return first "letters" letters
            }
        }
        letters++;
    }
    return firstWord;   //return full word
    }
};


int main()
{
    Solution sol;
    //11#
    vector<int> vec_11_1 = {1,8,6,2,5,4,8,3,7};
    cout << "maxArea" << sol.maxArea(vec_11_1) << endl;

    //14#
    vector<string> vec_14_1 = {"flower","flow","flight"};
    cout << " res14 " <<  sol.longestCommonPrefix(vec_14_1) << endl;

    return 0;
}

