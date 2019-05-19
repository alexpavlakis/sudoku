#' Intermediate functions
#'
#' These functions help the sudoku solver solve puzzles!
#' @param sudoku_df an unsolved sudoku, in dataframe form.
#' @param cant_bes all the cant_bes of the current sudoku
#' @param dimension row, col, or box

#' @export
element_checker <- function(sudoku_df, cant_bes,
                            dimension = c(2, 3, 4)) {

  # Look over the df and fill in values
  for(i in 1:nrow(sudoku_df)) {
    if(is.na(sudoku_df[i, 1])) {
      # Which idices are in the same value of dimension?
      in_index <- which(sudoku_df[, dimension] == sudoku_df[i, dimension])
      in_index <- in_index[in_index != i]
      in_already <- sudoku_df[, 1][sudoku_df[, dimension] == sudoku_df[i, dimension]]
      
      # What's not in dimension already
      cant_bes_in <- cant_bes[in_index][!is.na(cant_bes[in_index])]
      open_elements <- length(cant_bes_in)
      
      # Find those that can't be in as many elements as are open
      possibilities <- vector(mode = "integer", length = 9)
      for(n in 1:9) {
        possibilities[n] <- length(unlist(cant_bes_in)[unlist(cant_bes_in) == n])
      }
      
      answers <- which(possibilities == open_elements)[!which(possibilities == open_elements) %in% in_already[!is.na(in_already)]]
      # Check the answers
      answers <- answers[answers %in% not_in_box_c(sudoku_df, sudoku_df[i, 4])]
      answers <- answers[answers %in% not_in_col_c(sudoku_df, sudoku_df[i, 3])]
      answers <- answers[answers %in% not_in_row_c(sudoku_df, sudoku_df[i, 2])]
      if(length(answers[!is.na(answers)]) == 1) {
        sudoku_df[i, 1] <- answers
      }  
    }
  }
  return(sudoku_df)
}
