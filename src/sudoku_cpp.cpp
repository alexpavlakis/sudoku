#include <Rcpp.h>
using namespace Rcpp;


// [[Rcpp::export]]
IntegerVector can_bes_getter_index_c(IntegerMatrix sudoku_df, int index, 
                                     IntegerVector nums) {
  
  IntegerVector out;
  
  if(sudoku_df(index, 0) == NA_INTEGER) {
    
    int row = sudoku_df(index, 1);
    int col = sudoku_df(index, 2);
    int box = sudoku_df(index, 3);
    IntegerVector x;
    
    for(int i=0; i < 81; i++) {
      
      if(sudoku_df(i, 0) != NA_INTEGER) {
        
        if(sudoku_df(i, 2) == col) {
          x.push_back(sudoku_df(i, 0));
        } else if(sudoku_df(i, 3) == box) {
          x.push_back(sudoku_df(i, 0));
        } else if(sudoku_df(i, 1) == row) {
          x.push_back(sudoku_df(i, 0));
        }
        
      }
    }
    out = setdiff(nums, x);
  }
  
  else {
    out = NA_INTEGER;
  }
  return out;
}


// [[Rcpp::export]]
List cant_bes_getter_c(IntegerMatrix sudoku_df) {
  
  List out;
  int n = sudoku_df(_, 0).size();
  
  for(int i = 0; i < n; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      
      IntegerVector x;
      int row = sudoku_df(i, 1);
      int col = sudoku_df(i, 2);
      int box = sudoku_df(i, 3);
      
      for(int j = 0; j < n; j++) {
        if(sudoku_df(j, 1) == row) {
          x.push_back(sudoku_df(j, 0));
        } else if(sudoku_df(j, 2) == col) {
          x.push_back(sudoku_df(j, 0));
        } else if(sudoku_df(j, 3) == box) {
          x.push_back(sudoku_df(j, 0));
        }
      }
      out.push_back(unique(na_omit(x)));
    } else {
      out.push_back(NA_INTEGER);
    }
    
  }
  return out;
}





//[[Rcpp::export]]
IntegerMatrix cant_bes_lengths_c(IntegerMatrix sudoku_df, List cant_bes,
                                 IntegerVector nums) {
  
  int n = sudoku_df.size();
  
  for(int i = 0; i < n; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      IntegerVector cb;
      cb = cant_bes[i];
      if(cb.size() == 8) {
        int value = *setdiff(nums, cb).begin();
        sudoku_df(i, 0) = value;
      }  
    }
  }
  return sudoku_df;
}


// [[Rcpp::export]]
bool check_integrity_c(IntegerMatrix sudoku_df, IntegerVector nums) {
  
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


// [[Rcpp::export]]
IntegerMatrix element_checker_c(IntegerMatrix sudoku_df, List cant_bes, 
                                IntegerVector nums, int dimension) {
  
  dimension = dimension - 1;
  
  // Loop over the df and fill in values
  for(int p = 0; p < 81; p++) {
    
    if(sudoku_df(p, 0) == NA_INTEGER) {
      
      // Get all cant bes
      
      // Get the indices and values in the same dimension
      IntegerVector in_index;
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

      // What's not in dimension already
      IntegerVector cant_bes_in;
      
      for(int j = 0; j < 8; j++) {
        IntegerVector cb_ind;
        cb_ind = cant_bes[in_index[j]];
        for(int n = 0; n < cb_ind.size(); n++) {
          cant_bes_in.push_back(cb_ind[n]);
        }
      }
      cant_bes_in = na_omit(cant_bes_in);
      int open_elements = 8 - in_already.size();
      
      // Find those that can't be in as many elements as are open..
      IntegerVector possibilities;
      
      for(int j = 1; j < 10; j++) {
        IntegerVector as_num;
        as_num = cant_bes_in[cant_bes_in == j];
        possibilities.push_back(as_num.size());
      }
      
      IntegerVector a;
      IntegerVector which_in;
      
      // first get which possibilities = the number of open elements
      for(int j = 0; j < 9; j++) {
        if(possibilities[j] == open_elements) {
          which_in.push_back(j+1);
        }
      }
      a = setdiff(which_in, in_already);
      
      if(a.size() == 1) {
        sudoku_df(p, 0) = *a.begin();
        cant_bes = cant_bes_getter_c(sudoku_df);
      }
      
    }
  }
  return sudoku_df;
}


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

// [[Rcpp::export]]
IntegerVector which_empties(IntegerMatrix sudoku_df) {
  IntegerVector empties;
  for(int i = 0; i < 81; i++) {
    if(sudoku_df(i, 0) == NA_INTEGER) {
      empties.push_back(i);
    }
  }
  return empties;
} 



// [[Rcpp::export]]
IntegerMatrix logical_solver_c(IntegerMatrix sudoku_df, bool verbose, 
                               IntegerVector nums) {
  int empty_start = 1;
  int empty_finish = 0;
  
  while(empty_start != empty_finish & num_empties(sudoku_df) > 0) {
    empty_start = num_empties(sudoku_df);
    
    // If there's only one option, it's that
    sudoku_df = cant_bes_lengths_c(sudoku_df, cant_bes_getter_c(sudoku_df), nums);
    // Can't be in box
    sudoku_df = element_checker_c(sudoku_df, cant_bes_getter_c(sudoku_df), nums, 4);
    // Cant' be in row
    sudoku_df = element_checker_c(sudoku_df, cant_bes_getter_c(sudoku_df), nums, 2);
    // Can't be in col
    sudoku_df = element_checker_c(sudoku_df, cant_bes_getter_c(sudoku_df), nums, 3);
    sudoku_df = cant_bes_lengths_c(sudoku_df, cant_bes_getter_c(sudoku_df), nums);
    
    empty_finish = num_empties(sudoku_df);
    
    // Conver to matrix and show
    if(verbose) {
      IntegerVector smat = sudoku_df(_, 0);
      smat.attr("dim") = Dimension(9, 9);
      print(smat);
    }
  }
  return sudoku_df;
}



// [[Rcpp::export]]
bool solve_backtracking_c(IntegerMatrix sudoku_df, IntegerVector empties, bool verbose,
                          IntegerVector nums) {
  
  if(empties.size() == 0) {
    return true;
  }
  
  int index = *empties.begin();
  IntegerVector empties2 = empties;
  empties2.erase(0);
  NumericVector can_be_here;
  can_be_here = can_bes_getter_index_c(sudoku_df, index, nums);
  int options_length = can_be_here.size();
  
  for(int i = 0; i < options_length; i++) {
    
    sudoku_df(index, 0) = can_be_here[i];
    
    if(verbose) {
      IntegerVector smat = sudoku_df(_, 0);
      smat.attr("dim") = Dimension(9, 9);
      print(smat);
    }
    
    if(solve_backtracking_c(sudoku_df, empties2, verbose, nums)) {
      return true;
    }
    sudoku_df(index, 0) = NA_INTEGER;
  }
  return false;
}


