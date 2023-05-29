#include <iostream>
#include "routine.h"

using namespace std;

class Solution {
public:
    //https://leetcode.com/problems/remove-duplicates-from-sorted-array
    //#26 EASY
    int removeDuplicates(vector<int>& nums) {
        int totalPoints = nums.size();
        if (totalPoints<2) return totalPoints;  //if size==0 || size==1 cant contain duplicates
        int readPointer =1;                     //first element is uniques 100% skip it
        int savePointer =1;                     //first element is uniques 100% skip it
        while (readPointer<totalPoints) {       //read all elements
            if (nums[readPointer]!=nums[readPointer-1]) //if unique
            {
                nums[savePointer] = nums[readPointer];  //save it
                savePointer++;
            }
            readPointer++;
        }
        return savePointer;
    }
    //https://leetcode.com/problems/remove-element/
    //#27 EASY
    int removeElement(vector<int>& nums, int val) {
        int totalPoints = nums.size();
        if (totalPoints==0) return totalPoints;
        int readPointer =0;
        int savePointer =0;
        while (readPointer<totalPoints) {       //read all elements
            if (nums[readPointer]!=val) //if unique
            {
                //if (savePointer!=readPointer)   //better in some circumstances
                    nums[savePointer] = nums[readPointer];  //save it
                savePointer++;
            }
            readPointer++;
        }
        return savePointer;
    }
    //https://leetcode.com/problems/divide-two-integers/
    //#29 MEDIUM
    const int MAX_POSS_DIVIS = 1<<30;    //1<<30-1 max number which can be *2 without overflow
    const int MAX_POSS_INT = 1<<30;
    int divide(int dividend, int divisor) {
        if (dividend==0) return 0;  //empty solution
        int copyDivisor = divisor;
        //we want positive numbers bcs solution based on bit shifts
        int sign =1;
        if ((dividend>0 && divisor<0)||(dividend<0 && divisor>0)) sign=-1;
        if (divisor==dividend) return sign; //simple solution
        //we have saved result sign. now we can take abs
        if (divisor!=INT_MIN)
            divisor = abs(divisor);
        else
            return 0; //variant divisor==dividend==INT_MIN already checked. So abs(divisor)>abs(dividend)

        bool addBit = false;
        if (dividend!=INT_MIN)
            dividend = abs(dividend);
        else
        {
            //abs(INT_MIN) = INT_MAX + 1/*additional_bit*/
            if (divisor==1) return (sign>0)?INT_MAX:INT_MIN;
            dividend = INT_MAX;
            addBit=true; //we remember that we have
        }



        if (divisor>dividend) return 0; //simple solution

        if (divisor==1) return (sign>0)?dividend:-dividend; //simple solution

        //find pow(divisor,power2)>=dividend AND divisor safely can mult by 2 wihout overflow
        //IDEA is to find result in binary variant
        //divisor = dividend*(2^n)*V[n] + dividend*(2^(n-1))*V[n-1] //V can be 1 or 0
        int power2 = 0;
        while(divisor < dividend && divisor<MAX_POSS_DIVIS)
        {
            power2++;
            divisor = divisor << 1;
        }

        //no we can calc V[]
        int result = 0;
        while (power2>=0 && dividend!=0) //dividend!=0 can be omitted.
        {
            if (dividend >= divisor)
            {
                dividend-=divisor;
                result+= 1 << power2; //if (V[n]==1) => dividend*(2^n)*V[n] == dividend*(2^n). Simply add 2^n to result
            }
            divisor = divisor >> 1;
            power2--;
        }
        //dividend was MIN_INT
        if (addBit)
        {
            if (dividend+1>=copyDivisor) result++;
        }


        return (sign>0)?result:-result;
    }
};


int main()
{
    //26 and 27 are very simple

    Solution sol;
    int dividend = -2147483648;
    int divisor = -3;

    cout<< "divide " <<sol.divide(dividend,divisor) << " vs " << dividend/divisor << endl;

    return 0;
}
