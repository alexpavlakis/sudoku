library(sudoku)

# Make sure the time taken to solve hard_sudoku (which requires backtracking) is reasonable.
# It should be < 0.5 seconds and definitely not more than 5 seconds...

start <- Sys.time()
res <- solve_sudoku(hard_sudoku)
end <- Sys.time()

if(end - start > 5) {
  stop('solve_sudoku took longer than 5 seconds to solve data/hard_sudoku.rda')
} else {
  print(paste('solve_sudoku took', round(end-start, 1), 'seconds to solve data/hard_sudoku.rda'))
}
