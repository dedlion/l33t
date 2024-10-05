#include <iostream>
#include "routine.h"

using namespace std;

//PROBLEM 567. Permutation in String  MEDIUM
bool isPermutation(std::map<char,int> & letters)
{
    for (auto & i : letters)
    {
        if (i.second != 0) return false;
    }
    return true;
}
inline void changeWeight(std::map<char,int> &letters , char s, bool add)
{
    if (letters.count(s))
    {
        if (add)
            letters[s]++;
        else
            letters[s]--;
    }
    return;
}
bool checkInclusion(string s1, string s2) {
    int lenSmall  = s1.size();
    int lenBig  = s2.size();
    if (lenSmall>lenBig) return false;
    //we now whic letters MUST be in permutations. We use minus so we will "balance" this with letters from s2
    std::map<char,int> letters;
    for (auto i : s1)
    {
        letters[i]--;
    }

    //lets look at first s1.size() letters.
    for (int i=0; i<lenSmall; i++)
    {
        letters[s2[i]]++;
    }
    //if all letters weights == 0 this is result
    if (isPermutation(letters)) return true;

    //shift window to the right. add additional letter from the roght remove letter from the left
    for (int i=0; i<(lenBig-lenSmall); i++)
    {
        //we can add additional check here if new letter contains in "letters"

        changeWeight(letters,s2[i+lenSmall],true);
        //letters[s2[i+lenSmall]]++;  //MORE STRAIGHTFORWARD VARIANT... IMO FASTER

        changeWeight(letters,s2[i],false);
        //letters[s2[i]]--;  //MORE STRAIGHTFORWARD VARIANT... IMO FASTER
        if (isPermutation(letters)) return true;
    }


    return false;
}

int main()
{
    cout << "Hello World!" << checkInclusion("ab","zabzzzzzzzzzzazzzbzzzzz")<< endl;
    return 0;
}
