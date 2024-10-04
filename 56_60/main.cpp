#include <iostream>
#include "routine.h"

using namespace std;

//PROBLEM 56 MEDIUM
vector<vector<int>> merge(vector<vector<int>>& intervals) {
    vector<vector<int>> result;
    int len = intervals.size();
    //just sort vectors based on their starts
    std::sort(intervals.begin(), intervals.end(), [](vector<int> & a, vector<int> & b){ return a[0]<b[0];});

    int i =0;
    while (i <  len) //all intervals
    {
        int startInterval = intervals[i][0];
        int endInterval = intervals[i][1];
        i++;
        if (i<len)  //check vector end
        {
            while (intervals[i][0]<=endInterval) //while start of the next vector is inside curr vector
            {
                endInterval = max(endInterval,intervals[i][1]); //merge it with curr vector
                i++;
                if (i==len) break;  //check vector end
            }
        }
        result.push_back({startInterval, endInterval});  //add merged vector to result vector
    }
    return result;
}
//PROBLEM 57  EASY
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) {
    vector<vector<int>> result;
    intervals.push_back(newInterval);
    int len = intervals.size();
    //just sort vectors based on their starts
    std::sort(intervals.begin(), intervals.end(), [](vector<int> & a, vector<int> & b){ return a[0]<b[0];});

    int i =0;
    while (i <  len) //all intervals
    {
        int startInterval = intervals[i][0];
        int endInterval = intervals[i][1];
        i++;
        if (i<len)  //check vector end
        {
            while (intervals[i][0]<=endInterval) //while start of the next vector is inside curr vector
            {
                endInterval = max(endInterval,intervals[i][1]); //merge it with curr vector
                i++;
                if (i==len) break;  //check vector end
            }
        }
        result.push_back({startInterval, endInterval});  //add merged vector to result vector
    }
    return result;
}

//PROBLEM 58  EASY
const char SPACE = ' ';
int lengthOfLastWord(string s) {
    int len = s.size();
    if (len==0) return 0;
    //ofc we can use regexp here... but problem is easy

    //1. remove spaces from the end
    int i = len -1;
    while (i>=0)
    {
        if (s[i]!=SPACE) break;
        i--;
    }

    //find word len
    int wordStart = i;
    while (i>=0)
    {
        if (s[i]==SPACE) break;
        i--;
    }
    return wordStart-i;
}

//PROBLEM 59 SPIRAL MATRIX II
//internal function
int fillOuterFields(std::vector<std::vector<int>> & matrix, int row, int startVal)
{
    int n = matrix.size();
    //right up direction
    for (int i=row; i<n-row; i++)
        matrix[row][i]=startVal++;
    //down right
    for (int i=row+1; i<n-row; i++)
        matrix[i][n-row-1]=startVal++;
    //left down
    for (int i=n-row-2; i>=row; i--)
        matrix[n-row-1][i]=startVal++;
    //up left
    for (int i=n-row-2; i>row; i--)
        matrix[i][row]=startVal++;
    return startVal;
}
//main function
vector<vector<int>> generateMatrix(int n) {
    int row =0;
    int mid = (n%2==0)?n/2:(n/2+1);
    int startValue = 1;
    //make empty space
    vector<vector<int>> result;
    result.resize(n);
    for (int i=0; i<n; i++)
        result[i].resize(n);
    //fill it by continiously filled outer fields
    //can write wihtout func call... but this is more readable IMO
    while (row < mid)
    {
        startValue = fillOuterFields(result, row, startValue);
        row++;  //now we "pretend" that our matrix is smaller
    }
    return result;
}

int main()
{
    std::vector<std::vector<int>> input56 = {{4,5},{1,4},{7,8}};
    cout << "problem 56 " <<endl;
    routine::showVectors(merge(input56)) ;

    cout << "problem 58 " << lengthOfLastWord("  d   ")<<endl;


    cout << "problem 59 " <<endl;
    routine::showVectors(generateMatrix(7)) ;
    return 0;
}
