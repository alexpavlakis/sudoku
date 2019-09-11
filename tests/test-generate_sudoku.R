library(sudoku)

# Test that the generator produces correct puzzles
integrity <- is_legal(generate_sudoku())

if(!integrity) {
  stop('generate_sudoku created a bad puzzle.')
} else {
  print('generate_sudoku created a good puzzle.')
}

# Test that the seed produces identical puzzles
the_same <- identical(generate_sudoku(seed = 56), generate_sudoku(seed = 56))

if(!the_same) {
  stop('generate_sudoku(seed = 56) created two different puzzles.')
} else {
  print('generate_sudoku(seed = 56) created two identical puzzles.')
}
