#include <iostream>
#include "routine.h"

using namespace std;


class Solution {
public:
    //https://leetcode.com/problems/powx-n/
    //#50 MEDIUM
    double myPow(double x, int n) {
        if (n == 0) return 1.0;   //x^0==0
        if (abs(x) < std::numeric_limits<double>::epsilon() ) return 0.0; //0^x = 0 if x>0
        if (abs(abs(x)-1.0) < std::numeric_limits<double>::epsilon() )  //if x==1 OR x==-1
        {
            if (x>0)    //x==1
                return 1.0; //1^n=1
            else
                return (n%2==0)?1.0:-1.0;  //-1^n=1 or -1
        }
        double res; //result

        //if power is negative
        if (n<0)
        {
            x = 1.0/x;
            if (n==INT_MIN)
            {
                n=INT_MAX;
                res = x * x;
            } else
            {
                n = -n;
                res = x;
            }
        } else
        {
            res = x;
        }
        //make multiplying

        while (n>1)
        {
            res = res * x;
            n--;
            if (abs(res) < std::numeric_limits<double>::epsilon() ) return 0.0; //no point to mult further
        }
        return res;
    }
};

int main()
{
    Solution sol;
    cout << "power" << sol.myPow(11,11)<< endl;
    return 0;
}

