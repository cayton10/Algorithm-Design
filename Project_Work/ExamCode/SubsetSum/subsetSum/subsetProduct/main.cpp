//
//  main.cpp
//  subsetProduct
//  Program counts the number of subsets of array with sums less than 'm'
//  Created by Benjamin Paul Cayton on 3/20/21.
//  Assisted by Dr. Mummert, Marshall University CIT Chair

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
    
    //Vector A elements(1-J)
    
    for(int target = 2; target <= M; target++)
    {
        cache[0][target] = 1;
    }
    
    for(int nextElem = 1; nextElem <= A.size(); nextElem++)
    {
        
        for(int target = 1; target <= M; target++)
        {
            //Load cache[numElem][target]
            
            /*Sum of two things: subseq that do not use next elem & already have prod < target Ex: [1,2,3]
             ALSO: seq that DO use next elem Ex: [1,2,4], prod of previous is < target / nextElemnt */
            int first = cache[nextElem - 1][target];
            int second = cache[nextElem - 1][target / A[nextElem - 1]];
            
            //Round up if there's a remainder from above operation
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
    
    if(argc < 2) {
        printf("Enter number of elements in set:\n");
        return 1;
    }
    
    if(argc < 3) {
        printf("Enter the product limit for each subset: \n");
        return 1;
    }
    
    int numInSet = atoi(argv[1]);
    int M = atoi(argv[2]);
    
    printf("Enter number of elements in set: %d\n", numInSet);
    printf("Maximum product value for subset: %d\n", M);
    
    //Vector holds our random numbers
    vector<int> A(numInSet);
    
    int k = 0;
    //Load sequential vector
    for (int i = 1; i <= numInSet; i++) {
        A[k] = i;
        k++;
    }
    
    //Print random numbers
    printf("A: ");
    for ( int i = 0; i < numInSet; i++ )
      printf("%d ", A[i]);
    printf("\n");
    
    
    int numSubs = CountSubSets(A, M);
    printf("Number of subsets not exceeding product of %d: %d\n", M, numSubs);
    return 0;
}
