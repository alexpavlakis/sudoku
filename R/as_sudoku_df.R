#' Intermediate functions
#'
#' Convert a sudoku matrix to a sudoku data frame

#' @export

as_sudoku_df <- function(sudoku_matrix) {
  sudoku_df <- data.frame(
    value = c(sudoku_matrix),
    row = rep(c(1:9), times = 9),
    col = rep(c(1:9), each = 9),
    box = c(boxes)
  )
  return(sudoku_df)
}
