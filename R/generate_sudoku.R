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
  solve_sudoku(mat, shuffle = TRUE)
}



generate_puzzle <- function(empties = 56, seed = NULL, unique = FALSE) {
  full_puzzle <- generate_sudoku(seed = seed)
  
  out <- full_puzzle
  not_the_same <- TRUE
  while(not_the_same) {
    
    out <- full_puzzle
    # Random pattern symmetrical
    fill <- c(rep(NA, empties), rep(0, 81-empties))
    fill <- fill[sample(1:81)]
    om <- matrix(fill, nrow = 9)
    om[lower.tri(om)] <- t(om)[lower.tri(om)]
    
    for(i in 1:9) {
      for(j in 1:9) {
        if(is.na(om[i, j]))
          out[i, j] <- NA
      }
    }
    if(unique) {
      not_the_same <- !identical(full_puzzle, solve_sudoku(out, shuffle = T))
    } else {
      not_the_same <- FALSE
    }
  } 
  out
}


get_all_solutions <- function(sudoku_matrix, stop_early = TRUE, verbose = FALSE) {
  
  if(nrow(sudoku_matrix) != 9 & ncol(sudoku_matrix) != 9) {
    stop('sudoku_matrix must by a 9x9 numeric matrix with NAs for empty values')
  }
  
  # Concert to sudoku df
  sudoku_df <- as_sudoku_df(sudoku_matrix = sudoku_matrix)
  
  tryCatch( {
    out <- check_unique_solutions(sudoku_df  = sudoku_df,
                                  empties    = which(is.na(sudoku_df[, 1]))-1,
                                  verbose    = verbose,
                                  nums       = 1L:9L,
                                  ind_list   = sudoku::ind_list,
                                  shuffle    = FALSE,
                                  counter    = 0,
                                  out        = list(),
                                  stop_early = stop_early)
  }, error = function(e) print('multiple solutions detected'))
  out
}


