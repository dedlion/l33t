#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

template <class T>
void showVector(const vector<T> vec)
{
    for (auto i : vec) cout << i << "  ";
    cout<< endl;
}
template <class T>
void showVectors(const vector<vector<T>> vec)
{
    for (auto i : vec) showVector(i);
    cout<< endl;
}


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


    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> result;
        map<int,int> positive;
        map<int, int> negative;
        int zeroes=0;
        //create tw0 separate sets for + and - values
        for (auto i : nums)
        {
            if (i>=0)
            {
                positive[i]++;
                if (i==0)
                {
                    zeroes++;
                    negative[i]++;
                }
            }
            else
                negative[i]++;
            }

           if (zeroes==2) positive[0]--; //{0,0,X} != 0


           for (auto i = positive.begin(); i!=positive.end(); i++)
           {
               for (auto l = negative.begin(); l!=negative.end(); l++)
               {
                   int value = -(i->first + l->first); //we need to find this number A+B+C=0 -> A+B=-C
                   if (value>=0)
                   {
                       //search in positive
                       if (i->first == value)   //SAME l->first == 2 * i->first ;
                       {
                           if (i->second>1)
                           {
                               //viable {+i, +i, -2*i}
                               result.emplace_back(std::initializer_list<int>{i->first,i->first,l->first});
                           }
                       } else
                       {
                           if (value < i->first ) continue;
                           auto search = positive.find(value);
                           if (search != positive.end())
                           {
                               //viable {+i, -l, +search}
                               result.emplace_back(std::initializer_list<int>{i->first,l->first,search->first});
                           }
                       }
                   } else
                   {
                       //search in negative
                       if (l->first == value)   //SAME i->first == 2 * l->first ;
                       {
                           if (l->second>1)
                           {
                               //viable {+i, -i/2, -i/2}
                               result.emplace_back(std::initializer_list<int>{i->first,l->first,l->first});
                           }
                       } else
                       {
                           if (value < l->first ) continue;
                           auto search = negative.find(value);
                           if (search != negative.end())
                           {
                               //viable {+i, -l, -search}
                               result.emplace_back(std::initializer_list<int>{i->first,l->first,search->first});
                           }
                       }
                   }
               }
           }
           return result;
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

    //15#
    vector<int> vec_15_1 = {1,-1,0,0,-2,-2,4,1,-3,2};
    showVectors(sol.threeSum(vec_15_1));
    return 0;
}

