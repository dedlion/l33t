#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Solution {
public:
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

    //14#
    vector<string> vec_14_1 = {"flower","flow","flight"};
    cout << " res14 " <<  sol.longestCommonPrefix(vec_14_1) << endl;

    return 0;
}

