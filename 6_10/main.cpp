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
        int mid = str.size()/2;    //can swap for floor(str.size()/2.0)
        for (int i=0; i<mid;i++)
        {
            if (str.at(i)!=str.at(str.size()-i-1)) return false;    //compare letters. return if not
        }
        return true;
    }

    //https://leetcode.com/problems/regular-expression-matching/
    //Problem #10 HARD
    const char EMPTY_WILD = '\0';
    struct partExpr{
        string pattern;
        char wild;

        int any;
    };

    bool l_match(string input , partExpr * expr, int count)
    {
        partExpr currExpr;
        if (count==0)   //no more commands
        {
            if (input.size()==0) //no more data
                return true;
            else
                return false;
        }
        else
        {
            currExpr = *expr;   //make local copy of command
            count--;            //counter of commands
            if (count>0)
                expr++;
        }


        if (currExpr.any!=0)    //!.
        {
            if (currExpr.any==-1)   //wild .
            {
                currExpr.any=0;
                while(currExpr.any <= input.size())
                {
                    string copyInput = input;   //make cpy bcs arese modified base string. Can erase 1 letter without copy
                    bool ok = l_match(copyInput.erase(0,currExpr.any),expr,count);
                    if (ok) return ok;
                    currExpr.any++; //wild . + . + . and so on
                }
                return false;
            } else
            {
                if (currExpr.any > input.size()) return false;  //check that ... less then letters
                return l_match(input.erase(0,currExpr.any),expr,count); //remove letters and recursive call
            }
        } else
        {
            if (currExpr.wild==EMPTY_WILD)  //is any wild letters
            {
                size_t found = input.find(currExpr.pattern);
                if (found!=0)   //starts with pattern
                    return false;
                else
                    return l_match(input.erase(0,currExpr.pattern.size()),expr,count);  //remove letters and recursive call
            } else
            {
                //wild letters currExpr.pattern + currExpr.wild + currExpr.wild and so on
                size_t found =0;
                while (found!=string::npos)
                {
                    found = input.find(currExpr.pattern);
                    if (found!=0) //start with pattern
                        return false;
                    else
                    {
                        string copyInput = input;
                        bool ok = l_match(copyInput.erase(0,currExpr.pattern.size()),expr,count);
                        if (ok) return true;
                    }
                    currExpr.pattern+=currExpr.wild;
                }
                return false;
            }
        }
    }

    bool isMatch(string s, string p) {
        vector<partExpr> patterns;
        partExpr basic_expr = {"",EMPTY_WILD,0};    //basic empty pattern
        partExpr expr = basic_expr;
        //Im so hate strings in c++. Qt will do it in couple of strings
        //doing here command stack
        for (auto i : p)
        {
            switch (i) {
            case '.':
                if (expr.pattern!="")   //prev character was !.
                {
                    patterns.push_back(expr);
                    expr = basic_expr;
                }
                expr.any++; //optimizing ...
                break;
            case '*':
                if (expr.pattern!="")
                {
                    expr.wild = expr.pattern.back();
                    expr.pattern.pop_back();
                } else
                {
                    expr.any=-1;
                }
                patterns.push_back(expr);
                expr = basic_expr;
                break;
            default:    //any other character
                if (expr.any!=0) //prev character was .
                {
                    patterns.push_back(expr);
                    expr = basic_expr;
                }
                expr.pattern+=i;
                break;
            }
        }
        if (expr.any>0 || expr.pattern !="")
            patterns.push_back(expr);   //add last command
        return l_match(s,patterns.data(),patterns.size());  //this is recursive checker
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

    //Problem #10
    cout << "isMatch" << sol.isMatch("a",".*..a*") << endl;

    return 0;
}

