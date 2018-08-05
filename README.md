# sudoku

The goal of sudoku is to provide simple functions for solving most sudoku puzzles.

## Installation

You can install sudoku from github with:


``` r
# install.packages("devtools")
devtools::install_github("alexpavlakis/sudoku")
```

## Example

The workhorse function is `solve_sudoku`, which takes three arguments:

* `sudoku_matrix`: an unsolved sudoku puzzle in matrix form, with `NA` in unknown cells;
* `verbose`: `TRUE` if you want the function to print intermediate steps (defaults to `FALSE`); and
* `attempts`: the number of educted guesses the program should make if it is unable to find a solution logically.  Defaults to 50.

`check_integrity` will tell you if a puzzle is completed correctly.

``` r
solved_puzzle <- solve_sudoku(sudoku)
check_integrity(solved_puzzle)
```
