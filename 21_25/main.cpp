#include <iostream>
#include "routine.h"
#include "queue"
#include <bitset>

using namespace std;


class Solution {
public:
    //https://leetcode.com/problems/merge-two-sorted-lists
    //Ptroblem 21 EASY
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode * head;

        if (list1==nullptr) return list2;   //second list is sorted no need to do anything
        if (list2==nullptr) return list1;   //second list is sorted no need to do anything

        if (list1->val < list2->val)    //find start of new linked list
        {
            head = list1;
            list1 = list1->next;        //"rotate" used list
        } else
        {
            head = list2;
            list2 = list2->next;        //"rotate" used list
        }
        ListNode * copyHead = head;

        while (list1!=nullptr && list2!=nullptr) {  //link while both lists are valid
            if (list1->val < list2->val)
            {
                head->next = list1; //link
                list1 = list1->next;//"rotate"
            } else
            {
                head->next = list2; //link
                list2 = list2->next;//"rotate"
            }
            head=head->next;
        }

        //when one list is empty. we just lnk another list (it is already sorted)
        if (list1==nullptr)
            head->next=list2;
        else
            head->next=list1;

        return copyHead;
    }

    //https://leetcode.com/problems/generate-parentheses/
    //#22 MEDIUM
    void bracketRecursion(string input, vector<string> & res, int canAddBrackets, int openBrackets)
    {
        if (openBrackets>0)
        {
            //can close bracket
            bracketRecursion(input+")", res, canAddBrackets, openBrackets-1);  //1 closed bracket
        }
        if (canAddBrackets>0)
        {
            //can open new bracket
            bracketRecursion(input+"(", res, canAddBrackets-1, openBrackets+1); //1 new open bracket
        }
        if (canAddBrackets==0 && openBrackets==0)
        {
            //no more freedom. add to result
            res.push_back(input);
        }
    }

    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if (n==0) return result;    //empty variant
        string word{"("};                //empty word. Always start with "("
        //word.reserve(n*2);          //word have n*2 chars... Tests have showed this is bad idead, bcs of a lot of copy
        //signature (currentWord, result vector
        bracketRecursion(word, result, n-1,1);  //start recursion. canAddBrackets=n-1 (already used 1)
        return result;
    }

//https://leetcode.com/problems/merge-k-sorted-lists/
//23# HARD
ListNode* mergeKLists(vector<ListNode*>& lists) {

    //get count of linked lists
    int listsCount = lists.size();
    if (listsCount==0) return nullptr;

    //reversed priority Q. We are compare first int in pair
    priority_queue<pair<int,int>, vector<pair<int,int>> , std::greater<pair<int,int>>> headsValues;

    for (int i=0; i<listsCount; i++)
    {
        if (lists[i]!=nullptr)
        {
            headsValues.push({lists[i]->val,i});
        }
    }
    //Find Head (start) lowest value
    if (headsValues.size()==0) return nullptr; //no valid values
    int index = headsValues.top().second;   //index of
    ListNode * head = lists[index]; //this is head for me to link
    ListNode * returnHead = head;       //this is head pointer to return

    //remove head from queue
    headsValues.pop();
    lists[index] = lists[index]->next;  //"rotate" vector
    if (lists[index]!=nullptr)  //add new value if possible
    {
        headsValues.push({lists[index]->val,index});
    }

    while(headsValues.size()>0) //while there is data to link
    {
        pair<int,int> nextBest = headsValues.top(); //get next best value
        index = nextBest.second;                    //take num of Linked list
        head->next = lists[index];                  //link it to our head
        head = head->next;                          //change currHead
        headsValues.pop();                          //delete from priority_queue data
        lists[index] = lists[index]->next;          //get next node in used linked list
        if (lists[index]!=nullptr)                  //check there is new data in used link list
        {
            headsValues.push({lists[index]->val,index});    //add new data from used linked list
        }
        //find new value
    }

    return returnHead;
}

};

int main()
{
    Solution sol;

    vector <int> d1 {1,4,5};
    ListNode * first = routine::generateList(d1);
    vector <int> d2 {1,3,4};
    ListNode * second = routine::generateList(d2);
    vector <int> d3 {2,6};
    ListNode * third = routine::generateList(d3);
    vector <ListNode *> input {first, second, third};

    //22
    cout << "brakcets generate" ;
    routine::showVector( sol.generateParenthesis(3));
    //23
    routine::showList( sol.mergeKLists(input));



    return 0;
}

