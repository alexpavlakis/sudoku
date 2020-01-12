#' Sudoko solver
#'
#' This function solves sudoku puzzles.
#' @param s an unsolved sudoku, in matrix form, with NA values for empty cells.
#' @param ... additional argumenets.
#' @useDynLib sudokuplyr, .registration = TRUE
#' @importFrom Rcpp sourceCpp
#' @export
#' @examples
#' print_sudoku(sudoku)
#' solved_sudoku <- solve_sudoku(sudoku)
#' print_sudoku(solved_sudoku)
solve_sudoku <- function(s, ...) {
  
  # Convert to sudoku (this way puzzles in string or vector format can be solved directly)
  if(!is.sudoku(s)) {
    s <- as.sudoku(s)
  }
  
  # Solve
  s <- c(s)
  s[is.na(s)] <- 0
  solved <- solve_sudoku_(s, 1L:9L)
  out <- matrix(solved, nrow = 9)
  
  # Return
  if(!is_legal(out)) {
    print('no solution was found')
  } else {
    return(as.sudoku(out))
  }
}


#' Sudoku solver - all solutions
#'
#' This function can return all legal solutions to an unsolved puzzle
#' @param sudoku_matrix an unsolved sudoku, in matrix form, with NA values for empty cells
#' @param stop_early set to TRUE if you want to stop once you've found one solution, false if you want to return all solutions.  Defaults to TRUE  For puzzles with few clues (fewer than 25), attempting to return all solutions can take a long time.
#' @param ... additional arguments to pass to solver.
#' @export
#' @examples
#' random_puzzle <- generate_puzzle(seed = 56, clues = 30)
#' all_solutions <- get_all_solutions(random_puzzle)
#' length(all_solutions)
get_all_solutions <- function(sudoku_matrix, stop_early = FALSE, ...) {
  
  if(!check_sudoku(sudoku_matrix)) {
    stop('sudoku_matrix must by a 9x9 numeric matrix with NAs for empty values')
  }
  
  # Concert to sudoku df
  sudoku_df <- as_sdf(sudoku_matrix)
  out <- NULL
  tryCatch( {
    out <- solve_backtracking_all_(sudoku_df  = sudoku_df,
                                   empties    = which(is.na(sudoku_df[, 1]))-1,
                                   verbose    = FALSE,
                                   ind_list   = sudokuplyr::ind_list,
                                   shuffle    = FALSE,
                                   counter    = 0,
                                   out        = list(),
                                   stop_early = stop_early)
  }, error = function(e) 
    message('multiple solutions detected, set stop_early = FALSE to generate them all'))
  if(stop_early) {
    if(is.null(out)) {
      invisible()
    } else {
      message('only one solution detected')
      return(out)
    }
  } else {
    return(lapply(out, as.sudoku))
  }
}

# Convert 9x9 puzzle to 81x4 df where first row is values and others are row, col, box indices.
as_sdf <- function(suduoku_matrix) {
  as_sudoku_df_(values = c(suduoku_matrix), 
                row = rep(c(1:9), times = 9),  col = rep(c(1:9), each = 9),
                box = c(rep(rep(c(1, 4, 7), each = 3), 3),
                        rep(rep(c(2, 5, 8), each = 3), 3),
                        rep(rep(c(3, 6, 9), each = 3), 3)))
}
