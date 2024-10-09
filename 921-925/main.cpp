#include <iostream>
#include "routine.h"
using namespace std;
//921. Minimum Add to Make Parentheses Valid MEDIUM DAILY
int minAddToMakeValid(string s) {
    const char LEFT_BRACKET = '(';
    if (s.size()==0) return 0;

    int balancer =0;    //this is amoun of unbalanced left brackets
    int errors = 0;
    for (int i=0; i<s.size(); i++)
    {
        if (s[i]==LEFT_BRACKET)
            balancer++; //open bracket
        else
            if (balancer>0)
                balancer--; //closed bracket
            else
                errors++;  //non opened bracket
    }
    return errors+balancer; //non opened + non closed brackets
}


//922 Sort array by parity II
inline bool isNonEven(int val)
{
    return (val & 0x01); //old school. just want to check diff with %
    //return (val % 2);
}

vector<int> sortArrayByParityII(vector<int>& nums) {
    //not best solution. my idea was to swap if errors rate ere low.
    //but after checking results faster idea was createeeeeeeeeeeeeeeee result vector from the scratch
    int indexEven =0;
    int indexNonEven =1;
    int len = nums.size();
    while (indexEven < len) //this loop only on even indexes
    {
        if (isNonEven(nums[indexEven])) //if not even number in even index
        {
            //lets find even number in not even index and swap them
            while (isNonEven(nums[indexNonEven]))
            {
                indexNonEven+=2;
            }
            swap(nums[indexNonEven],nums[indexEven]);
            indexNonEven+=2;    //iterate noneven
        }
        indexEven+=2;   //iterate even
    }

    return nums;
}

int main()
{
    cout << "921 >> " <<  minAddToMakeValid("))((");

    std::vector<int> data921{4,2,5,7};
    cout << "922 >> " << endl;
    routine::showVector(sortArrayByParityII(data921);


    return 0;
}
