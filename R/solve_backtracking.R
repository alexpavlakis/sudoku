#' Solve a sudoku by the backtracking algorithm
#'
#' This function recursively solves a sudoku
#' @param sudoku_df a sudku dataframe
#' @param empties the empty elements
#' @param cant_bes a list of what each empty element can't be
#' @param verbose do you want to see the output at every step? (it's a lot!)

solve_backtracking <- function(sudoku_df, empties, verbose) {
  
  if(length(empties) == 0) {
    out <<- sudoku_df
    return(TRUE)
  }
  
  index <- empties[1]
  can_be_here <- can_bes_getter_index_c(sudoku_df, index-1)
  
  for(i in can_be_here) {
    sudoku_df[index, 1] <- i
    
    if(verbose) {
      print(matrix(sudoku_df[, 1], nrow = 9, ncol = 9))
    }
    
    if(solve_backtracking(sudoku_df = sudoku_df, 
                          empties   = empties[-1],
                          verbose   = verbose)) {
      return(TRUE)
    }
    sudoku_df[index, 1] <- NA
  }
  return(FALSE)
}














