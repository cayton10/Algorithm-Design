/*
 * Algorithm Design Chapter 2 Problem 6
 * Adjusted for 0-based vectors instead of 1-based
 * Carl Mummert, Jan 2021
 * Edited by Benjamin Cayton 1.27.2021
 * Objective to reduce complexity from n^3 to n^2
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char * argv[] ) {

  if ( argc < 2 ) {
    printf("Specify an array size\n");
    return 1;
  }

  srand(time(NULL)); // good enough for a demo

  int n = atoi(argv[1]);
  printf("Size: %d\n", n);

  //Vector holds our random numbers
  vector<int> A(n);
  for ( int i = 0; i < n; i++ ) {
    A[i] = rand() % 10;
  }

  //Print random numbers
  printf("A: ");
  for ( int i = 0; i < n; i++ )
    printf("%d ", A[i]);
  printf("\n");

  //Create vector to display the summing process from original vector
  vector<vector<int> >  B(n);
  for ( int i = 0; i < n; i++ ) {
    B[i].resize(n);
  }

  //Reduce complexity here
  for ( int i = 0; i < n; i++ ) {
      //Start the running total var
      int runningTotal = A[i];
      
    for ( int j = i+1; j < n; j++ ) {
        //Add to the running total var
        runningTotal += A[j];
        
        B[i][j] = 0; // making double sure it's initialized correctly
        B[i][j] = runningTotal;
    }
      
  }

  for ( int i = 0; i < n; i++ ) {
    for ( int j = 0; j < n; j++ ) {
      printf("%8d ", B[i][j]);
    }
    printf("\n");
  }

}
