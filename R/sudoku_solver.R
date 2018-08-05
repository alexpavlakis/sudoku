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

solve_sudoku <- function(sudoku_matrix, verbose = FALSE,
                          attempts = 50) {
  
  sudoku_df <<- as_sudoku_df(sudoku_matrix)
  
  attempt <- logical_solver(sudoku_df, verbose = verbose)
  
  if(check_integrity(attempt)) {
    out <- attempt
  } else {
    out <- guesser(attempt, verbose = verbose,
                   attempts = attempts)
  }
  if(!check_integrity(out)) {
    out <- NULL
    print("No solution was found!")
  } else {
    out <- matrix(out$value, nrow = 9, ncol = 9)
    print("A solution is found!")
  }
  return(out)
}
