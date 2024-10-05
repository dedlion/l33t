#include <iostream>
#include "routine.h"

using namespace std;
//PROBLEM 566. Reshape the Matrix EASY
vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
    //width(x) - c
    //height(y) - r
    int y = mat.size();
    int x = mat[0].size();

    if (r*c!=x*y) return mat; //conversion not possible

    vector<vector<int>> result;
    result.resize(r);
    for (int i=0; i<r; i++)
        result[i].resize(c);

    for (int i=0; i<y; i++) //y
        for (int j=0; j<x; j++) //x
        {
            int point = i*x + j;
            int new_x = point % c;
            int new_y = (point-new_x)/c;
            result[new_y][new_x] = mat[i][j];
        }
    return result;
}

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
    cout << "Problem 567!" << checkInclusion("ab","zabzzzzzzzzzzazzzbzzzzz")<< endl;

    std::vector<std::vector<int>> matrix ({{1,2,3,4,5,6},{3,4,5,6,7,8}});
    cout << "Problem 566!" << endl;
    routine::showVectors(matrixReshape(matrix,3,4));
    return 0;
}
