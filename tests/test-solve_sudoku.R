library(sudokuplyr)

# Solution to sudoku
solved_sudoku <- matrix(c(2L, 1L, 3L, 8L, 4L, 7L, 9L, 6L, 5L,
                          4L, 9L, 8L, 6L, 5L, 1L, 3L, 2L, 7L,
                          7L, 6L, 5L, 3L, 2L, 9L, 8L, 1L, 4L,
                          6L, 4L, 2L, 5L, 7L, 3L, 1L, 9L, 8L,
                          8L, 3L, 7L, 1L, 9L, 6L, 5L, 4L, 2L,
                          1L, 5L, 9L, 2L, 8L, 4L, 7L, 3L, 6L,
                          5L, 8L, 6L, 9L, 1L, 2L, 4L, 7L, 3L, 
                          9L, 2L, 4L, 7L, 3L, 8L, 6L, 5L, 1L,
                          3L, 7L, 1L, 4L, 6L, 5L, 2L, 8L, 9L), nrow = 9L, byrow = T)

# Ensure it's the same
if(!identical(solve_sudoku(sudoku_matrix = sudoku), as.sudoku(solved_sudoku))) {
  stop('the solution to data/sudoku.rda is not the same as is was!')
} else {
  print('solve_sudoku solved data/sudoku.rda')
}



