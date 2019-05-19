#include <Rcpp.h>
using namespace Rcpp;

// This is a simple example of exporting a C++ function to R. You can
// source this function into an R session using the Rcpp::sourceCpp 
// function (or via the Source button on the editor toolbar). Learn
// more about Rcpp at:
//
//   http://www.rcpp.org/
//   http://adv-r.had.co.nz/Rcpp.html
//   http://gallery.rcpp.org/
//

// [[Rcpp::export]]
IntegerVector not_in_row_c(IntegerMatrix sudoku_df, int row) {
  IntegerVector x;
  IntegerVector nums;
  IntegerVector out;
  nums = IntegerVector::create(1, 2, 3, 4, 5, 6, 7, 8, 9);
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
IntegerVector not_in_col_c(IntegerMatrix sudoku_df, int col) {
  IntegerVector x;
  IntegerVector nums;
  IntegerVector out;
  nums = IntegerVector::create(1, 2, 3, 4, 5, 6, 7, 8, 9);
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
IntegerVector not_in_box_c(IntegerMatrix sudoku_df, int box) {
  IntegerVector x;
  IntegerVector nums;
  IntegerVector out;
  nums = IntegerVector::create(1, 2, 3, 4, 5, 6, 7, 8, 9);
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
IntegerVector can_bes_getter_index_c(IntegerMatrix sudoku_df, int index) {
  
  IntegerVector out;
  
  if(sudoku_df(index, 0) == NA_INTEGER) {
    int row = sudoku_df(index, 1);
    int col = sudoku_df(index, 2);
    int box = sudoku_df(index, 3);
    int n = sudoku_df(_, 0).size();
    IntegerVector x;
    IntegerVector nums = IntegerVector::create(1, 2, 3, 4, 5, 6, 7, 8, 9);
    for(int i=0; i < n; i++) {
      if(sudoku_df(i, 1) == row) {
        x.push_back(sudoku_df(i, 0));
      } else if(sudoku_df(i, 2) == col) {
        x.push_back(sudoku_df(i, 0));
      } else if(sudoku_df(i, 3) == box) {
        x.push_back(sudoku_df(i, 0));
      }
    }
    out = setdiff(nums, na_omit(x));
    return out;
  }
  
  else {
    out = NA_INTEGER;
    return out;
  }
}


