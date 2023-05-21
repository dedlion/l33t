#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T>
void showVector(const vector<T> vec)
{
    for (auto i : vec) cout << i << "  ";
    cout<< endl;
}


class Solution {
public:
    //https://leetcode.com/problems/reverse-integer/
    //Problem #7 MEDIUM
    //that was funny... they though i will calc decimal digits. So naive... This solution is FASTEST.
    int reverse(int x) {
        string str = std::to_string(x);
        bool start0 = true; //flag to skip 0 in the end
        bool negative = false;
        string newVal = "";
        for (std::string::reverse_iterator rit=str.rbegin(); rit!=str.rend(); ++rit)    //reverse iterator
        {
            if ((*rit)=='0' && start0)
            {
                continue;   //skip 0
            }
            start0 = false; //skip zeroes
            char c = *rit;
            if (c=='-') //skip "-"
                negative= true;
            else
                newVal += c;

        }
        try
        {
            int val = stoi(newVal);
            return (negative)?-val:val;
        }
        catch(...)
        {
            return 0; //just in case
        }

    }

    //https://leetcode.com/problems/palindrome-number/
    //Problem #9 EASY
    bool isPalindrome(int x) {
        string str = to_string(x);
        bool even = str.size()%2==1;
        int mid = str.size()/2;    //can swap for floor(str.size()/2.0)
        for (int i=0; i<mid;i++)
        {
            if (str.at(i)!=str.at(str.size()-i-1)) return false;
        }
        return true;
    }
};

int main()
{
    Solution sol;
    //Problem #6 SKIPPED

    //Problem #7
    cout << sol.reverse(102) << endl;

    //Problem #8 atoi.... cmon this NOT FUN

    //Problem #9
    cout << " pal " << sol.isPalindrome(12321) << endl;

    return 0;
}

