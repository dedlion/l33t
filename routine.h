#ifndef ROUTINE_H
#define ROUTINE_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

//Definition for singly-linked list. from leetcode
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};


namespace routine {


template <class T>
    void showVector(const std::vector<T> & vec)
    {
        for (auto i : vec) std::cout << i << "  ";
        std::cout << std::endl;
    }

    template <class T>
    void showVectors(const std::vector<std::vector<T>> & vec)
    {
        for (auto i : vec) showVector(i);
        std::cout<< std::endl;
    }

    //my own func for dbg
    void showList(ListNode const * list)
    {
        while (list != nullptr)
        {
            std::cout << list->val << "  ";
            list = list->next;
        }
        std::cout<< std::endl;
    }

    //transfrom vector to ListNode*. Dbg only
    ListNode* generateList(const std::vector<int> & vec )
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
}


#endif // ROUTINE_H

