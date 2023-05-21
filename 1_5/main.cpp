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

//my own func for dbg
void showList(ListNode* list)
{
    while (list != nullptr)
    {
        cout << list->val << "  ";
        list = list->next;
    }
    cout<< endl;
}

//transfrom vector to ListNode*. Dbg only
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
                //AFTER solution submit:
                //people's solutions use map<c,freq> for frequency distribution. Faster soulution.
                while (find(FIFO.begin(), FIFO.end(), c) != FIFO.end()) {   //is there any same char
                    FIFO.pop_front();   //start deleting char from another side of deque (FIFO)
                }
                FIFO.push_back(c);  //we are here only if there is no char in deque

                result = max(result,static_cast<int>( FIFO.size() ));   //save max solution
            }
            return result;
        }

        //https://leetcode.com/problems/longest-palindromic-substring/
        //Problem #5  MEDIUM

        //routine function. to check how long is finded polindrome.
        //check string by expanping borders (left border of the substring anf right border of the string)
        string mirroring(string &s, int left, int right)
        {
            const int strLen = s.size();    //string length
            while (left>=0 && right<strLen)
            {
                if (s[left]==s[right])
                {
                    left--;
                    right++;
                } else
                {
                    break;
                }
            }
            //cancel last change. Can be moved to while, but less readable
            left++;
            right--;
            return s.substr(left,right-left+1);
        }

        string longestPalindrome(string s) {
            string bestSolution = string(1,s.at(0));  //guranteed s.length>0. Didnt know that word with 1 letter also is a palindrome word
            const int strLen = s.size();
            //cant use else. bcs "fasddddsaf" i+1 better then i+2
            for (int l=0;l<2; l++)  //change a?a and aa
            {
                for(int i=0; i<strLen-1-l; i++)
                {
                    if (s[i]==s[i+1+l]) //find center Palindromic string of aa OR a?a if l==1
                    {
                        string palindrom = mirroring(s,i,i+1+l);    //check len. atleast we have found string with 2 letters
                        if (palindrom.size()>bestSolution.size()) bestSolution=palindrom;   //save best word
                    }
                }
            }
            return bestSolution;
        }


        double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
            int totalValues = nums1.size() + nums2.size();
            if (totalValues==1)
            {
                if (nums1.size()==1)
                    return nums1.at(0);
                else
                    return nums2.at(0);
            }
            bool even = (totalValues%2==0)?true:false;
            int medianIndex = floor(totalValues/2);

            //we try find
            return 0; //SKIPPED. NOT FINISHED. May be i will return later. too late already.

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
    cout << "max len " << sol.lengthOfLongestSubstring("abcaderfb0+cbb") << endl;

    //Problem #4
    vector<int> case4_1 {};
    vector<int> case4_2 {4,5};
    cout << "median value " <<  sol.findMedianSortedArrays(case4_1,case4_2) << endl;

    //Problem #5
    cout << "max str " << sol.longestPalindrome("bb") << endl;
    return 0;
}

