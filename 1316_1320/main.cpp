#include <iostream>

using namespace std;

class Solution {
public:
    //https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c
    //#1318 MEDIUM
    int minFlips(int a, int b, int c) {
        //a || b == c
        int diffBits = (a|b)^c; //mask of diff bits
        int addDiffBits = a & b & diffBits;   //we need to chage 2 bits when 11 -> 0. So we can find this cases a&&b -> 11

        int res =0;
        const int BITS_INTEGER = sizeof(int) * 8;
        for (int i=0; i<BITS_INTEGER; i++)
        {
            res += (diffBits & 0x01) + (addDiffBits & 0x01);    //count number of 1 in this integers. take last bit
            diffBits = diffBits >> 1;                           //shift value
            addDiffBits = addDiffBits >> 1;
            if (addDiffBits==0 && diffBits==0) break;           //if both int is 0 no need to proceed
        }
        return res;
    }
};

int main()
{
    Solution sol;
    cout << "bit shifts " << sol.minFlips(1234142,1244,5)<<endl;

    return 0;
}

