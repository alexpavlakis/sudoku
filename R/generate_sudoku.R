generate_sudoku <- function(seed = NULL) {
  mat <- matrix(NA, nrow = 9, ncol = 9)
  if(!is.null(seed)) {
    set.seed(seed)
  }
  mat[sample(1:9, size = 1), sample(1:9, size = 1)] <- sample(1:9, size = 1)
  solve_sudoku(mat, shuffle = TRUE)
}

generate_puzzle <- function(empties = 56, seed = NULL, unique = FALSE) {
  full_puzzle <- generate_sudoku(seed = seed)
  
  out <- full_puzzle
  not_the_same <- TRUE
  while(not_the_same) {
    
    out <- full_puzzle
    # Random pattern symmetrical
    fill <- c(rep(NA, empties), rep(0, 81-empties))
    fill <- fill[sample(1:81)]
    om <- matrix(fill, nrow = 9)
    om[lower.tri(om)] <- t(om)[lower.tri(om)]
    
    for(i in 1:9) {
      for(j in 1:9) {
        if(is.na(om[i, j]))
          out[i, j] <- NA
      }
    }
    if(unique) {
      not_the_same <- !identical(full_puzzle, solve_sudoku(out, shuffle = T))
    } else {
      not_the_same <- FALSE
    }
    print(not_the_same)
  } 
  out
}



#puz <- generate_puzzle(59, unique = T)
#print_sudoku(puz)
#solve_sudoku(puz)
