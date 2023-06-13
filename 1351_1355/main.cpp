#include <iostream>
#include "routine.h"
#include "memory"
#include <algorithm>
#include <queue>

using namespace std;


class Solution {
public:
    //https://leetcode.com/problems/count-negative-numbers-in-a-sorted-matrix/
    //#1351 EASY
    int countNegatives(vector<vector<int>>& grid) {
        int height = grid.size();
        int width = grid.at(0).size();  //grid[x][y]

        int x=width-1;
        int y=height-1;
        int res=0;
        //find bottom keft positive value
        while (x>=0)
        {
            if (grid[y][x]>=0)
            {
                break;
            } else
            {
                res++;
            }
            x--;
        }
        y--;
        if (x==-1) x=0; //if all numbers are negative


        //we go zig-zag till we find negaive number
        while (y>=0)    //move up
        {
            while (x<width) //move right
            {
                if (grid[y][x]<0)
                {
                    res++;
                    break;   //positive
                }
                x++;//move right
            }
            if (x==width) return res;    //if all numbers is positive
            res+=width-x-1;
            y--;//move up
        }
        return res;
    }

    //https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/
    //#1353  MEDIUM
    int maxEvents(vector<vector<int>>& events) {
        int len = events.size();
        if (len==0) return 0;
        //sort to simplify code below by starting day
        sort(events.begin(), events.end(), [](vector<int> & a, vector<int> & b){ return b.at(0)>a.at(0); });

        int eventsDone =0;
        int currDay = events.at(0).at(0);
        priority_queue<int, vector<int>, std::greater<int> > Q;
        int i=0;
        while (i<len || Q.size()>0) //while have new events OR have events in Q
        {
            if (Q.size()>0) //Q not empty
            {
                Q.pop();        //get event with best priority (priority = endDay - currDay). Less is more priority
                eventsDone++;   //event is done
                currDay++;      //currDay

                //Delete all events which cannot be done
                while (Q.size()>0)
                {
                    if (Q.top()-currDay<0)
                        Q.pop();
                    else
                        break;
                }
                //add new events from new currDay
                while (i<len && events.at(i).at(0)==currDay)
                {
                    Q.push(events.at(i).at(1));
                    i++;
                }
            } else
            {
                //No events in Q. lets jump to closest event and add all events with this startDay
                if (i<len)
                {
                    currDay= events.at(i).at(0);
                    while (i<len && events.at(i).at(0)==currDay)
                    {
                        Q.push(events.at(i).at(1));
                        i++;
                    }
                }
            }
        }
        return eventsDone;
    }
};

//https://leetcode.com/problems/product-of-the-last-k-numbers/
//#1352 MEDIUM
class ProductOfNumbers {
public:
    vector <int> memory;
    //we will save not numbers but possible results
    ProductOfNumbers() {

    }

    void add(int num) {
        if (num==0)
        {
            //X * 0 == 0... no need to save data anymore
            memory.clear();
        } else
        {
            //mult everything by input
            //adding data is slow BUT getProduct will be FAST
            if (num!=1)
            {
                for (auto & i : memory)
                {
                    i = i*num;
                }
            }
            memory.push_back(num);  //self*1
        }
    }

    int getProduct(int k) {
        if (k>memory.size()) return 0;
        int reverseIndex = memory.size()-k; //k==1 -> reverseIndex==memory.size()-1
        return memory[reverseIndex];
    }
};


int main()
{
    Solution sol;
    vector<vector<int>> data_1351 = {{4,3,2,-1},{3,2,1,-1},{1,1,-1,-2},{-1,-1,-2,-3}};
    vector<vector<int>> data_1351_2 = {{7,-5}};
    cout << " negatives count " << sol.countNegatives(data_1351_2) << endl;

    ProductOfNumbers pr;
    pr.add(1);
    pr.add(3);
    pr.add(0);
    cout << "product value " <<pr.getProduct(3) << endl;

    vector<vector<int>> data_1353 = {{1,4},{4,4},{2,2},{3,4},{1,1}};
    vector<vector<int>> data_1353_2 = {{1,2},{2,3},{3,4},{1,2}};
    cout << "max events" << sol.maxEvents(data_1353_2) << endl;
    return 0;
}

