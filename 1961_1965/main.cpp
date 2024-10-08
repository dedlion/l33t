#include <iostream>

using namespace std;

//1963. Minimum Number of Swaps to Make the String Balanced MEDIUM Daily
int minSwaps(string s) {
    const char LEFT_BRACKET = '[';
    //idea here is just to find unbalanced bracket
    int balancer =0;
    int errors =0;
    for (int i=0; i<s.size(); i++)
    {
        if (s[i]==LEFT_BRACKET)
        {
            balancer++;
        } else
        {
            if (balancer>0)
            {
                balancer--; //balanced -> ok
            } else
            {
                errors++;   //!balanced -> error
            }
        }
    }
    int result = errors/2 + (errors%2); //we can fix two problems with 1 swap
    return result;

}


int main()
{

    return 0;
}
