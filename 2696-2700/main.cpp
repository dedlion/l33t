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

//2697. Lexicographically Smallest Palindrome EASY
string makeSmallestPalindrome(string s) {
    int len = s.size();
    for (int i=0; i<len/2; i++)
    {
        if (s[i] != s[len-i-1])
        {
            if (s[i] < s[len-i-1])
            {
                s[len-i-1] = s[i];
            } else
            {
                s[i] = s[len-i-1];
            }
        }
    }
    return s;
}

////////
//2698. Find the Punishment Number of an Integer MEDIUM

//just faster version of stoi for out proble
int fromString(string num)
{
    int result = 0;
    int base = 1;
    int len = num.size();
    for (int i=0; i<len; i++)
    {
        int val = num[len-i-1] - '0';   //C style. Get value
        result += val * base;           //then mult value on 10^n... 123 = 1*10^2+2*10^1+3*10^0
        base = base*10;                 //change basis
    }
    return result;
}

//check our number i (targetSum) == sum of substrings of i*i (currSum)
//we use recursion to check all possible variants
bool isSpecialNumber(int targetSum, string sub, int currSum)
{
    if (currSum>targetSum) return false;    //no point to proceed. currSum can only increase
    int len = sub.size();
    if (len!=0) //can we recursion deeper?
    {
        for (int i=1; i<=len; i++)
        {
            int add = fromString(sub.substr(0,i));      //get first i chars
            string cuttedCopy = sub.substr(i,len-i);    //get all what left
            bool ok = isSpecialNumber(targetSum, cuttedCopy, currSum+add );   //call self (recursion)
            if (ok) return ok;
        }
    } else
    {
        //there is no letters. lets check result
        if (targetSum==currSum) return true;
    }
    return false;
}


int punishmentNumber(int n) {
    int result =0;
    //just check all possible values
    for (int i=9; i<=n; i++)
    {
        int square = i*i;
        if (isSpecialNumber(i,to_string(square),0))
            result += square;
    }


    return result;
}


int main()
{
    cout << "Problem 2696 -- " << minLength("CABCDD") <<endl;

    cout << "Problem 2697 -- " << makeSmallestPalindrome("asdasdafg") <<endl;

    cout << "Problem 2698" << punishmentNumber(37) <<endl;
    return 0;
}
