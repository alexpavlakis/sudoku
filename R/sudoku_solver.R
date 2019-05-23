#' Sudoko solver
#'
#' This function solves sudoku puzzles.
#' @param sudoku_matrix an unsolved sudoku, in matrix form, with NA values for empty cells
#' @param verbose set to TRUE if you want to print intermediate steps.  Default is FALSE. Note that setting to TRUE can increase the time it takes to solve a puzzle by an order of magnitude.
#' @useDynLib sudoku, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
#' @examples
#' print(sudoku)
#' solved_sudoku <- solve_sudoku(sudoku)
#' print(solved_sudoku)

solve_sudoku <- function(sudoku_matrix, verbose = FALSE) {
  
  if(nrow(sudoku_matrix) != 9 & ncol(sudoku_matrix) != 9) {
    stop('sudoku_matrix must by a 9x9 numeric matrix with NAs for empty values')
  }
  
  # Attempt to solve with logic
  sudoku_df <- logical_solver(sudoku_df = as_sudoku_df(sudoku_matrix = sudoku_matrix),
                              verbose   = verbose)
  
  # IF that doesn't work, try backtracking
  if(!check_integrity_c(sudoku_df)) {
    empties <- which(is.na(sudoku_df[, 1]))
    solve_backtracking_c(sudoku_df, empties-1, verbose)
  }
    
  if(!check_integrity(sudoku_df)) {
    print('no solution was found')
  } else {
    out <- matrix(sudoku_df[, 1], nrow = 9, ncol = 9)
    return(out)
  }
}


