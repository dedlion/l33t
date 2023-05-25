#include <iostream>
#include "routine.h" //some common headers and functions ./../

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
};

int main()
{
    Solution sol;

    ListNode * head = routine::generateList(std::initializer_list<int>{1,2});
    ListNode * newList = sol.removeNthFromEnd(head,1);
    cout << "new list ";
    routine::showList(newList);
    cout << endl;

    return 0;
}

