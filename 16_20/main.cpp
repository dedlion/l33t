#include <iostream>
#include "routine.h" //some common headers and functions ./../
#include "queue"
#include "stack"

using namespace std;


class Solution {
public:
    //https://leetcode.com/problems/remove-nth-node-from-end-of-list/
    //#19 MEDIUM
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if (head==nullptr || head->next==nullptr) return nullptr;   //if len==0 OR len==1
        ListNode * pointer = head;  //make pointer copy
        int len =1; //we have atleast 1 value
        //Get list LEN
        while (pointer->next!=nullptr)
        {
            pointer = pointer->next;
            len++;
        }
        if (len==n) return head->next; //if we need to kill first element

        int indexPointerToChange = len - n - 1; //index of element BEFORE (-1) needed
        pointer = head;  //make pointer copy
        //Find pointer BEFORE (-1) needed
        while (indexPointerToChange!=0)
        {
            pointer = pointer->next;
            indexPointerToChange--;
        }
        ListNode * pointerToChange = pointer;   //Save it
        pointer = pointer->next;    //we can be sure next is exists
        pointerToChange->next = pointer->next;  //Relink

        return head;
    }


    //https://leetcode.com/problems/letter-combinations-of-a-phone-number/
    //17 MEDIUM
    const vector<vector<char>> PHONE_LETTERS = {{/*0*/},{/*1*/},{'a','b','c'},{'d','e','f'},{'g','h','i'},{'j','k','l'},{'m','n','o'},{'p','q','r','s'},{'t','u','v'},{'w','x','y','z'},{/*9*/}};
    //internal funct for problem #17
    void recursion(int num, vector<int> & indexNums ,vector<string> &result, const vector<vector<char>> & letters)
    {
        int startValue = indexNums.at(num);  //we save starting position of index == max possible index
        for (int i=startValue; i>=0; i--)   //iterate all possible variants of THIS index
        {
            indexNums[num]=i;    //change index for recursion call
            if (num==0)
            {
                //end of recursion. Add word based on indexes num
                string word;
                int wordSize = letters.size();
                word.resize(wordSize);
                for (int l=0; l<wordSize;l++)
                {
                    word[l]=letters[l][indexNums[l]];   //fill string with letters
                }
                result.push_back(word); //add result
            } else
            {
                recursion(num-1,indexNums,result, letters); //iterate through all posible letters positioned roght to target (num)
            }
        }
        indexNums.at(num)=startValue;
    }
    //problem #17 Main func
    vector<string> letterCombinations(string digits) {
        vector<int> indexNums;
        vector<vector<char>> letters;
        int resultLen=1;
        for (auto i : digits)
        {
            int num = static_cast<int>(i)-48; //can be done with map<> OR stoi
            if (num>=0 && num<10)             //character is valid
            {
                letters.push_back(PHONE_LETTERS.at(num));   //this will be const array of possible letters for eash position
                resultLen = resultLen * PHONE_LETTERS.at(num).size();   //this is how many possible variantss  we can have
                indexNums.push_back(PHONE_LETTERS.at(num).size()-1);     //this indexes for letters in this word
            }
        }
        vector<string> result;
        if (indexNums.size()==0) return result;
        result.reserve(resultLen);
        recursion(indexNums.size()-1,indexNums,result,letters);
        return result;
    }
    //https://leetcode.com/problems/valid-parentheses/
    //problem #20 EASY
    bool isValid(string s) {
        stack<char> st; //idea is simple. closing bracket must match last open bracket
        for (auto i : s)
        {
            if (i=='[' || i=='(' || i=='{')
            {
                st.push(i); //save open bracket
            } else
            {
                //check closing bracket
                if (st.size()==0) return false;
                if (i==']') if (st.top()=='[') st.pop(); else return false;
                if (i=='}') if (st.top()=='{') st.pop(); else return false;
                if (i==')') if (st.top()=='(') st.pop(); else return false;
            }
        }
        if (st.size()!=0) return false;
        return true;
    }

};

int main()
{
    Solution sol;
    //17#
    cout << "phone letters : ";
    routine::showVector(sol.letterCombinations("223"));

    //#19
    ListNode * head = routine::generateList(std::initializer_list<int>{1,2});
    ListNode * newList = sol.removeNthFromEnd(head,1);
    cout << "new list ";
    routine::showList(newList);
    cout << endl;

    //#20
    cout << "valid bracker " << sol.isValid("{}[](())") << endl;

    return 0;
}

