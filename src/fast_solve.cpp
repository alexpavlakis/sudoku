#include <Rcpp.h>
#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <array>

using namespace std;
using namespace Rcpp;

// This is a fast and simple pure backtracking solver -- no use of hidden singles, naked singles, etc.

// Array of peers for each element
int arr[81][20] = { {1,2,3,4,5,6,7,8,9,10,11,18,19,20,27,36,45,54,63,72},
                    {0,2,3,4,5,6,7,8,9,10,11,18,19,20,28,37,46,55,64,73},
                    {0,1,3,4,5,6,7,8,9,10,11,18,19,20,29,38,47,56,65,74},
                    {0,1,2,4,5,6,7,8,12,13,14,21,22,23,30,39,48,57,66,75},
                    {0,1,2,3,5,6,7,8,12,13,14,21,22,23,31,40,49,58,67,76},
                    {0,1,2,3,4,6,7,8,12,13,14,21,22,23,32,41,50,59,68,77},
                    {0,1,2,3,4,5,7,8,15,16,17,24,25,26,33,42,51,60,69,78},
                    {0,1,2,3,4,5,6,8,15,16,17,24,25,26,34,43,52,61,70,79},
                    {0,1,2,3,4,5,6,7,15,16,17,24,25,26,35,44,53,62,71,80},
                    {0,1,2,10,11,12,13,14,15,16,17,18,19,20,27,36,45,54,63,72},
                    {0,1,2,9,11,12,13,14,15,16,17,18,19,20,28,37,46,55,64,73},
                    {0,1,2,9,10,12,13,14,15,16,17,18,19,20,29,38,47,56,65,74},
                    {3,4,5,9,10,11,13,14,15,16,17,21,22,23,30,39,48,57,66,75},
                    {3,4,5,9,10,11,12,14,15,16,17,21,22,23,31,40,49,58,67,76},
                    {3,4,5,9,10,11,12,13,15,16,17,21,22,23,32,41,50,59,68,77},
                    {6,7,8,9,10,11,12,13,14,16,17,24,25,26,33,42,51,60,69,78},
                    {6,7,8,9,10,11,12,13,14,15,17,24,25,26,34,43,52,61,70,79},
                    {6,7,8,9,10,11,12,13,14,15,16,24,25,26,35,44,53,62,71,80},
                    {0,1,2,9,10,11,19,20,21,22,23,24,25,26,27,36,45,54,63,72},
                    {0,1,2,9,10,11,18,20,21,22,23,24,25,26,28,37,46,55,64,73},
                    {0,1,2,9,10,11,18,19,21,22,23,24,25,26,29,38,47,56,65,74},
                    {3,4,5,12,13,14,18,19,20,22,23,24,25,26,30,39,48,57,66,75},
                    {3,4,5,12,13,14,18,19,20,21,23,24,25,26,31,40,49,58,67,76},
                    {3,4,5,12,13,14,18,19,20,21,22,24,25,26,32,41,50,59,68,77},
                    {6,7,8,15,16,17,18,19,20,21,22,23,25,26,33,42,51,60,69,78},
                    {6,7,8,15,16,17,18,19,20,21,22,23,24,26,34,43,52,61,70,79},
                    {6,7,8,15,16,17,18,19,20,21,22,23,24,25,35,44,53,62,71,80},
                    {0,9,18,28,29,30,31,32,33,34,35,36,37,38,45,46,47,54,63,72},
                    {1,10,19,27,29,30,31,32,33,34,35,36,37,38,45,46,47,55,64,73},
                    {2,11,20,27,28,30,31,32,33,34,35,36,37,38,45,46,47,56,65,74},
                    {3,12,21,27,28,29,31,32,33,34,35,39,40,41,48,49,50,57,66,75},
                    {4,13,22,27,28,29,30,32,33,34,35,39,40,41,48,49,50,58,67,76},
                    {5,14,23,27,28,29,30,31,33,34,35,39,40,41,48,49,50,59,68,77},
                    {6,15,24,27,28,29,30,31,32,34,35,42,43,44,51,52,53,60,69,78},
                    {7,16,25,27,28,29,30,31,32,33,35,42,43,44,51,52,53,61,70,79},
                    {8,17,26,27,28,29,30,31,32,33,34,42,43,44,51,52,53,62,71,80},
                    {0,9,18,27,28,29,37,38,39,40,41,42,43,44,45,46,47,54,63,72},
                    {1,10,19,27,28,29,36,38,39,40,41,42,43,44,45,46,47,55,64,73},
                    {2,11,20,27,28,29,36,37,39,40,41,42,43,44,45,46,47,56,65,74},
                    {3,12,21,30,31,32,36,37,38,40,41,42,43,44,48,49,50,57,66,75},
                    {4,13,22,30,31,32,36,37,38,39,41,42,43,44,48,49,50,58,67,76},
                    {5,14,23,30,31,32,36,37,38,39,40,42,43,44,48,49,50,59,68,77},
                    {6,15,24,33,34,35,36,37,38,39,40,41,43,44,51,52,53,60,69,78},
                    {7,16,25,33,34,35,36,37,38,39,40,41,42,44,51,52,53,61,70,79},
                    {8,17,26,33,34,35,36,37,38,39,40,41,42,43,51,52,53,62,71,80},
                    {0,9,18,27,28,29,36,37,38,46,47,48,49,50,51,52,53,54,63,72},
                    {1,10,19,27,28,29,36,37,38,45,47,48,49,50,51,52,53,55,64,73},
                    {2,11,20,27,28,29,36,37,38,45,46,48,49,50,51,52,53,56,65,74},
                    {3,12,21,30,31,32,39,40,41,45,46,47,49,50,51,52,53,57,66,75},
                    {4,13,22,30,31,32,39,40,41,45,46,47,48,50,51,52,53,58,67,76},
                    {5,14,23,30,31,32,39,40,41,45,46,47,48,49,51,52,53,59,68,77},
                    {6,15,24,33,34,35,42,43,44,45,46,47,48,49,50,52,53,60,69,78},
                    {7,16,25,33,34,35,42,43,44,45,46,47,48,49,50,51,53,61,70,79},
                    {8,17,26,33,34,35,42,43,44,45,46,47,48,49,50,51,52,62,71,80},
                    {0,9,18,27,36,45,55,56,57,58,59,60,61,62,63,64,65,72,73,74},
                    {1,10,19,28,37,46,54,56,57,58,59,60,61,62,63,64,65,72,73,74},
                    {2,11,20,29,38,47,54,55,57,58,59,60,61,62,63,64,65,72,73,74},
                    {3,12,21,30,39,48,54,55,56,58,59,60,61,62,66,67,68,75,76,77},
                    {4,13,22,31,40,49,54,55,56,57,59,60,61,62,66,67,68,75,76,77},
                    {5,14,23,32,41,50,54,55,56,57,58,60,61,62,66,67,68,75,76,77},
                    {6,15,24,33,42,51,54,55,56,57,58,59,61,62,69,70,71,78,79,80},
                    {7,16,25,34,43,52,54,55,56,57,58,59,60,62,69,70,71,78,79,80},
                    {8,17,26,35,44,53,54,55,56,57,58,59,60,61,69,70,71,78,79,80},
                    {0,9,18,27,36,45,54,55,56,64,65,66,67,68,69,70,71,72,73,74},
                    {1,10,19,28,37,46,54,55,56,63,65,66,67,68,69,70,71,72,73,74},
                    {2,11,20,29,38,47,54,55,56,63,64,66,67,68,69,70,71,72,73,74},
                    {3,12,21,30,39,48,57,58,59,63,64,65,67,68,69,70,71,75,76,77},
                    {4,13,22,31,40,49,57,58,59,63,64,65,66,68,69,70,71,75,76,77},
                    {5,14,23,32,41,50,57,58,59,63,64,65,66,67,69,70,71,75,76,77},
                    {6,15,24,33,42,51,60,61,62,63,64,65,66,67,68,70,71,78,79,80},
                    {7,16,25,34,43,52,60,61,62,63,64,65,66,67,68,69,71,78,79,80},
                    {8,17,26,35,44,53,60,61,62,63,64,65,66,67,68,69,70,78,79,80},
                    {0,9,18,27,36,45,54,55,56,63,64,65,73,74,75,76,77,78,79,80},
                    {1,10,19,28,37,46,54,55,56,63,64,65,72,74,75,76,77,78,79,80},
                    {2,11,20,29,38,47,54,55,56,63,64,65,72,73,75,76,77,78,79,80},
                    {3,12,21,30,39,48,57,58,59,66,67,68,72,73,74,76,77,78,79,80},
                    {4,13,22,31,40,49,57,58,59,66,67,68,72,73,74,75,77,78,79,80},
                    {5,14,23,32,41,50,57,58,59,66,67,68,72,73,74,75,76,78,79,80},
                    {6,15,24,33,42,51,60,61,62,69,70,71,72,73,74,75,76,77,79,80},
                    {7,16,25,34,43,52,60,61,62,69,70,71,72,73,74,75,76,77,78,80},
                    {8,17,26,35,44,53,60,61,62,69,70,71,72,73,74,75,76,77,78,79} };


// Return the indices that are empty
std::vector<int> getEmpties(std::vector<int>& sudoku) {
  std::vector<int> empties;
  for(int i = 0; i < 81; i++) {
    if(sudoku[i] == 0) {
      empties.push_back(i);
    }
  }
  return empties;
}

// Return the number of candidates for each empty cell
std::vector<int> getLengths(std::vector< std::vector<int> >& candidates, std::vector<int>& empties) {
  std::vector<int> lens(empties.size());
  for(int i = 0; i < empties.size(); i++) {
    lens[i] = candidates[empties[i]].size();
  }
  return lens;
}

// Pair of empty element and its length
struct Pairs { 
  int length, empty; 
}; 

// Compares two intervals according to staring times. 
bool compareInterval(Pairs i1, Pairs i2) { 
  return (i1.length < i2.length); 
} 

// Sort empty elements by their length
std::vector<int> sortEmpties(std::vector<int>& empties, std::vector<int>& lens) {
  
  // Initialize pairs of lengths and empties
  std::vector<Pairs> v(lens.size());
  for(int i = 0; i < lens.size(); i++) {
    v[i].length = lens[i];
    v[i].empty  = empties[i];
  } 
  // Sort Pairs
  sort(v.begin(), v.end(), compareInterval); 
  
  // Reorder empties
  for(int i = 0; i < empties.size(); i++) {
    empties[i] = v[i].empty;
  }
  
  return empties;
}

// GET CANDIDATES
std::vector< std::vector<int> > getCandidates(std::vector<int>& sudoku, std::vector<int> nums) {
  
  std::vector< std::vector<int> > out(81);
  
  for(int i = 0; i < 81; i++) {
    if(sudoku[i] != 0) {
      std::vector<int> s(1);
      s[0] = sudoku[i];
      out[i] = s;
    } else {
      std::vector<int> diff(9);
      for(int n = 0; n < 9; n++) {
        diff[n] = n+1;
      } 
      for(int j = 0; j < 20; j++) {
        int val = arr[i][j];
        if(sudoku[val] != 0) {
          if(std::find(diff.begin(), diff.end(), sudoku[val]) != diff.end()) {
            diff.erase(std::remove(diff.begin(), diff.end(), sudoku[val]), diff.end());
          }
        }
      }
      out[i] = diff;
    }
  }
  return out;
}



// Fast backtracking solver
// [[Rcpp::export]]
bool solveBacktrack(std::vector<int>& sudoku, std::vector< std::vector<int> >& candidates,
                    std::vector<int>& empties) {
  
  // If completed, return true
  if(empties.size() == 0) {
    return true;
  }
  
  // Find the empty element with the minimum number of candidates
  int index = empties[0];
  int clen = candidates[index].size();
  if(clen > 1) {
    for(int i = 1; i < empties.size(); ++i) {
      if(candidates[empties[i]].size() < clen) {
        index = empties[i];
        clen = candidates[empties[i]].size();
        if(clen == 1) {
          break;
        }
      }
    }
  }
  // Vector to record which elements' candidates are updates
  std::vector<int> to_update(20);
  int nupdated = 0;
  
  // Loop over candidates, filling them in then backtracking if it doesn't work;
  for(int o = 0; o < clen; ++o) {
    
    // Fill in option
    int v = candidates[index][o];
    
    // Loop over all peers.  Remove value from peers if it's there.  Backtrack if
    // any peer is left with no candidates.
    for(int j = 0; j < 20; ++j) {
      
      if(sudoku[arr[index][j]] == 0) {
        
        int p = arr[index][j];
        for(int l = 0; l < candidates[p].size(); ++l) {
          if(candidates[p][l] == v) {
            if(candidates[p].size() == 1) {
              goto BACKTRACK;
            }
            to_update[nupdated] = p;
            candidates[p].erase(candidates[p].begin() + l);
            nupdated += 1;
            break;
          }
        }
      }
    }
    
    // Fil in the element, update the vector of empty cells, and solve
    sudoku[index] = v;
    empties.erase(std::remove(empties.begin(), empties.end(), index), empties.end());
    if(solveBacktrack(sudoku, candidates, empties)) {
      return true;
    }
    
    // Otherwise backtrack 
    empties.insert(empties.end(), index);
    BACKTRACK : {
      // Backtrack value
      sudoku[index] = 0;
      // Backtrack candidates for peers
      for(int j = 0; j < nupdated; ++j) {
        candidates[to_update[j]].insert(candidates[to_update[j]].end(), v);
      } 
      nupdated = 0;
    }
  }
  return false;
}


// Full solver
// [[Rcpp::export]]
std::vector<int> solve_sudoku_(std::vector<int> sudoku, std::vector<int> nums) {
  
  // Get candidates
  std::vector< std::vector<int> > candidates;
  candidates = getCandidates(sudoku, nums);
  
  // Get empties
  std::vector<int> empties;
  empties = getEmpties(sudoku);
  
  // Get number of candidates for each empty cell
  std::vector<int> lens;
  lens = getLengths(candidates, empties);
  
  // Sorty empties according to the number of empties
  empties = sortEmpties(empties, lens);
  
  // Solve 
  solveBacktrack(sudoku, candidates, empties);
  
  return sudoku;
}
