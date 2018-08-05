#' Intermediate functions
#'
#' These functions help the sudoku solver solve puzzles!
#' @param sudoku_df an unsolved sudoku, in dataframe form.
#' @param cant_bes all the cant_bes of the current sudoku
#' @param dimension row, col, or box

#' @export
element_checker <- function(sudoku_df, cant_bes,
                            dimension = c("row", "col", "box")) {
  # Get correct dimention
  if(dimension == "row") {
    dimension_index <- 2
  } else if(dimension == "col") {
    dimension_index <- 3
  } else if(dimension == "box") {
    dimension_index <- 4
  } else {
    stop("Provide a valid dimension!")
  }
  
  # Look over the df and fill in values
  for(i in 1:nrow(sudoku_df)) {
    if(is.na(sudoku_df$value[i])) {
      # Which idices are in the same value of dimension?
      in_index <- which(sudoku_df[, dimension_index] == sudoku_df[i, dimension_index])
      in_index <- in_index[in_index != i]
      in_already <- sudoku_df$value[sudoku_df[, dimension_index] == sudoku_df[i, dimension_index]]
      
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
      answers <- answers[answers %in% not_in_box(sudoku_df$box[i])]
      answers <- answers[answers %in% not_in_row(sudoku_df$row[i])]
      answers <- answers[answers %in% not_in_col(sudoku_df$col[i])]
      if(length(answers[!is.na(answers)]) == 1) {
        sudoku_df$value[i] <- answers
      }  
    }
  }
  return(sudoku_df)
}
