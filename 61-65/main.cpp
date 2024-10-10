#include <iostream>
#include "routine.h"

using namespace std;
//61. Rotate List MEDIUM
ListNode* rotateRight(ListNode* head, int k) {
       if (head==nullptr) return head;
       ListNode* saveHead = head;
       int len = 1;
       while (head->next!=nullptr)
       {
           head = head->next;
           len++;
       }
       if (len==1) return head;
       int shift = k % len;            //number of "left shifts"
       if (shift==0) return saveHead;  //no need to change anything
       int whereToBreak = len-1-shift; //number of right shifts

       head->next = saveHead; //make list infinite;
       for (int i=0; i<whereToBreak; i++)  //find where to break
       {
           saveHead = saveHead->next;
       }
       head = saveHead->next;  //save future start of list
       saveHead->next =  nullptr;  //break list here
       return head;

   }

//62 Unique Paths MEDIUM
int uniquePaths(int m, int n) {
    if (m==1 || n==1) return 1;
    if (m==2 || n==2) return max(n,m);
    int sum = m+n-2;            //total moves
    int bigBasis = max(m,n) - 1;       //number of one directional moves
    int smallBasis = sum - bigBasis;     //number of one directional moves (another)
    //so we mus calc
    //sum! / ((smallBasis!) * (sum-smallBasis!))

    //up = sum! / (sum-var)! => 9! / (9-7)! == 8!*9!
    double up = 1.0;
    for (int i=bigBasis+1; i<=sum; i++)
        up = up *i;

    //usual factorial
    double down = 1.0;
    for (int i=1; i<=smallBasis; i++)
        down = down *i;

    return round(up/down);
}

//63. Unique Paths II MEDIUM
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

    int lenY = obstacleGrid.size();
    int lenX = obstacleGrid[0].size();

    //nummber of variants is negative bcs obstacle is positive
    //easier to check results... can be changed to positive

    obstacleGrid[0][0] = -1; //fill start row
    //fill first row
    for (int i=1; i<lenX; i++)
    {
        if (obstacleGrid[0][i]==1)  //obstacle
            obstacleGrid[0][i]=0;   //zero ways to come here
        else
            obstacleGrid[0][i]=obstacleGrid[0][i-1];    //copy prev cell
    }
    //fill first column
    for (int i=1; i<lenY; i++)
    {
        if (obstacleGrid[i][0]==1) //obstacle
            obstacleGrid[i][0]=0;   //zero ways to come here
        else
            obstacleGrid[i][0]=obstacleGrid[i-1][0];    //copy prev cell
    }

    int maxLen = min(lenX,lenY);
    for (int i=1; i<maxLen; i++)
    {
        //fill row then column
        if (i<lenX)
        {
            //i - x, j - y
            for (int j=i; j<lenY; j++)
            {
                //idea like before. if obstacle - 0, not obstacle pathes = cell from left + cell from up
                if (obstacleGrid[j][i]==1)
                {
                    obstacleGrid[j][i]=0;
                } else
                {
                    obstacleGrid[j][i] = obstacleGrid[j-1][i] + obstacleGrid[j][i-1];
                }
            }
        }
        if (i<lenY)
        {
            //i - y, j - x
            //idea like before. if obstacle - 0, not obstacle pathes = cell from left + cell from up
            for (int j=i+1; j<lenX; j++)
            {
                if (obstacleGrid[i][j]==1)
                {
                    obstacleGrid[i][j]=0;
                } else
                {
                    obstacleGrid[i][j] = obstacleGrid[i-1][j] + obstacleGrid[i][j-1];
                }
            }
        }
    }
    return -obstacleGrid[lenY-1][lenX-1];
}


//64. Minimum Path Sum MEDIUM
int minPathSum(vector<vector<int>>& grid) {
    int y_len = grid.size();
    int x_len = grid.at(0).size();
    int totalSteps = x_len + y_len - 1;
    if (totalSteps == 1) return grid[0][0]; //dont want ot calc if size == [1;1]

    for (int y = 1; y < y_len; y++)         //summ first row (so we can skip "if" in math for border values)
        grid[y][0]+=grid[y-1][0];

    for (int x = 1; x < x_len; x++)         //summ first col (so we can skip "if" in math for border values)
        grid[0][x]+=grid[0][x-1];

    if (x_len==1 || y_len==1) return grid[y_len-1][x_len-1];    //if we have only one row or one column skip math

    for (int i=2; i<totalSteps; i++)    //i==2 bcs first we already calced
    {
        for (int y = 1; y < min(i,y_len); y++)  //calc diag values Y
        {
            int x = i - y;                                  //calc diag values X
            if (x>=x_len) continue;                         //border check
            grid[y][x] += min(grid[y][x-1],grid[y-1][x]);   //take prev value only from top or left
        }
    }
    return grid[y_len-1][x_len-1];
}

int main()
{
    std::vector<int> data61 {1,2,3,4,5,6,7};
    cout << "61 >> " << endl;
    routine::showList(rotateRight(routine::generateList(data61),5));

    cout << "62 >> " << uniquePaths(17,2) << endl;

    //std::vector<std::vector<int>> data63 {{0,0,0},{0,0,0},{0,1,0},{1,0,0},{0,0,0}};
    std::vector<std::vector<int>> data63 {{0,0,0,0,0},{0,0,0,0,1},{0,0,0,1,0},{0,0,1,0,0}};
    cout << "_63 >> " << uniquePathsWithObstacles(data63) << endl;

    std::vector<std::vector<int>> data64{{1,3,1},{1,5,1},{4,2,1}};
    cout << "64 >> "  << minPathSum(data64) << endl;
    return 0;
}
