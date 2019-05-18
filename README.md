
<!-- README.md is generated from README.Rmd. Please edit that file -->
sudoku
======

The goal of sudoku is to provide simple functions for solving most sudoku puzzles.

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

solve sudoku first attempts to solve the sudoku with basic sudoku logic. If this does not work, it uses a backtracking algorithm to find a solution (if one exists).

``` r
# An unsolved puzzle
print(sudoku)
#>       V1 V2 V3 V4 V5 V6 V7 V8 V9
#>  [1,]  2  1 NA NA NA NA NA NA NA
#>  [2,]  4 NA  8 NA NA  1 NA  2 NA
#>  [3,] NA  6  5 NA  2 NA NA NA  4
#>  [4,] NA NA  2  5 NA  3 NA  9 NA
#>  [5,]  8 NA  7 NA NA NA  5 NA  2
#>  [6,] NA  5 NA  2 NA  4  7 NA NA
#>  [7,]  5 NA NA NA  1 NA  4  7 NA
#>  [8,] NA  2 NA  7 NA NA  6 NA  1
#>  [9,] NA NA NA NA NA NA NA  8  9

# Solve
solved_puzzle <- solve_sudoku(sudoku)
#> [1] "A solution is found!"

# Check that it is correct
check_integrity(solved_puzzle)
#> [1] FALSE
```
