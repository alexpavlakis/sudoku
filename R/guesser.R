#' Intermediate functions
#'
#' These functions help the sudoku solver solve puzzles!

#' @export

guesser <- function(attempt, verbose,
                    attempts) {
  attempt2 <- attempt
  counter <- 0
  
  while(!check_integrity(attempt2) && counter < attempts) {
    cant_bes <- cant_bes_getter(sudoku_df = attempt)
    length_cant_bes <- unlist(lapply(cant_bes, length))
    
    guess_index <- sample(which(length_cant_bes == max(length_cant_bes)), size = 1)
    attempt_rando <- attempt
    attempt_rando$value[guess_index] <- sample(c(1:9)[!c(1:9) %in% cant_bes[[guess_index]]],
                                               size = 1)
    
    attempt2 <- logical_solver(sudoku_df = attempt_rando,
                               verbose = verbose)
    counter <- counter + 1
  }
  return(attempt2)
}




