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

void getSubsetNum(vector<int> const &vec, int const &max, vector<vector<int> > &t, int &pos, int const &length)
{
    for(int i = pos; i < vec.size(); i++)
    {
        
        vector<int> temp;
        int current = vec[i];
        int product = current;
        int prevProduct = 1;
        if(current < max)
        {
            temp.push_back(current);
            t.push_back(temp);
        }

        for(int k = i + 1; k < vec.size(); k++)
        {
            
            if(product * vec[k] < max)
            {
                prevProduct = product;
                product = product * vec[k];
                temp.push_back(vec[k]);
            }
        }
        
        if(temp.size() > 1) {
            t.push_back(temp);
        }
    }
    
    pos++;

    if(pos == vec.size())
    {
        return;
    }
    else {
        getSubsetNum(vec, max, t, pos, length);
    }
    
}

int main(int argc, const char * argv[]) {
    
    vector<int> A{1,2,3,4};
    vector<vector<int> > subsets;
    int pos = 0;
    int length = A.size();
    int M = 10;
    
    getSubsetNum(A, M, subsets, pos, length);
    
    for(int i = 0; i < subsets.size(); i++)
    {
        for(int k = 0; k < subsets[i].size(); k++)
        {
            cout << subsets[i][k] << ", ";
        }
        
        cout << endl;
    }
    
    printf("Number of subsets less than %d: %d\n", M, subsets.size());
    
    if ( argc < 2 ) {
      printf("Specify an array size\n");
      return 1;
    }
    else if ( argc < 3 ) {
        printf("Specify product limit (m)\n");
    }
    
    srand(time(NULL));

    int n = atoi(argv[1]);
    int m = atoi(argv[2]);
    printf("Size: %d\n", n);
    printf("Max m: %d\n", m);
    
    return 0;
}
