#' Sudoko generator
#'
#' This function generates sudoku puzzles
#' @param seed integer used to create reproducible randomly generated puzzles.  defaults to NULL.
#' @export
#' @examples
#' print_sudoku(sudoku)
#' solved_sudoku <- solve_sudoku(sudoku)
#' print_sudoku(solved_sudoku)

generate_sudoku <- function(seed = NULL) {
  mat <- matrix(NA, nrow = 9, ncol = 9)
  if(!is.null(seed)) set.seed(seed)
  mat[sample(1:9, size = 1), sample(1:9, size = 1)] <- sample(1:9, size = 1)
  solve_sudoku(mat, shuffle = TRUE)
}



