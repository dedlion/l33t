#include <iostream>
#include "routine.h"
#include "queue"
using namespace std;


class Solution {
public:
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

    //23
    routine::showList( sol.mergeKLists(input));



    return 0;
}

