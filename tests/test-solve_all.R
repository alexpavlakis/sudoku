library(sudokuplyr)

# Create a sudoku with 15 solutions
puzzle <- matrix(c(4L, NA, 6L, NA, NA, NA, NA, 9L, 2L,
                   NA, NA, 1L, NA, NA, 2L, NA, NA, NA,
                   5L, 3L, 2L, 6L, NA, NA, NA, NA, 7L,
                   NA, NA, 8L, NA, 7L, 6L, 9L, NA, NA, 
                   NA, NA, NA, 4L, 8L, 9L, NA, NA, NA,
                   NA, 4L, NA, 5L, 2L, 3L, NA, NA, NA,
                   NA, NA, NA, 2L, NA, NA, NA, NA, 9L,
                   2L, NA, NA, NA, NA, NA, NA, 4L, 6L,
                   9L, NA, 4L, NA, NA, NA, 2L, 5L, 3L), nrow = 9, byrow = T)

# Get all solutions
all_solutions <- get_all_solutions(puzzle)

# Check that it found all 15 solutions
if(length(all_solutions) == 15 & all(unlist(lapply(all_solutions, is_legal)))) {
  print('get_all_solutions found all 15 solutions to puzzle')
} else {
  stop('get_all_solutions did not find all 15 solutions to puzzle')
}

# Check that is_unique identifies it as a puzzle without a unique solution
if(!is_unique(puzzle)) { 
  print('is_unique correctly identified that puzzle does not have a unique solution')
} else {
  stop('is_unique did not correctly identify that puzzle does not have a unique solution')
}
