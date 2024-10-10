#include <iostream>
#include "routine.h"

using namespace std;
//61. Rotate List MEDIUM
ListNode* rotateRight(ListNode* head, int k) {
       if (head==nullptr) return head;
       ListNode* saveHead = head;
       int len = 1;
       while (head->next!=nullptr)
       {
           head = head->next;
           len++;
       }
       if (len==1) return head;
       int shift = k % len;            //number of "left shifts"
       if (shift==0) return saveHead;  //no need to change anything
       int whereToBreak = len-1-shift; //number of right shifts

       head->next = saveHead; //make list infinite;
       for (int i=0; i<whereToBreak; i++)  //find where to break
       {
           saveHead = saveHead->next;
       }
       head = saveHead->next;  //save future start of list
       saveHead->next =  nullptr;  //break list here
       return head;

   }


int main()
{
    std::vector<int> data61 {1,2,3,4,5,6,7};
    cout << "61 >> " << endl;
    routine::showList(rotateRight(routine::generateList(data61),5));

    return 0;
}
