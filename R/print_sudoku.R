#' Sudoku printer
#'
#' This function prints sudoku puzzles.
#' @param sudoku_matrix a 9x9 matrix
#' @export
#' @examples
#' print_sudoku(sudoku)
#' solved_sudoku <- solve_sudoku(sudoku)
#' print_sudoku(solved_sudoku)

print_sudoku <- function(sudoku_matrix) {
  
  if(!all(dim(sudoku_matrix) == c(9, 9))) {
    stop('sudoku_matrix must be a 9x9 matrix')
  }
  
  # Spread out the letters and fill in
  sdf <- cbind(sudoku_matrix, cbind(matrix(rep(rep(NA, 9), 4), ncol = 4)))[,c(10,1:3,11,4:6,12,7:9,13)]
  sdf <- rbind(sdf, rbind(matrix(rep(rep(NA, 13), 4), nrow = 4)))[c(10,1:3,11,4:6,12,7:9,13),]
  sdf <- apply(sdf, 2, function(x) ifelse(is.na(x), '', x))
  out <- matrix('', 13, 13)
  for(i in 1:13) {
    for(j in 1:13) {
      if(i %in% c(1, 5, 9, 13) & j %in% c(1, 5, 9, 13)) {
        out[i, j] <- '+'
      } else if(i %in% c(1, 5, 9, 13)) {
        out[i, j] <- '-'
      } else if(j %in% c(1, 5, 9, 13)) {
        out[i, j] <- '|'
      } else {
        out[i, j] <- sdf[i, j] 
      }
    }
  }
  dimnames(out) <- list(rep('', 13), rep('', 13))
  print(out, quote = F)
}
