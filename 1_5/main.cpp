#include <iostream>
#include <vector>
#include <map>

using namespace std;
template <class T>
void showVector(const vector<T> vec)
{
    for (auto i : vec) cout << i << "  ";
    cout<< endl;
}

//https://leetcode.com/problems/two-sum/
//Problem #1  EASY
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        map<int,int> possibleVariants; //{possible variant, base index}
        int vecSize = nums.size(); //hust dont want to call it every loop
        for (int i=0; i<vecSize; i++)
        {
            auto it = possibleVariants.find(nums[i]); //find self. have gurantee im in borders no need in at(i)
            if (it==possibleVariants.end()) //is there solution
            {
                //add new possible variant. if we will find it later - this is solution
                int secondValue = target - nums[i];
                possibleVariants[secondValue]=i;
            } else
            {
                //we have found solution
                vector<int> result;
                result.push_back(i);
                result.push_back( it->second );
                return result;
            }
        }
        vector<int> emptyResult {-1,-1};//just in case
        return emptyResult;
    }


};

int main()
{
    Solution sol; //make instance
    //Problem #1
    vector<int> case1_1 {2,7,11,15};
    showVector(sol.twoSum(case1_1,9));

    return 0;
}

