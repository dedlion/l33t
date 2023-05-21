#include <iostream>
#include <vector>
#include <algorithm>
#include "array"
#include "bitset"

using namespace std;

//https://leetcode.com/problems/the-k-weakest-rows-in-a-matrix/   //#1337 Easy

vector<int> kWeakestRows(vector<vector<int>>& mat, int k) {
    vector<int> result ;
    int m = mat.size(); //rows
    std::vector<std::pair<int,int>> STRcounter;
    for (int i=0;i<m;i++)
    {
        //because we have only 0 and 1, we can just find sum of all numbers in row. Not fastest but simple solution
        STRcounter.push_back({std::accumulate(mat.at(i).begin(), mat.at(i).end(), 0),i});   //pair <STR,row>
    }
    //sort them manually by first value in pair
    //we can use set instead of vector for autosorting but this is less readable and slower solution
    std::sort( STRcounter.begin(),STRcounter.end() );

    for (int i=0;i<k;i++)   //take k weakest rows (i.second)
    {
        result.push_back(STRcounter.at(i).second);
    }
    return result;
}

struct ListNode {
    int val;
     ListNode *next;
     ListNode() : val(0), next(nullptr) {}
     ListNode(int x) : val(x), next(nullptr) {}
     ListNode(int x, ListNode *next) : val(x), next(next) {}

};

//https://leetcode.com/problems/maximum-twin-sum-of-a-linked-list
int pairSum(ListNode* head) {
    //BruteForce Solution heavy on memory but simple

    //Make deep copy to std::vector
    std::vector<int> allData;
    while (head!=nullptr)
    {
        allData.push_back(head->val);
        head = head->next;
    }
    int len = allData.size(); //len > 2 guranteed. No need to check
    int halfLen = len/2; //len is even. No need to check

    //just find max sum
    int maxValue=0;
    for (int i=0 ; i<halfLen; i++)
    {
        int sum = allData[i] + allData[len-i-1];
        maxValue = std::max(sum,maxValue);
    }
    return maxValue;
}

int firstMissingPositive(vector<int>& nums) {
    //another straightforward solution
    const int MAX_MISSED_VAL  =  10e5+1; //in worst case scenario we need this amount of memory
    //create map of recieved numbers
    bitset<MAX_MISSED_VAL> map {0};
    map[0]=true; //zero is not positive autoskip
    for (auto i : nums)
    {
        if (i>0 && i<MAX_MISSED_VAL)
            map[i]=true;   //skip this value
    }
    //return distance( begin(map), find_if( begin(map), end(map), [](int x) { return x == false; })); //first zero is missed int

}
//2407. Longest Increasing Subsequence II

int main()
{
    vector<vector<int>> mat = {{1,1,0,0,0},{1,1,1,1,0},{1,0,0,0,0},{1,1,0,0,0},{1,1,1,1,1}};    //use case 1
    vector<int> res = kWeakestRows(mat,3);  //use case 1

    for (auto i: res)
    {
        cout << i << " ";
    }

    vector<int> test = {3,4,-1,1};
    cout << " res " << firstMissingPositive(test);
    return 0;
}

