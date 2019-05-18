#' Check the integrity of a sudoku
#'
#' This function allows you to check whether a sudoku solution is good
#' @param sudoku_matrix a sudku matrix
#' @export
#' @examples
#' solved_puzzle <- solve_sudoku(sudoku)
#' check_integrity(solved_puzzle)

check_integrity <- function(sudoku_df) {
  rows_good <- NULL
  cols_good <- NULL
  boxes_good <- NULL
  suppressWarnings(
    for(i in 1:9) {
      rows_good[i] <- all(sort(sudoku_df[sudoku_df[, 2] == i, 1]) == c(1:9)) 
      cols_good[i] <- all(sort(sudoku_df[sudoku_df[, 3] == i, 1]) == c(1:9)) 
      boxes_good[i] <- all(sort(sudoku_df[sudoku_df[, 4] == i, 1]) == c(1:9)) 
    } 
  )
  return(all(rows_good, cols_good, boxes_good))
}
