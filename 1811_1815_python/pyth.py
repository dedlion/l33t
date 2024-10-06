from typing import List
import math
#1811 PREMIUM 

#1812 EASY Determine Color of a Chessboard Square
def squareIsWhite(self, coordinates: str) -> bool:
    column : int = ord(coordinates[0]) - ord('a')  ; #c++ style to get number of the column from char
    row : int = int(coordinates[1]);
    return ((column+row) % 2 == 0); #black dields diagonal

#1813 MEDIUM Sentence Similarity III
def areSentencesSimilar(sentence1: str, sentence2: str) -> bool:
    #sentence1 > sentence2.
    if (len(sentence2) > len(sentence1)):
        sentence1, sentence2 = sentence2 ,sentence1; #swap

    #small optimization wthich gives decent speed up
    if (sentence1 == sentence2):    #totally equal 
        return True;
    if (sentence1.startswith(sentence2 + " ") or sentence1.endswith(" "+sentence2 )): #starts or ends
        return True;
    #we want all words
    baseWords = sentence2.split(" ");
    extendedSent = sentence1.split(" ");
    
    length :int = len(baseWords);
    lengthBig :int = len(extendedSent);
    counter :int = 0;
    #words compare from the beginning
    while counter < length:
        if baseWords[counter]==extendedSent[counter]:
            counter=counter+1
        else:
            break;
    #words compare from the end
    usedwords :int = counter;
    counter = 0;
    while counter < length:
        if baseWords[length-counter-1]==extendedSent[lengthBig-counter-1]:
            counter=counter+1
        else:
            break;

    usedwords = usedwords+counter;  #total equal words
    return usedwords >= length;     #may be overlapping so we use >= instead of ==

#1814 Count Nice Pairs in an Array
def countNicePairs(nums: List[int]) -> int:
    MODULO = 1e9+7; #const
    def reverso(val:int) -> int:
        return int(str(val)[::-1]);
    
    def variants(val:int) -> int: #in russian this is sochetanie. n! / (n-2)! * 2!
        return (val*(val-1)/2) % MODULO;

    d = dict();
    #create map of usable numbers.
    #a + revers(b) == revers(a) + b ONLY if a-reverse(a) == b-reverse(b)
    #so we save only diff = a-reverse(a) 
    for i in nums:
        diff = i - reverso(i);
        if diff in d:
            d[diff] = d[diff]+1;
        else:
            d[diff] = 1;
    result:int =0;
    #sum all possibilities
    for key in d:
        val = d[key];
        result = (result + variants(val)) % MODULO;
    
    return int(result);


#1815 Maximum Number of Groups Getting Fresh Donuts           HARD- NOT WORKING =\
def maxHappyGroups( batchSize: int, groups: List[int]) -> int:
    #this is recursion
    #idea was that if group is minimal - solution is optimal... but i was wrong
    def recurison(groups: List[int], used: List[int], depth: int, batch: int) -> List[int]:
        if depth>0: #recurison depth
            for i in range(len(groups)):
                val = groups[i];
                #deep copy for recursion
                l_used = used.copy();
                l_used.append(val);
                l_groups = groups.copy();
                l_groups.remove(val);
                gr = recurison(l_groups,l_used,depth-1, batch);
                if (len(gr)>0): #return to main call
                    return gr;
            return [];
        else:
            sum=0;
            for i in used:
                sum = sum + i;
            if (sum % batch == 0):
                return used; #internal call from deepest recursion. group is minimal.
            else:
                return []; #not optimal

    
    basicLen = len(groups);
    for i in range(len(groups)):
        groups[i] = groups[i]%batchSize; #we want only reminders.
    
    groups.sort();
    
    happy:int =0;
    depth: int = 1;
    while depth <= len(groups):
        #we get subgroups with winimal len (WRONG)
        subArr = recurison(groups,[],depth,batchSize);
        if (len(subArr) > 0):
            #remove used indexes
            print(happy+1,"removed" , subArr);
            for k in subArr:
                groups.remove(k);
            happy=happy+1;
        else:
            depth=depth+1;
    #add 1 happy group if anything left
    if (len(groups)>0):
        happy=happy+1;
    
    return happy;

###################################################################
res : bool = areSentencesSimilar("CwFfRo regR", "CwFfRo H regR");
print("result" , res);

res2 = countNicePairs([13,10,35,24,76]);
print("result2" , res2);

input = [1,1,1,1,1,1,1,1,1,6,6,6,7];
res3 = maxHappyGroups(9, input);
print("result3" , res3);
