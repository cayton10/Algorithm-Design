// Basic Sudoku Solver with backtracking
// Carl Mummert and Ben Cayton
// April 2021

// A Sudoku puzzle is stored as a 9x9 grid. The entries
// are 0 if the entry is blank, or an integer from 1 to 9
// if the entry is filled in.

#include <iostream>
#include <fstream>
#include <vector>


using namespace std;

// Print out the 9x9 Sudoku grid
void print_grid(const std::vector<std::vector<int> > & grid) { 
  for ( int row = 0; row < 9; row++ ) {
    for ( int col = 0; col < 9; col++ ) {
      if ( grid[row][col] == 0 ) {
	std::cout << '_';
      } else {
	  std::cout << (char) ('0' + grid[row][col]);
      }
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// Use max row and column values to constrain the subsquare search
// space
bool search_subsquare(const std::vector<std::vector<int> > grid,
          int maxRow, int maxCol, int val)  {

    for(int initR = maxRow - 2; initR <= maxRow; initR++) {
      for(int initC = maxCol - 2; initC <= maxCol; initC++) {
        if(grid[initR][initC] == val) {
          return false;
        }
      }
    }

    return true;
}

//Pass in the current row or column to return the maximum we need to inspect
//for the subsquare
int find_max(const int& num) {
    int max = 0;

    if(num < 3) {
      return max = 2;
    } else if (num >= 3 && num < 6) {
      return max = 5;
    } else {
      return max = 8;
    }
}


// Would it be legal, as far as we can see, to put
// value 'val' at location (row,col) of 'grid'?
bool is_legal (const std::vector<std::vector<int> > grid,
	       int row, int col, int val) {

  int maxR = 0;
  int maxC = 0;
  
  // Does 'val' already occur in a different location in the same row?
  for ( int tcol = 0; tcol < 9; tcol++ ) {
    if ( (tcol != col) && ( grid[row][tcol] == val )) {
      return false;
    }
  }

  // Does 'val' already occur in a different location in the same column?
  // If so, return false
  for(int trow = 0; trow < 9; trow++) {
    if((trow != row) && (grid[trow][col] == val)) {
      return false;
    }
  }

  // Does 'val' already occur in a different section in the same 3x3 subsquare?
  // If so, return false

  // TO DO
  
  //Find the maximum col && row we're going to look at for subsquare
  //In essence constrains the grid quadrant we want
  maxR = find_max(row);
  maxC = find_max(col);

  //If the value isn't in the subsquare return true
  if(search_subsquare(grid, maxR, maxC, val)) {
    return true;
  }
  else
    return false;

}

// Recursively try to fill in a Sudoku grid using backtracking
// Add 1 to 'count' each time the function is called
bool fill_in( std::vector<std::vector<int> > & grid, std::vector<std::vector<int> > & cache, int depth, int & count) {

  count++;
  
  if ( depth == 81 )
    return 1;  // completely filled in

  int row = depth / 9;
  int col = depth % 9;
  
  // case 1: grid[row][col] is a blank
  if ( grid[row][col] == 0 ) {

//TODO:This is where we start memoizing stop trying all possibilities and just try what ISN'T there*/

    // try all possibilities
    for ( int val = 1; val <= 9; val++ ) {
      if ( is_legal (grid, row, col, val) ) { 
	      grid[row][col] = val; // fill it in temporarily

        // if there is a complete solution using the value we filled
        // in temporarily, pass that information back to whoever called us

        if ( fill_in(grid, cache, depth+1, count) ) { 
          return true;
        }
      }
    }

    // If we get here, we could not find any solution from where we are.
    // Clean up and then report false to whoever called us.
    // Maybe they will then try another value in some other square
    // This is the backtracking part of the algorithm
    
    grid[row][col] = 0 ; // reset it to a blank
    return false;   
  }

  // In this case, there is a value from 1 to 9 in the current
  // location. In that case, just move on to the next entry
  return fill_in(grid, cache, depth+1, count);
}



// Load a 9x9 Sudoku grid from a file
std::vector<std::vector<int> > get_grid_from_file(const char * filename) {

  std::fstream fin(filename);
  
  // init 9x9 grid
  std::vector<std::vector<int> > grid;
  grid.resize(9);
  for( int i = 0; i < 9; i++ ) {
    grid[i].resize(9);
  }
  
  // input elements
  char c;
  fin.get(c);
  int position = 0;
  while ( (position < 81) && ( ! fin.eof() )) {
    if ( c == '\n') {
      fin.get(c);
    }
    int row = position / 9;
    int col = position % 9;
    
    if ( c == '_') {
      grid[row][col] = 0;
    } else {   
      grid[row][col] = (int) (c - '0');
    }
    
    position++;
    fin.get(c);
  }
  
  fin.close();

  return grid;
}

int main(int argc, char * argv[]) {

  if ( argc < 1 ) {
    std::cout << "Give a filename" << std::endl;
    return 1;
  }

//Initial grid
  std::vector<std::vector<int> > grid = get_grid_from_file(argv[1]);  
  //Cache 
  std::vector<std::vector<int> > cache = grid;
  
  std::cout << "Initial grid: " << std::endl;
  print_grid(grid);
  std::cout << "Memoized grid: " << std::endl;
  print_grid(cache);

  int recur_count = 0;
  bool found_solution = fill_in(grid, cache, 0, recur_count);

  if ( found_solution ) {
    std::cout << "Solution: " << std::endl;
    print_grid(grid);
  } else  {
    std::cout << "No solution"<< std::endl;
  }

  std::cout << "Recursion count: " << recur_count << std::endl;     
}
