#include <iostream>
#include "routine.h"

using namespace std;

//2696. Minimum String Length After Removing Substrings EASY
int minLength(string s) {
     int len = s.size();
    if (len==1) return 1;
    const char LEFT[2] = {'A','C'};
    const char RIGHT[2] = {'B','D'};

    string s2;
    s2.reserve(len);
    s2.push_back(s[0]); //add first letter. bcs no right part

    for (int i=1; i<len; i++)
    {
        if (s2.size()==0)
        {
            s2.push_back(s[i]);
            //no left part
        } else
        {
            if (((s[i] == RIGHT[0]) && (s2.back() == LEFT[0])) || ((s[i] == RIGHT[1]) && (s2.back() == LEFT[1])))
            {
                //pair. Remove letter and dont add new
                s2.pop_back();
            } else
            {
                //not pait. add letter
                s2.push_back(s[i]);
            }
        }
    }
    return s2.size();
}



int main()
{
    cout << "Problem 2696 -- " << minLength("CABCDD") <<endl;

    return 0;
}
