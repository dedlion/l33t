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

//923. 3Sum With Multiplicity MEDIUM

//this is variants for 2 and 3
long long variantsCount(long long val, int copies)
{
    // val! / (val-copies)! * copies!
    if (copies==2)
        if (val>=2)
            return (val*(val-1)/2);
        else
            return 0;
    else
        if (val>=3)
            return (val*(val-1)*(val-2)/6);
        else
            return 0;
}

int threeSumMulti(vector<int>& arr, int target) {
    //here we abusing low count of input values.
    const int MAX_VAL = 101;
    const int MODULO = 1e9+7;
    std::vector<int> mp(MAX_VAL); //so we can premap vector
    //more general solution to use map... but we can use vector here.
    //code will be faster but more uglier

    for (auto i : arr) mp[i]++;

    long long result =0;
    for (int i=0;i<MAX_VAL;i++)
    {
        if (mp[i]!=0)   //skip zeroes in vefctor. can use addition vector/set to store usefull indexes. But input vector size is only 100
            for (int j=i;j<MAX_VAL;j++)
            {
                if (mp[j]!=0)   //skip zeroes
                    for (int k=j; k<MAX_VAL; k++)
                    {
                        if (mp[k]!=0)   //skip zeroes
                        {
                            if (i+k+j==target)  //if we can make result
                            {
                                if (k==i && j==i && k==j)
                                {
                                    //all three numbers the same - cal then val! / ((val-3)! * 3!)
                                    result += variantsCount(mp[i],3);
                                } else
                                {
                                    if (i==j)
                                    {
                                        //two numbers the same - cal then val! / ((val-2)! * 2!)
                                        result += variantsCount(mp[i],2) * mp[k];
                                    } else
                                    {
                                        if (j==k)
                                        {
                                            //two numbers the same - cal then val! / ((val-2)! * 2!)
                                            result += variantsCount(mp[j],2) * mp[i];
                                        } else
                                        {
                                            if (i==k)
                                            {
                                                //two numbers the same - cal then val! / ((val-2)! * 2!)
                                                result += variantsCount(mp[i],2) * mp[j];
                                            } else
                                            {
                                                //all numbera are different, just multiply them
                                                result += mp[j]*mp[i]*mp[k];
                                            }
                                        }
                                    }
                                }
                                result = result % MODULO; //applu MODULO
                            }
                        }
                    }
            }
    }
    return result;
}

//925



int main()
{
    cout << "921 >> " <<  minAddToMakeValid("))((") << endl;

    std::vector<int> data922{4,2,5,7};
    cout << "922 >> " << endl;
    routine::showVector(sortArrayByParityII(data922));

    std::vector<int> data924{1,1,2,2,3,3,4,4,5,5};
    cout << "924 >> " << threeSumMulti(data924, 8);

    return 0;
}
