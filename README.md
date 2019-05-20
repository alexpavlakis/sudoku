
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
#> [1] "A solution was found!"
print(solved_puzzle)
#>       [,1] [,2] [,3] [,4] [,5] [,6] [,7] [,8] [,9]
#>  [1,]    2    1    3    8    4    7    9    6    5
#>  [2,]    4    9    8    6    5    1    3    2    7
#>  [3,]    7    6    5    3    2    9    8    1    4
#>  [4,]    6    4    2    5    7    3    1    9    8
#>  [5,]    8    3    7    1    9    6    5    4    2
#>  [6,]    1    5    9    2    8    4    7    3    6
#>  [7,]    5    8    6    9    1    2    4    7    3
#>  [8,]    9    2    4    7    3    8    6    5    1
#>  [9,]    3    7    1    4    6    5    2    8    9

# Check that it is correct
check_integrity(solved_puzzle)
#> [1] TRUE
```

`solve_sudoku` completes puzzles in the blink of an eye. The example below shows the time taken to solve an easy puzzle (49 empty cells) and a hard puzzle (59 empty cells). The easy puzzle is solved in 20-30 milliseconds and the hard puzzle is solved in less than half a second.

``` r
# Easy puzzle - 49 empty cells
sum(is.na(sudoku))
#> [1] 49
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

# Hard Puzzle - 59 empty cells
sum(is.na(hard_sudoku))
#> [1] 59
print(hard_sudoku)
#>       V1 V2 V3 V4 V5 V6 V7 V8 V9
#>  [1,]  8  7 NA  5 NA NA NA NA  3
#>  [2,] NA NA NA NA NA  8 NA NA  7
#>  [3,] NA NA NA NA  4 NA NA NA NA
#>  [4,] NA NA  9 NA NA NA NA NA NA
#>  [5,] NA  8 NA  7 NA NA NA  1  6
#>  [6,] NA NA  2 NA  8  6 NA NA NA
#>  [7,]  2 NA NA NA NA NA NA NA NA
#>  [8,] NA  5 NA  1 NA NA  2  3 NA
#>  [9,] NA  9  6 NA NA NA NA NA NA
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
#>  expr    min     lq   mean median     uq    max neval
#>  easy 0.0203 0.0217 0.0252 0.0231 0.0262 0.0873   100
#>  hard 0.3904 0.4098 0.4567 0.4289 0.4703 0.7834   100
```
