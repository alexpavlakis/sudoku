#' Check if a solution is legal
#'
#' This function allows you to check whether a sudoku solution is good
#' @param sudoku_df a sudoku matrix
#' @useDynLib sudokuplyr, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
#' @examples
#' solved_puzzle <- solve_sudoku(sudoku)
#' is_legal(solved_puzzle)

is_legal <- function(sudoku_df) {
  if(nrow(sudoku_df) == 9) sudoku_df <- as_sudoku_df(sudoku_df)
  if(any(is.na(sudoku_df))) return(FALSE)
  check_integrity(sudoku_df, c(1L:9L))
}


#' Check if a puzzle has a unique solution
#'
#' This function allows you to check whether an unsolved sudoku puzzle has a unique solution.
#' @param sudoku_matrix a sudoku matrix
#' @param return_all_solutions TRUE if you want to return all solutions.  FALSE if you want a TRUE/FALSE check on uniqueness.  Defaults to FALSE.  For puzzles with few clues (fewer than 25), attempting to return all solutions can take a long time.
#' @param ... additional arguments to pass to solver.
#' @export
#' @examples
#' random_puzzle <- generate_puzzle(clues = 30, unique = TRUE, seed = 56)
#' is_unique(random_puzzle)

is_unique <- function(sudoku_matrix, return_all_solutions = FALSE, ...) {
  out <- NULL
  suppressMessages(
    out <- get_all_solutions(sudoku_matrix, stop_early = !return_all_solutions)
  )
  if(return_all_solutions) {
    return(out)
  } else if(is.null(out)) {
    return(FALSE)
  } else {
    return(TRUE)
  }
}

