#' Check the integrity of a sudoku
#'
#' This function allows you to check whether a sudoku solution is good
#' @param sudoku_df a sudku matrix
#' @export
#' @examples
#' solved_puzzle <- solve_sudoku(sudoku)
#' check_integrity(solved_puzzle)

check_integrity <- function(sudoku_df) {
  
  if(nrow(sudoku_df) == 9) sudoku_df <- as_sudoku_df(sudoku_df)
  if(any(is.na(sudoku_df))) return(FALSE)
  
  check_integrity_c(sudoku_df, c(1L:9L))
}
