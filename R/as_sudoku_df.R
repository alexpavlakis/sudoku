#' Intermediate functions
#'
#' Convert a sudoku matrix to a sudoku data frame
#' @param sudoku_matrix a 9x9 sudoku matrix.

#' @export
as_sudoku_df <- function(sudoku_matrix) {
  sudoku_df <- matrix(
    c(c(sudoku_matrix),
      rep(c(1:9), times = 9), rep(c(1:9), each = 9),
      c(boxes)), nrow = 81, byrow = FALSE
  )
  return(apply(sudoku_df, 2, as.integer))
}

boxes <- matrix(c(1, 1, 1, 2, 2, 2, 3, 3, 3,
                  1, 1, 1, 2, 2, 2, 3, 3, 3,
                  1, 1, 1, 2, 2, 2, 3, 3, 3,
                  4, 4, 4, 5, 5, 5, 6, 6, 6,
                  4, 4, 4, 5, 5, 5, 6, 6, 6,
                  4, 4, 4, 5, 5, 5, 6, 6, 6,
                  7, 7, 7, 8, 8, 8, 9, 9, 9,
                  7, 7, 7, 8, 8, 8, 9, 9, 9,
                  7, 7, 7, 8, 8, 8, 9, 9, 9),
                nrow = 9, ncol = 9, byrow = TRUE)
