#include <iostream>
#include "routine.h"
using namespace std;
//921. Minimum Add to Make Parentheses Valid MEDIUM DAILY
int minAddToMakeValid(string s) {
    const char LEFT_BRACKET = '(';
    const char RIGHT_BRACKET = ')';
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


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
