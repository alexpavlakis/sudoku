#' Perform some basic diagnostics on a sudoku puzzle
#'
#' This function returns a puzzle's number of clues, naked singles, hidden signles, whether it is solvable, and whether its solution is unique.
#' @param sudoku_matrix a sudoku matrix
#' @useDynLib sudokuplyr, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
#' @examples
#' analyze_sudoku(sudoku_matrix = sudoku)

analyze_sudoku <- function(sudoku_matrix) {
  
  if(!check_sudoku(sudoku_matrix)) {
    stop('sudoku_matrix must by a 9x9 numeric matrix with NAs for empty values')
  }
  
  sudoku_df <- as_sdf(sudoku_matrix)
  # Attempt to solve with logic 
  nns <- count_naked_singles(sudoku_df = sudoku_df,
                             cant_bes  = cant_bes_getter(sudoku_df))
  nhs <- count_hidden_singles(sudoku_df = sudoku_df)
  out <- list(clues          = 81 - sum(is.na(sudoku_matrix)), 
              naked_singles  = nns,
              hidden_singles = nhs,
              unique         = is_unique(sudoku_matrix),
              legal_solution = is_legal(solve_sudoku(sudoku_matrix)),
              sudoku         = sudoku_matrix)
  structure(out, class = 'analyzed_sudoku')
}

#' print method for objects of class analyzed_sudoku
#' @param x an object of class analyzed_sudoku
#' @param ... additional parameters to pass to method
#' @export
print.analyzed_sudoku <- function(x, ...) {
  print_sudoku(x$sudoku)
  cat(paste(' clues:          ', x$clues, '\n',
            'naked singles:  ', x$naked_singles, '\n',
            'hidden singles: ', x$hidden_singles, '\n',
            'legal solution: ', x$legal_solution, '\n',
            'unique solution:', x$unique))
}

#' summary method for objects of class analyzed_sudoku
#' @param object an object of class analyzed_sudoku
#' @param ... additional parameters to pass to method
#' @export
summary.analyzed_sudoku <- function(object, ...) print(object)
