#' Sudoko solver
#'
#' This function allows you to solve a sudoku puzzle
#' @param sudoku_matrix an unsolved sudoku, in matrix form, with NA values for empty cells
#' @param verbose set to TRUE if you want to print intermediate steps.  Default is FALSE.
#' @param attempts if the program cannot solve with only logic, it will make educated guesses.  How many attempt should it make with educated guesses before giving up?
#' @export
#' @examples
#' solved_puzzle <- solve_sudoku(sudoku)
#' solved_puzzle_2 <- solve_sudoku(sudoku2)

solve_sudoku <- function(sudoku_matrix, verbose = FALSE) {
  
  # Attempt to solve with just logic
  sudoku_df <- logical_solver(as_sudoku_df(sudoku_matrix = sudoku_matrix))
  
  # IF that doesn't work, try backtracking
  if(!check_integrity(sudoku_df)) {
    empties <- which(is.na(sudoku_df[, 1]))
    cant_bes <- cant_bes_getter(sudoku_df)
    solve_backtracking(sudoku_df, empties, cant_bes)
    out <- out
  } else {
    out <- sudoku_df
  }
  if(!check_integrity(out)) {
    out <- NULL
    print("No solution was found!")
  } else {
    out <- matrix(out[, 1], nrow = 9, ncol = 9)
    print("A solution is found!")
  }
  return(out)
}

