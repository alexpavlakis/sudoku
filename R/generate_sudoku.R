#' Sudoko generator
#'
#' This function generates completed sudoku puzzles
#' @param seed integer used to create reproducible randomly generated puzzles.  defaults to NULL.
#' @export
#' @examples
#' random_puzzle <- generate_sudoku(seed = 56)
#' print_sudoku(random_puzzle)

generate_sudoku <- function(seed = NULL) {
  mat <- matrix(NA, nrow = 9, ncol = 9)
  if(!is.null(seed)) set.seed(seed)
  solve_sudoku(mat, shuffle = TRUE)
}


#' Puzzle generator
#'
#' This function generates sudoku puzzles with a specified number of clues.
#' @param clues number of non empty cells in the puzzle (must be <= 81 and >= 0).
#' @param seed integer used to create reproducible randomly generated puzzles.  defaults to NULL.
#' @export
#' @examples
#' random_puzzle <- generate_puzzle(clues = 45, seed = 56)
#' print_sudoku(random_puzzle)
generate_puzzle <- function(clues = 56, seed = NULL) {
  
  full_puzzle <- generate_sudoku(seed = seed)
  
  # Random pattern symmetrical
  fill <- c(rep(NA, (81-clues)), rep(0, clues))
  fill <- fill[sample(1:81)]
  om <- matrix(fill, nrow = 9)
  om[lower.tri(om)] <- t(om)[lower.tri(om)]
  
  for(i in 1:9) {
    for(j in 1:9) {
      if(is.na(om[i, j]))
        full_puzzle[i, j] <- NA
    }
  }
  full_puzzle
}




