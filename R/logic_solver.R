#' Sudoko logic
#'
#' This function attempt to solve a sudoku logically
#' @param sudoku_df an unsolved sudoku, in dataframe form.
#' @param verbose set to TRUE if you want to print intermediate steps.  Default is FALSE.
#' @export
#' @examples

logical_solver <- function(sudoku_df, verbose = FALSE) {
  empty_start <- 1
  empty_finish <- 0
  while(empty_start != empty_finish) {
    empty_start <- sum(is.na(sudoku_df$value))
    
    # Get all the can't bes!
    cant_bes <- cant_bes_getter(sudoku_df = sudoku_df)
    sudoku_df <- cant_bes_lengths(sudoku_df = sudoku_df,
                                  cant_bes = cant_bes)
    
    ### WHAT CAN'T BE IN THE BOX
    sudoku_df <- element_checker(sudoku_df = sudoku_df,
                                 cant_bes = cant_bes,
                                 dimension = "box")
    
    ### WHAT CAN'T BE IN THE ROW
    sudoku_df <- element_checker(sudoku_df = sudoku_df,
                                 cant_bes = cant_bes,
                                 dimension = "row")
    
    ### WHAT CAN'T BE IN THE COLUMN
    sudoku_df <- element_checker(sudoku_df = sudoku_df,
                                 cant_bes = cant_bes,
                                 dimension = "col")
    
    # Convert back to matrix and show
    if(verbose) {
      sudoku_step <- matrix(sudoku_df$value, nrow = 9, ncol = 9)
      print(sudoku_step) 
    }
    empty_finish <- sum(is.na(sudoku_df$value))
  }
  return(sudoku_df)
}
