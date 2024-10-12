#include <iostream>
#include "routine.h"

using namespace std;
//2406. Divide Intervals Into Minimum Number of Groups
//third iteration of algo
int minGroups(vector<vector<int>>& intervals) {
    std::vector<int> borders(1e6+1); //here we are preallocate mem. to increase speed, in real work must me dynamical allocated
    //add groups border
    for (auto & i : intervals)
    {
        borders[i[0]-1]++; //start group... we do -1 bcs groups cant overlap
        borders[i[1]]--;   //end group
    }
    //we count max amount of overlapping grousp
    int groups =0;
    int currValue = 0;
    for (auto i : borders)
    {
        currValue +=  i;                    //curr overlap count
        groups = max(groups,currValue);     //max overllap count
    }
    return groups;
}
int main()
{
    std::vector<std::vector<int>>data2406 {{5,10},{6,8},{1,5},{2,3},{1,10}};
    cout << "2406 >> "<< minGroups(data2406) << endl;
    return 0;
}
