#' Intermediate functions
#'
#' Convert a sudoku matrix to a sudoku data frame

#' @export
as_sudoku_df <- function(sudoku_matrix) {
  sudoku_df <- matrix(
    c(c(sudoku_matrix),
      rep(c(1:9), times = 9),
      rep(c(1:9), each = 9),
      c(sudoku::boxes)), nrow = 81, byrow = FALSE
  )
  return(sudoku_df)
}
