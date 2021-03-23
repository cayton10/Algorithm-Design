//
//  main.cpp
//  subsetProduct
//  Program counts the number of subsets of array with sums less than 'm'
//  Created by Benjamin Paul Cayton on 3/20/21.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;


int CountSubSets(vector<int> const &A, int const &M)
{
    //Num elements from array / vector 1st-D
    //Product of elements 2nd-D
    
    vector<vector<int> > cache;
    
    cache.resize(A.size() + 1);
    
    for(int i = 0; i <= A.size(); i++)
    {
        cache[i].resize(M + 1);
    }
    
    //Elements(1-J)
    
    for(int target = 2; target <= M; target++)
    {
        cache[0][target] = 1;
    }
    
    for(int nextElem = 1; nextElem <= A.size(); nextElem++)
    {
        
        for(int target = 1; target <= M; target++)
        {
            //Load cache[numElem][target]
            
            /*Sum of two things: subseq that don't use next elem & already have prod < target
             ALSO: seq that DO use next elem, prod of previous is < target / nextElemnt */
            int first = cache[nextElem - 1][target];
            int second = cache[nextElem - 1][target / A[nextElem - 1]];
            if(target % A[nextElem - 1] != 0)
            {
                second = cache[nextElem - 1][1 + target / A[nextElem - 1]];
            }
            cache[nextElem][target] = first + second;
            
        }
    }
    
    /*for(int i = 0; i <= A.size(); i++)
    {
        for(int k = 0; k <= M; k++)
        {
            printf("%2d ", cache[i][k]);
        }
        
        cout << endl;
    }*/
    
    
    return cache[A.size()][M] - 1; //Minus one for empty sequence
}

int main(int argc, const char * argv[]) {
    
    //int N = 40;
    
    vector<int> A = {1,2,3,4};
    vector<vector<int> > subsets;
    int M = 10;
    
    
    for(int i = 0; i < subsets.size(); i++)
    {
        for(int k = 0; k < subsets[i].size(); k++)
        {
            cout << subsets[i][k] << ", ";
        }
        
        cout << endl;
    }
    
    int numSubs = CountSubSets(A, M);
    cout << "Num of subsets " << numSubs << endl;
    
    return 0;
}
