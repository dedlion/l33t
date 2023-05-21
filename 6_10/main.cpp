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
};

int main()
{
    Solution sol;
    //Problem #6 SKIPPED

    //Problem #7
    cout << sol.reverse(102) << endl;

    return 0;
}

