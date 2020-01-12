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
  sdf <- as_sdf(mat)
  solve_backtracking_(sdf, which(is.na(sdf[, 1])) - 1, F, sudokuplyr::ind_list, T)
  return(as.sudoku(matrix(sdf[, 1], nrow = 9)))
}


#' Puzzle generator
#'
#' This function generates sudoku puzzles with a specified number of clues.
#' @param clues number of non empty cells in the puzzle (must be <= 81 and >= 0).
#' @param unique add the requirement that the puzzle must have a unique solution. defaults to TRUE.
#' @param seed integer used to create reproducible randomly generated puzzles.  defaults to NULL.
#' @export
#' @examples
#' random_puzzle <- generate_puzzle(clues = 32, unique = TRUE, seed = 56)
#' print_sudoku(random_puzzle)

generate_puzzle <- function(clues = 56, unique = TRUE, seed = NULL) {
  s <- generate_sudoku(seed = seed)
  while(sum(is.na(s)) <= (81 - clues)) {
    coord <- sample(1:9, size = 2, replace = T)
    tmp <- s
    tmp[coord[1], coord[2]] <- NA
    tmp[coord[2], coord[1]] <- NA
    if(unique) {
      if(is_unique(tmp)) {
        s <- tmp
      }
    } else {
      s <- tmp
    }
  }
  return(as.sudoku(s))
}




