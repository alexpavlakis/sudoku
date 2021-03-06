% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/sudoku-solver.R
\name{get_all_solutions}
\alias{get_all_solutions}
\title{Sudoku solver - all solutions}
\usage{
get_all_solutions(sudoku_matrix, stop_early = FALSE, ...)
}
\arguments{
\item{sudoku_matrix}{an unsolved sudoku, in matrix form, with NA values for empty cells}

\item{stop_early}{set to TRUE if you want to stop once you've found one solution, false if you want to return all solutions.  Defaults to TRUE  For puzzles with few clues (fewer than 25), attempting to return all solutions can take a long time.}

\item{...}{additional arguments to pass to solver.}
}
\description{
This function can return all legal solutions to an unsolved puzzle
}
\examples{
random_puzzle <- generate_puzzle(seed = 56, clues = 30)
all_solutions <- get_all_solutions(random_puzzle)
length(all_solutions)
}
