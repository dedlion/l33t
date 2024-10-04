#include <iostream>
#include "routine.h"

using namespace std;

//PROBLEM 56 MEDIUM
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> result;
    int len = intervals.size();
    //just sort vectors based on their starts
    std::sort(intervals.begin(), intervals.end(), [](vector<int> & a, vector<int> & b){ return a[0]<b[0];});

    int i =0;
    while (i <  len) //all intervals
    {
        int startInterval = intervals[i][0];
        int endInterval = intervals[i][1];
        i++;
        if (i<len)  //check vector end
        {
            while (intervals[i][0]<=endInterval) //while start of the next vector is inside curr vector
            {
                endInterval = max(endInterval,intervals[i][1]); //merge it with curr vector
                i++;
                if (i==len) break;  //check vector end
            }
        }
        result.push_back({startInterval, endInterval});  //add merged vector to result vector
    }
    return result;
}

int main()
{
    std::vector<std::vector<int>> input56 = {{4,5},{1,4},{7,8}};
    cout << "problem 56 " <<endl;
    routine::showVectors(merge(input56)) ;
    return 0;
}
