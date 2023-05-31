#include <iostream>
#include "routine.h"
#include "unordered_map"

using namespace std;

class Solution {
public:
    //https://leetcode.com/problems/remove-duplicates-from-sorted-array
    //#26 EASY
    int removeDuplicates(vector<int>& nums) {
        int totalPoints = nums.size();
        if (totalPoints<2) return totalPoints;  //if size==0 || size==1 cant contain duplicates
        int readPointer =1;                     //first element is uniques 100% skip it
        int savePointer =1;                     //first element is uniques 100% skip it
        while (readPointer<totalPoints) {       //read all elements
            if (nums[readPointer]!=nums[readPointer-1]) //if unique
            {
                nums[savePointer] = nums[readPointer];  //save it
                savePointer++;
            }
            readPointer++;
        }
        return savePointer;
    }
    //https://leetcode.com/problems/remove-element/
    //#27 EASY
    int removeElement(vector<int>& nums, int val) {
        int totalPoints = nums.size();
        if (totalPoints==0) return totalPoints;
        int readPointer =0;
        int savePointer =0;
        while (readPointer<totalPoints) {       //read all elements
            if (nums[readPointer]!=val) //if unique
            {
                //if (savePointer!=readPointer)   //better in some circumstances
                    nums[savePointer] = nums[readPointer];  //save it
                savePointer++;
            }
            readPointer++;
        }
        return savePointer;
    }
    //https://leetcode.com/problems/divide-two-integers/
    //#29 MEDIUM
    const int MAX_POSS_DIVIS = 1<<30;    //1<<30-1 max number which can be *2 without overflow
    int divide(int dividend, int divisor) {
        if (dividend==0) return 0;  //empty solution
        int copyDivisor = divisor;
        //we want positive numbers bcs solution based on bit shifts
        int sign =1;
        if ((dividend>0 && divisor<0)||(dividend<0 && divisor>0)) sign=-1;
        if (divisor==dividend) return sign; //simple solution
        //we have saved result sign. now we can take abs
        if (divisor!=INT_MIN)
            divisor = abs(divisor);
        else
            return 0; //variant divisor==dividend==INT_MIN already checked. So abs(divisor)>abs(dividend)

        bool addBit = false;
        if (dividend!=INT_MIN)
            dividend = abs(dividend);
        else
        {
            //abs(INT_MIN) = INT_MAX + 1/*additional_bit*/
            if (divisor==1) return (sign>0)?INT_MAX:INT_MIN;
            dividend = INT_MAX;
            addBit=true; //we remember that we have
        }



        if (divisor>dividend) return 0; //simple solution

        if (divisor==1) return (sign>0)?dividend:-dividend; //simple solution

        //find pow(divisor,power2)>=dividend AND divisor safely can mult by 2 wihout overflow
        //IDEA is to find result in binary variant
        //divisor = dividend*(2^n)*V[n] + dividend*(2^(n-1))*V[n-1] //V can be 1 or 0
        int power2 = 0;
        while(divisor < dividend && divisor<MAX_POSS_DIVIS)
        {
            power2++;
            divisor = divisor << 1;
        }

        //no we can calc V[]
        int result = 0;
        while (power2>=0 && dividend!=0) //dividend!=0 can be omitted.
        {
            if (dividend >= divisor)
            {
                dividend-=divisor;
                result+= 1 << power2; //if (V[n]==1) => dividend*(2^n)*V[n] == dividend*(2^n). Simply add 2^n to result
            }
            divisor = divisor >> 1;
            power2--;
        }
        //dividend was MIN_INT
        if (addBit)
        {
            if (dividend+1>=copyDivisor) result++;
        }


        return (sign>0)?result:-result;
    }

    //https://leetcode.com/problems/substring-with-concatenation-of-all-words/
    //30# HARD
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> res;
        int totalWords = words.size();
        if (totalWords == 0 ) return res;

        int oneWordLen = words.at(0).size();
        int allWordsLen = totalWords * oneWordLen;

        int len = s.size();
        if (len<allWordsLen) return res;

        //we use map bcs words can contain duplicates. So we save "word" + "weight"
        //it contains all subparts of concatenation word
        map<string,int> wordMap;
        for (auto i:words)
            wordMap[i]++;

        //bcs i want some optimizing. im doing this algo oneWordLen-1 time.
        //so we skip some letters and assume that all words can be only in oneWordLen*N indexes
        for (int i=0; i<oneWordLen;i++)
        {
            int position = i;
            map<string,int> currMap;    //we store curr freq map (aka all subparts of concatenation word)
            int fifoLen = 0;
            while (position<len-oneWordLen+1)
            {
                string sub = s.substr(position,oneWordLen); //get substr
                auto find = wordMap.find(sub);
                if (find!=wordMap.end())        //if this can be patr of our Concatenation
                {
                    //here we doing some kinf of FIFO
                    //we should use this bcs of variant: string = "bbbbbb" words = {"b","b"};
                    //with FIFO we can it much faster
                    if (fifoLen==totalWords)
                    {
                        //add to currMap when len is == totalWords and remove prev word
                        currMap[sub]++;
                        string outStr = s.substr(position-fifoLen*oneWordLen,oneWordLen);
                        currMap[outStr]--;  //we can offord this. bcs keys are only == words in "words". So no add keys is generated
                    } else
                    {
                        //add to currMap while len is < totalWords
                        fifoLen++;  //fifoLen!=currMap.size() when same words occures
                        currMap[sub]++;
                    }
                    if (fifoLen==totalWords)    //not nessesary. just save a little bit CPU time
                    {
                        if (currMap==wordMap)   //compare two maps... this is main idead of algo. Check that curr word contains from the same subparts
                        {
                            //we save result
                            res.push_back(position-allWordsLen+oneWordLen);
                        }
                    }
                } else
                {
                    //we have no such word -> should clear all prev words
                    currMap.clear();
                    fifoLen=0;
                }
                position+=oneWordLen;
            }

        }

        return res;
    }
};


int main()
{
    //26 and 27 are very simple


    //29
    Solution sol;
    int dividend = -2147483648;
    int divisor = -3;

    cout<< "divide " <<sol.divide(dividend,divisor) << " vs " << dividend/divisor << endl;

    //30
    //vector<int> findSubstring(string s, vector<string>& words) {

    cout << "words  " ;
    vector<string> s{"ab","ba"};
    routine::showVector(sol.findSubstring("kabaab",s));

    return 0;
}
