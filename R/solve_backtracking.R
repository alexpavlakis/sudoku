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
  cant_be_here <- cant_bes_getter_index(sudoku_df, index)
  
  for(i in 1:9) {
    
    if(!i %in% cant_be_here) {
      
      sudoku_df[index, 1] <- i
      
      if(verbose) {
        print(matrix(sudoku_df[, 1], nrow = 9, ncol = 9))
      }
      
      if(solve_backtracking(sudoku_df = sudoku_df, 
                            empties   = which(is.na(sudoku_df[, 1])),
                            verbose   = verbose)) {
        return(TRUE)
      }
      sudoku_df[index, 1] <- NA
    }
  }
  return(FALSE)
}






