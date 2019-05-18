#' Intermediate functions
#'
#' These functions help the sudoku solver solve puzzles!

#' @export
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
#' @export
numbers <- c(1:9)

# See what's not in row
#' @export
not_in_row <- function(sudoku_df, row) {
  sudoku::numbers[!sudoku::numbers %in% sudoku_df[, 1][sudoku_df[, 2] == row]]
}

# See what's not in column
#' @export
not_in_col <- function(sudoku_df, col) {
  sudoku::numbers[!sudoku::numbers %in% sudoku_df[, 1][sudoku_df[, 3] == col]]
}

# See what's not in box
#' @export
not_in_box <- function(sudoku_df, box) {
  sudoku::numbers[!sudoku::numbers %in% sudoku_df[, 1][sudoku_df[, 4] == box]]
}
