#' Intermediat functions
#'
#' These functions help the sudoku solver solve puzzles!
#' @param sudoku_df an unsolved sudoku, in dataframe form.
#' @export
cant_bes_getter <- function(sudoku_df) {
  # Get all the can't bes!
  cant_bes <- vector('list', 81)
  for(i in 1:nrow(sudoku_df)) {
    if(is.na(sudoku_df[i, 1])) {
      cant_bes[[i]] <- unique(c(sudoku_df[, 1][sudoku_df[, 2] == sudoku_df[i, 2]],
                                sudoku_df[, 1][sudoku_df[, 3] == sudoku_df[i, 3]],
                                sudoku_df[, 1][sudoku_df[, 4] == sudoku_df[i, 4]]))
      cant_bes[[i]] <- cant_bes[[i]][!is.na(cant_bes[[i]])]
    } else {
      cant_bes[[i]] <- NA
    }
  }
  return(cant_bes)
}

#' @export
can_bes_getter_index <- function(sudoku_df, index) {
  if(is.na(sudoku_df[index, 1])) {
    # Get all the can't bes!
    can_bes <- which(!c(1:9) %in% c(sudoku_df[, 1][sudoku_df[, 2] == sudoku_df[index, 2]],
                                    sudoku_df[, 1][sudoku_df[, 3] == sudoku_df[index, 3]],
                                    sudoku_df[, 1][sudoku_df[, 4] == sudoku_df[index, 4]]))
  } else {
    can_bes <- NA
  }
  return(can_bes)
}


#' @export
cant_bes_lengths <- function(sudoku_df, cant_bes) {
  length_cant_bes <- unlist(lapply(cant_bes, length))
  for(i in seq_along(length_cant_bes)) {
    if(length_cant_bes[i] == 8) {
      sudoku_df[i, 1] <- which(!c(1:9) %in% cant_bes[[i]])
    }  
  }
  return(sudoku_df)
}
