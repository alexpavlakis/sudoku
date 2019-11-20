
<!-- badges: start -->
[![Travis build status](https://travis-ci.org/alexpavlakis/sudokuplyr.svg?branch=master)](https://travis-ci.org/alexpavlakis/sudokuplyr) <!-- badges: end -->

sudokuplyr
==========

The goal of sudokuplyr is to provide simple functions for solving, creating, and analyzing sudoku puzzles in R.

Installation
------------

You can install sudoku from github with:

``` r
# install.packages("devtools")
devtools::install_github("alexpavlakis/sudoku")
```

Examples
--------

The following methods are available for objects of class `sudoku`:

-   `print`
-   `plot`
-   `solve`
-   `summary`

For example, we can convert a 9x9 matrix, with `NA` for unknown cells, convert it into a `sudoku`, and print, plot, solve, and summarise it.

``` r
# Sudoku puzzle in matrix form, with NA for unknown values
sudoku
#>       [,1] [,2] [,3] [,4] [,5] [,6] [,7] [,8] [,9]
#>  [1,]    2    1   NA   NA   NA   NA   NA   NA   NA
#>  [2,]    4   NA    8   NA   NA    1   NA    2   NA
#>  [3,]   NA    6    5   NA    2   NA   NA   NA    4
#>  [4,]   NA   NA    2    5   NA    3   NA    9   NA
#>  [5,]    8   NA    7   NA   NA   NA    5   NA    2
#>  [6,]   NA    5   NA    2   NA    4    7   NA   NA
#>  [7,]    5   NA   NA   NA    1   NA    4    7   NA
#>  [8,]   NA    2   NA    7   NA   NA    6   NA    1
#>  [9,]   NA   NA   NA   NA   NA   NA   NA    8    9

# Convert to sudoku
s <- as.sudoku(sudoku)

# Print
print(s)
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
solve(s)
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

# Plot
plot(s)
```

<img src="man/figures/README-example-1.png" width="100%" />

``` r

# Summarize
summary(s)
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
#>  clues:           32 
#>  naked singles:   2 
#>  hidden singles:  18 
#>  legal solution:  TRUE 
#>  unique solution: TRUE
```

`solve_sudoku` can operate directly on the matrix. `solve_sudoku` first attempts to solve the sudoku with basic sudoku logic. If this doesn't work, a backtracking algorithm takes over to find a solution (if one exists). Core functions are written in C++ for speed. `solve_sudoku` completes puzzles in the blink of an eye. The example below shows the time taken to solve an easy puzzle (49 empty cells) and a hard puzzle (59 empty cells). The easy puzzle is solved in &lt;10 milliseconds and the hard puzzle is solved in a fraction of a second on a MacBook Air.

``` r
library(microbenchmark)
m <- microbenchmark(easy = solve_sudoku(sudoku),
                    hard = solve_sudoku(hard_sudoku), 
times = 100, unit = 's')
```

``` r
print(m, digits = 2)
#> Unit: seconds
#>  expr    min     lq   mean median     uq  max neval
#>  easy 0.0045 0.0049 0.0065 0.0055 0.0066 0.02   100
#>  hard 0.0079 0.0462 0.0714 0.0722 0.0967 0.15   100
```

`generate_sudoku` creates randomly generated complete sudoku puzzles. The `seed` argument can be used to create reproducible random puzzles or left `NULL` (default). `generate_puzzle` creates randomly generated incomplete sudoku puzzles with a specified number of clues.

``` r
new_puzzle <- generate_puzzle(clues = 32, unique = TRUE, seed = 56)
print(new_puzzle)
#>                           
#>  + - - - + - - - + - - - +
#>  | 4   6 | 7     | 3 9   |
#>  |       |       |   6 8 |
#>  | 5     |   9   |     7 |
#>  + - - - + - - - + - - - +
#>  | 3     |     6 | 9     |
#>  |     7 |   8   | 6     |
#>  |       | 5     |   8   |
#>  + - - - + - - - + - - - +
#>  | 8     | 2 3   | 1   9 |
#>  | 2 1   |     7 |   4   |
#>  |   7 4 |       | 2   3 |
#>  + - - - + - - - + - - - +
```

`get_all_solutions` generates all possible solutions for a given puzzle. Puzzles with fewer than 20-25 clues (depending on the puzzle, of course), can have *a lot* of solutions, and this function can take a while to find them all. Beware. Most puzzles that appear in newspapers and magazines have only one solution.

``` r
# This puzzle has a lot of solutions
puzzle <- generate_puzzle(clues = 28, unique = FALSE, seed = 56)
all_solutions <- get_all_solutions(puzzle)
length(all_solutions)
#> [1] 898
```

`analyze_sudoku` (or the `summary` method for objects of class `sudoku`) returns some helpful information about sudoku puzzles. Both the easy and hard sudokus that come with the package have legal, unique solutions; but the easy sudoku has more clues, "hidden singles", and "naked singles" (unknown cells that can be populated with simple logic).

``` r
# Compare the easy and hard sudokus that come with the package
analyze_sudoku(sudoku)
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
#>  clues:           32 
#>  naked singles:   2 
#>  hidden singles:  18 
#>  legal solution:  TRUE 
#>  unique solution: TRUE
analyze_sudoku(hard_sudoku)
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
#>  clues:           22 
#>  naked singles:   0 
#>  hidden singles:  3 
#>  legal solution:  TRUE 
#>  unique solution: TRUE
```
