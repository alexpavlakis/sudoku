#' Intermediat functions
#'
#' These functions help the sudoku solver solve puzzles!
#' @param sudoku_df an unsolved sudoku, in dataframe form.
#' @export

cant_bes_getter <- function(sudoku_df) {
  # Get all the can't bes!
  cant_bes <- list()
  for(i in 1:nrow(sudoku_df)) {
    if(is.na(sudoku_df$value[i])) {
      cant_bes[[i]] <- unique(c(sudoku_df$value[sudoku_df$col == sudoku_df$col[i]],
                                sudoku_df$value[sudoku_df$row == sudoku_df$row[i]],
                                sudoku_df$value[sudoku_df$box == sudoku_df$box[i]]))
      cant_bes[[i]] <- cant_bes[[i]][!is.na(cant_bes[[i]])]
    } else {
      cant_bes[[i]] <- NA
    }
  }
  return(cant_bes)
}

#' @export
cant_bes_lengths <- function(sudoku_df, cant_bes) {
  length_cant_bes <- unlist(lapply(cant_bes, length))
  for(i in seq_along(length_cant_bes)) {
    if(length_cant_bes[i] == 8) {
      sudoku_df$value[i] <- c(1:9)[!c(1:9) %in% cant_bes[[i]]]
    }  
  }
  return(sudoku_df)
}




