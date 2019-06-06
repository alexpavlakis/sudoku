
<!-- README.md is generated from README.Rmd. Please edit that file -->
sudoku
======

The goal of sudoku is to provide simple functions for solving sudoku puzzles in R.

Installation
------------

You can install sudoku from github with:

``` r
# install.packages("devtools")
devtools::install_github("alexpavlakis/sudoku")
```

Example
-------

The workhorse function is `solve_sudoku`, which takes two arguments:

-   `sudoku_matrix`: an unsolved sudoku puzzle in matrix form, with `NA` in unknown cells;
-   `verbose`: `TRUE` if you want the function to print intermediate steps (defaults to `FALSE`)

`check_integrity` will tell you if a puzzle is completed correctly.

solve sudoku first attempts to solve the sudoku with basic sudoku logic. If this does not work, it uses a backtracking algorithm to find a solution (if one exists). Core functions (such as backtracking) are written in C++ for speed.

``` r
# An unsolved puzzle
print_sudoku(sudoku)
#>                           
#>  + - - - + - - - + - - - +
#>  | 2 1   |       |       |
#>  | 4   8 |     1 |   2   |
#>  |   6 5 |   2   |     4 |
#>  + - - - + - - - + - - - +
#>  |     2 | 5   3 |   9   |
#>  | 8   7 |       | 5   2 |
#>  |   5   | 2   4 | 7     |
#>  + - - - + - - - + - - - +
#>  | 5     |   1   | 4 7   |
#>  |   2   | 7     | 6   1 |
#>  |       |       |   8 9 |
#>  + - - - + - - - + - - - +

# Solve
solved_puzzle <- solve_sudoku(sudoku)
print_sudoku(solved_puzzle)
#>                           
#>  + - - - + - - - + - - - +
#>  | 2 1 3 | 8 4 7 | 9 6 5 |
#>  | 4 9 8 | 6 5 1 | 3 2 7 |
#>  | 7 6 5 | 3 2 9 | 8 1 4 |
#>  + - - - + - - - + - - - +
#>  | 6 4 2 | 5 7 3 | 1 9 8 |
#>  | 8 3 7 | 1 9 6 | 5 4 2 |
#>  | 1 5 9 | 2 8 4 | 7 3 6 |
#>  + - - - + - - - + - - - +
#>  | 5 8 6 | 9 1 2 | 4 7 3 |
#>  | 9 2 4 | 7 3 8 | 6 5 1 |
#>  | 3 7 1 | 4 6 5 | 2 8 9 |
#>  + - - - + - - - + - - - +

# Check that it is correct
check_integrity(solved_puzzle)
#> [1] TRUE
```

`solve_sudoku` completes puzzles in the blink of an eye. The example below shows the time taken to solve an easy puzzle (49 empty cells) and a hard puzzle (59 empty cells). The easy puzzle is solved in &lt;20 milliseconds and the hard puzzle is solved in a fraction of a second on a MacBook Air.

``` r
# Easy puzzle - 49 empty cells
sum(is.na(sudoku))
#> [1] 49
print_sudoku(sudoku)
#>                           
#>  + - - - + - - - + - - - +
#>  | 2 1   |       |       |
#>  | 4   8 |     1 |   2   |
#>  |   6 5 |   2   |     4 |
#>  + - - - + - - - + - - - +
#>  |     2 | 5   3 |   9   |
#>  | 8   7 |       | 5   2 |
#>  |   5   | 2   4 | 7     |
#>  + - - - + - - - + - - - +
#>  | 5     |   1   | 4 7   |
#>  |   2   | 7     | 6   1 |
#>  |       |       |   8 9 |
#>  + - - - + - - - + - - - +

# Hard Puzzle - 59 empty cells
sum(is.na(hard_sudoku))
#> [1] 59
print_sudoku(hard_sudoku)
#>                           
#>  + - - - + - - - + - - - +
#>  | 8 7   | 5     |     3 |
#>  |       |     8 |     7 |
#>  |       |   4   |       |
#>  + - - - + - - - + - - - +
#>  |     9 |       |       |
#>  |   8   | 7     |   1 6 |
#>  |     2 |   8 6 |       |
#>  + - - - + - - - + - - - +
#>  | 2     |       |       |
#>  |   5   | 1     | 2 3   |
#>  |   9 6 |       |       |
#>  + - - - + - - - + - - - +
```

``` r
library(microbenchmark)
m <- microbenchmark(easy = solve_sudoku(sudoku),
                    hard = solve_sudoku(hard_sudoku), 
                    times = 100, unit = 's')
```

``` r
print(m, digits = 3)
#> Unit: seconds
#>  expr     min      lq    mean  median      uq   max neval cld
#>  easy 0.00723 0.00756 0.00979 0.00781 0.00825 0.140   100  a 
#>  hard 0.12118 0.12565 0.12791 0.12717 0.12954 0.149   100   b
```
