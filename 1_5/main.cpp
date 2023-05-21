#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>

using namespace std;
template <class T>
void showVector(const vector<T> vec)
{
    for (auto i : vec) cout << i << "  ";
    cout<< endl;
}

//Definition for singly-linked list. from leetcode
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

void showList(ListNode* list)
{
    while (list != nullptr)
    {
        cout << list->val << "  ";
        list = list->next;
    }
    cout<< endl;
}

//transfrom vector to ListNode*
ListNode* generateList(const vector<int> & vec )
{
    if (vec.size()==0) return new ListNode();
    ListNode * end = new ListNode(vec[vec.size()-1]); //last value
    ListNode * start = end ;    //in case size()==1
    for (int i=vec.size()-2;i>=0;i--) //reverse
    {
        start = new ListNode(vec.at(i),start);
    }
    return start;
}



class Solution {
public:
    //https://leetcode.com/problems/two-sum/
    //Problem #1  EASY
    //fast but not best for memory solution
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


    //https://leetcode.com/problems/add-two-numbers/
    //Problem #2  MEDIUM

    //routine funciton. get next pointer if possible. output = value or 0
    ListNode* getValue(ListNode* input, int * output)
    {
        if (input!=nullptr)
        {
            *output = input->val;
            return input->next;
        } else
        {
            *output =0;
            return input;
        }
    }

    /* My first idea was to create vector with values and transfrom them to ListNode see ::generateList()
     * But on leetcode you fight for speed and memory consuption so after first valid solution
     * i changed my code for better performance now results stored in input L1
    */
      ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        //we emulate сolumn summation
        int valueToStore = 0;  //number of decades from prev sum
        ListNode* startL1 = l1;
        ListNode* pointerToSave = l1;
        bool nextDigitIsValid = true;
        while(nextDigitIsValid)
        {
            int value1, value2;
            l1 = getValue(l1,&value1);  //get value from pointer and shift it
            l2 = getValue(l2,&value2);
            int sum = value1 + value2 + valueToStore;   //sum value and decades from prev step

            int valueToSave = sum%10;
            valueToStore = (sum>9)?1:0; //decades (carry) for next loop. OR //valueToStore = (sum - valueToSave)/10;

            nextDigitIsValid = l1!= nullptr || l2!= nullptr || valueToStore!=0; //check exit condition now bcs we want ot know do we need next item in List
            if (pointerToSave->next == nullptr)
            {
                if (nextDigitIsValid)   //create ne new element if needed
                {
                    pointerToSave->next = new ListNode();
                }
            }
            pointerToSave->val=valueToSave;
            pointerToSave = pointerToSave->next;
        }
        return startL1;
    }


        //https://leetcode.com/problems/longest-substring-without-repeating-characters/
        //Problem #3  MEDIUM
        int lengthOfLongestSubstring(string s) {
            int result = 0;
            std::deque<char> FIFO;
            for(char& c : s)
            {
                while (find(FIFO.begin(), FIFO.end(), c) != FIFO.end()) {
                    FIFO.pop_front();
                }
                FIFO.push_back(c);

                result = max(result,static_cast<int>( FIFO.size() ));
            }
            return result;
        }


};

int main()
{
    Solution sol; //make instance
    //Problem #1
    vector<int> case1_1 {2,7,11,15};
    showVector(sol.twoSum(case1_1,9));

    //Problem #2
    vector<int> case2_1 {2,4,3};
    vector<int> case2_2 {5,6,4};
    ListNode * l1 = generateList(case2_1);
    ListNode * l2 = generateList(case2_2);
    ListNode * result = sol.addTwoNumbers(l1,l2);
    showList(result);

    //Problem #3
    cout << "max len" << sol.lengthOfLongestSubstring("abcaderfb0+cbb") << endl;

    return 0;
}

