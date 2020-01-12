#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
// Sudoku numbers
IntegerVector nums = IntegerVector::create(1, 2, 3, 4, 5, 6, 7, 8, 9);

// Convert a 9x9 sudoku puzzle into a 81x4 matrix where:
// - the first column is the value in the cell;
// - the second column is the row index;
// - the third column is the column index;
// - the fourth column is the box index.
// [[Rcpp::export]]
IntegerMatrix as_sudoku_df_(IntegerVector values, IntegerVector row, IntegerVector col, IntegerVector box) {
  IntegerMatrix out(81, 4);
  for(int i = 0; i < 81; i++) {
    out(i, 0) = values[i];
    out(i, 1) = row[i];
    out(i, 2) = col[i];
    out(i, 3) = box[i];
  }
  return out;
}

// return all numbers 1-9 that are options for a given cell.
// [[Rcpp::export]]
IntegerVector can_bes_getter_index(IntegerMatrix& sudoku_df, IntegerVector ind_list) {
  
  IntegerVector alreadies(20);
  for(int i = 0; i < 20; i++) {
    if(sudoku_df(ind_list[i], 0) != NA_INTEGER) {
      alreadies[i] = sudoku_df(ind_list[i], 0);
    }
  }
  return setdiff(nums, alreadies);
}


// return a list of length 81 containing everything that every cell
// cannot be (NA for already filled cells)
// [[Rcpp::export]]
List cant_bes_getter(IntegerMatrix sudoku_df) {
  
  List out(81);
  
  for(int i = 0; i < 81; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      
      IntegerVector x;
      
      for(int j = 0; j < 81; j++) {
        if(sudoku_df(j, 0) != NA_INTEGER) {
          if(sudoku_df(j, 1) == sudoku_df(i, 1)) {
            x.push_back(sudoku_df(j, 0));
          } else if(sudoku_df(j, 2) == sudoku_df(i, 2)) {
              x.push_back(sudoku_df(j, 0));
          } else if(sudoku_df(j, 3) == sudoku_df(i, 3)) {
              x.push_back(sudoku_df(j, 0));
          }
        }
      }
      
      out[i] = unique(x);
    } else {
      out[i] = NA_INTEGER;
    }
  }
  return out;
}




// If there is a cell that can only be one number, fill in that number.
// [[Rcpp::export]]
IntegerMatrix cant_bes_lengths(IntegerMatrix sudoku_df, List cant_bes) {
  
  for(int i = 0; i < 81; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      IntegerVector cb;
      cb = cant_bes[i];
      if(cb.size() == 8) {
        sudoku_df(i, 0) = *setdiff(nums, cb).begin();
      }  
    }
  }
  return sudoku_df;
}

// Count naked singles
// [[Rcpp::export]]
int count_naked_singles_(IntegerMatrix sudoku_df, List cant_bes) {
  
  int counter = 0;
  for(int i = 0; i < 81; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      IntegerVector cb;
      cb = cant_bes[i];
      if(cb.size() == 8) {
        counter += 1;
      }  
    }
  }
  return counter;
}

// check that each row, column, and box has 1:9 exclusively
// [[Rcpp::export]]
bool check_integrity(IntegerMatrix sudoku_df) {
  
  for(int j = 1; j < 4; j++) {
    for(int i = 1; i < 10; i++) {
      IntegerVector x;
      for(int n = 0; n < 81; n++) {
        if(sudoku_df(n, j) == i) {
          x.push_back(sudoku_df(n, 0));
        }
      }
      if(!setequal(x.sort(), nums)) {
        return false;
      }
    }
  }
  return true;
}


// For a given dimension (row, col, box), fill in all cells in the puzzle
// that can only be one value based on others in that dimension.
// [[Rcpp::export]]
IntegerMatrix element_checker(IntegerMatrix sudoku_df, List cant_bes, int dimension) {
  
  // Loop over the df and fill in values
  for(int p = 0; p < 81; p++) {
    
    // For all empty elements....
    if(sudoku_df(p, 0) == NA_INTEGER) {
      
      // Get the indices and values in the same dimension
      std::vector<int> in_index;
      in_index.reserve(8);
      IntegerVector in_already;
      for(int j = 0; j < 81; j++) {
        if(sudoku_df(j, dimension) == sudoku_df(p, dimension)) {
          if(j != p) {
            in_index.push_back(j);
            if(sudoku_df(j, 0) != NA_INTEGER) {
              in_already.push_back(sudoku_df(j, 0));
            }
          }
        }
      }
      
      // If 8 are in already, it's the other one
      if(in_already.size() == 8) {
        sudoku_df(p, 0) = setdiff(nums, in_already)[0];
        cant_bes = cant_bes_getter(sudoku_df);
      }
      
      else {
        // What's not in dimension already
        std::vector<int> cant_bes_in;
        cant_bes_in.reserve(9);
        for(int j = 0; j < 8; j++) {
          IntegerVector cb_ind;
          cb_ind = cant_bes[in_index[j]];
          for(int n = 0; n < cb_ind.size(); n++) {
            if(cb_ind[n] != NA_INTEGER) {
              cant_bes_in.push_back(cb_ind[n]);
            }
          }
        }
        
        // How many numbers are left to add?
        int open_elements = 8 - in_already.size();
        
        // Find numbers which have the same number of possible locations
        // as there are open elements
        IntegerVector which_in;
        for(int j = 1; j < 10; j++) {
          int as_num = std::count(cant_bes_in.begin(), cant_bes_in.end(), j);
          if(as_num == open_elements) {
            which_in.push_back(j);
          }
        }
        
        if(which_in.size() > 0) {
          IntegerVector a = setdiff(which_in, in_already);
          if(a.size() == 1) {
            sudoku_df(p, 0) = a[0];
            cant_bes = cant_bes_getter(sudoku_df);
          }
        }
      }
      
    }
  }
  return sudoku_df;
}

// Return the number of empty cells in a sudoku puzzle
// [[Rcpp::export]]
int num_empties(IntegerMatrix sudoku_df) {
  int empties = 0;
  for(int i = 0; i < 81; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      empties += 1;
    }
  }
  return empties;
} 


// Attempt to solve a puzzle with logic only, using cant_bes_lengths and 
// element_checker
// [[Rcpp::export]]
IntegerMatrix solve_logic_(IntegerMatrix sudoku_df, bool verbose) {
  int empty_start  = 2;
  int empty_finish = 1;
  
  while(empty_start != empty_finish) {
    
    empty_start = num_empties(sudoku_df);
    // If there's only one option, it's that
    sudoku_df = cant_bes_lengths(sudoku_df, cant_bes_getter(sudoku_df));
    // Can't be in row
    sudoku_df = element_checker(sudoku_df, cant_bes_getter(sudoku_df), 1);
    // Cant' be in col
    sudoku_df = element_checker(sudoku_df, cant_bes_getter(sudoku_df), 2);
    // Can't be in box
    sudoku_df = element_checker(sudoku_df, cant_bes_getter(sudoku_df), 3);
    empty_finish = num_empties(sudoku_df);
    
    // Convert to matrix and show
    if(verbose) {
      IntegerVector smat = sudoku_df(_, 0);
      smat.attr("dim") = Dimension(9, 9);
      print(smat);
    }
  }
  return sudoku_df;
}


// [[Rcpp::export]]
int count_hidden_singles_(IntegerMatrix& sudoku_df) {
  
  int counter = 0;
  IntegerMatrix sdf1;
  IntegerMatrix sdf2;
  IntegerMatrix sdf3;
  
  // Can't be in box
  sdf1 = element_checker(clone(sudoku_df), cant_bes_getter(sudoku_df), 3);
  counter += (num_empties(sudoku_df) - num_empties(sdf1));
  // Cant' be in row
  sdf2 = element_checker(clone(sdf1), cant_bes_getter(sdf1), 1);
  counter += (num_empties(sdf1) - num_empties(sdf2));
  // Can't be in col
  sdf3 = element_checker(clone(sdf2), cant_bes_getter(sdf2), 2);
  counter += (num_empties(sdf2) - num_empties(sdf3));
  
  return counter;
}

inline int randWrapper(const int n) { return floor(unif_rand()*n); }


// Return one solution with backtracking algorithm
// [[Rcpp::export]]
bool solve_backtracking_(IntegerMatrix& sudoku_df, IntegerVector& empties, 
                         bool& verbose, List ind_list, bool shuffle) {
  
  if(empties.size() == 0) {
    return true;
  }
  
  int index = empties[0]; 
  IntegerVector empties2 = empties;
  empties2.erase(0);
  NumericVector can_be_here;
  can_be_here = can_bes_getter_index(sudoku_df, ind_list[index]);
  
  if(shuffle) {
    std::random_shuffle(can_be_here.begin(), can_be_here.end(), randWrapper);
  }
  
  for(int i = 0; i < can_be_here.size(); i++) {
    
    sudoku_df(index, 0) = can_be_here[i];
    
    if(verbose) {
      IntegerVector smat = sudoku_df(_, 0);
      smat.attr("dim") = Dimension(9, 9);
      print(smat);
    }
    
    if(solve_backtracking_(sudoku_df, empties2, verbose, ind_list, shuffle)) {
      return true;
    }
    sudoku_df(index, 0) = NA_INTEGER;
  }
  return false;
}


// Return all solutions with backtracking algorithm (or stop once you've found 2)
// [[Rcpp::export]]
List solve_backtracking_all_(IntegerMatrix& sudoku_df, 
                            IntegerVector& empties, 
                            bool& verbose, List ind_list, bool shuffle, 
                            int &counter, List &out,
                            bool stop_early) {
  
  if(empties.size() == 0) {
    
    IntegerVector smat = sudoku_df(_, 0);
    smat.attr("dim") = Dimension(9, 9);
    counter += 1;
    if(stop_early && counter > 1) {
      stop("multiple solutions detected");
    }
    out.push_back(smat);
  } else {
    
    int index = empties[0]; 
    IntegerVector empties2 = empties;
    empties2.erase(0);
    NumericVector can_be_here;
    can_be_here = can_bes_getter_index(sudoku_df, ind_list[index]);
    
    if(shuffle) {
      std::random_shuffle(can_be_here.begin(), can_be_here.end(), randWrapper);
    }
    
    for(int i = 0; i < can_be_here.size(); i++) {
      
      sudoku_df(index, 0) = can_be_here[i];
      
      if(verbose) {
        IntegerVector smat = sudoku_df(_, 0);
        smat.attr("dim") = Dimension(9, 9);
        print(smat);
      }
      solve_backtracking_all_(sudoku_df, empties2, verbose, 
                              ind_list, shuffle, counter, out, stop_early);
      sudoku_df(index, 0) = NA_INTEGER;
    } 
  }
  return out;
}




