#include <iostream>
#include "routine.h"
using namespace std;


class Solution {
public:

    //https://leetcode.com/problems/sort-integers-by-the-number-of-1-bits
    //#1356 EASY

    //find number of ones
    short numOfOnes(int a)
    {
        short res=0;
        while (a>0) {
            res += a & 0x01;    //take least sign. bit
            a = a >> 1;         //shift it left == /2
        }
        return res;             //return number of bits
    }

    vector<int> sortByBits(vector<int>& arr) {
        //in first iteration i used map, to store nubmer of bits. I thought map find will be faster then call functions. i was wrong.

        //sort using lambda
        sort(arr.begin(), arr.end(), [this](int & a, int &b){
            short a_ones = numOfOnes(a);
            short b_ones = numOfOnes(a);
            if (a_ones==b_ones)
                return a<b;
            else
                return a_ones<b_ones;

            });
        return arr;
    }


    //https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/
    //#1359 HARD

    //just find number of degrees of freedom
    //we check what can be in every cell. There can be not used P's and possible D's for used P's == D-P
    //SLOW... NOT USED in real solution
    //but i used it to get math function. First Multiplier is n!

    /*
    void recursion(int P, int D, int n, long long currMult, int & Result)
    {
        if (P>D) return;
        if (D>0)
        {
            //sum of this elemrnts is second muliplier
            this->recursion(P,D-1,n,currMult * (D-P)  % MODULO,Result); //can only be D-P variants
        }
        if (P>0)
        {
            //!!!!!!!!!!!
            //can be P variants --> n! in totalResult. THIS IS FIRST MULTIPLIER
            //bcs obviously we will go through all P=1..n
            this->recursion(P-1,D,n,currMult*P  % MODULO ,Result);
        }
        if (P==0 && D==0)
        {
            Result += currMult;
            Result = Result % MODULO;
        }
    }
   */

    /*
     *   6  / 2! = 3            ... / 1   = 3
     *   90 / 3! = 15           ... / 3   = 5
     *   2520 / 4! = 105        ... / 15  = 7
     *   113400 / 5! = 945      ... / 105 = 9
     *   7484400 / 6!	= 10395 ... / 945 = 11
    */
    const int MODULO = 1e9+7;
    int countOrders(int n) {
        int Result = 0;
        //Result = n! * seq
        //n!  *= k          k E [1,n]
        //seq *= 2*k-1      k E [1,n]

        long fact = 1;  //start value
        long seq  = 1;  //start value
        for (int i=2; i<=n; i++)    //problem solved for n==1, can skip i==1
        {
            fact = fact * i % MODULO;       //factorial obv
            seq = seq * (2*i-1) % MODULO;
        }
        Result = fact * seq % MODULO;

        return Result;
    }
};


int main()
{
    Solution sol;
    cout << " total variants " << sol.countOrders(6) << endl;

    vector<int> values {1111,7644,1107,6978,8742,1,7403,7694,9193,4401,377,8641,5311,624,3554,6631};
    cout << "test by bits" ;
    routine::showVector(  sol.sortByBits(values));

    return 0;
}

