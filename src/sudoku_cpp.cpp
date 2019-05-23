#include <Rcpp.h>
using namespace Rcpp;

// Moving some base functions to cpp for speed up.


// [[Rcpp::export]]
IntegerVector not_in_row_c(IntegerMatrix sudoku_df, int row, IntegerVector nums) {
  
  IntegerVector x;
  IntegerVector out;
  
  int n = sudoku_df(_, 0).size();
  for(int i = 0; i < n; i++) {
    if(sudoku_df(i, 1) == row) {
      x.push_back(sudoku_df(i, 0));
    }
  }
  out = setdiff(nums, na_omit(x));
  return out;
}

// [[Rcpp::export]]
IntegerVector not_in_col_c(IntegerMatrix sudoku_df, int col, IntegerVector nums) {
  
  IntegerVector x;
  IntegerVector out;
  
  int n = sudoku_df(_, 0).size();
  for(int i = 0; i < n; i++) {
    if(sudoku_df(i, 2) == col) {
      x.push_back(sudoku_df(i, 0));
    }
  }
  out = setdiff(nums, na_omit(x));
  return out;
}

// [[Rcpp::export]]
IntegerVector not_in_box_c(IntegerMatrix sudoku_df, int box, IntegerVector nums) {
  
  IntegerVector x;
  IntegerVector out;
  
  int n = sudoku_df(_, 0).size();
  for(int i = 0; i < n; i++) {
    if(sudoku_df(i, 3) == box) {
      x.push_back(sudoku_df(i, 0));
    }
  }
  out = setdiff(nums, na_omit(x));
  return out;
}

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
        
        if(sudoku_df(i, 1) == row) {
          x.push_back(sudoku_df(i, 0));
        } else if(sudoku_df(i, 2) == col) {
          x.push_back(sudoku_df(i, 0));
        } else if(sudoku_df(i, 3) == box) {
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
