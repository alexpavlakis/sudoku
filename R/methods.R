#' Convert a matrix to sudoku
#' 
#' @param x a 9x9 numeric matrix.
#' @param ... additional arguments.
#' @export
as.sudoku <- function(x, ...) structure(x, class = c('sudoku', 'matrix'))

#' Convert a sudoku to a matrix
#' 
#' @param x an object of class sudoku
#' @param ... additional arguments.
#' @export
as.matrix.sudoku <- function(x, ...) matrix(x, nrow = 9)


#' Print a sudoku puzzle
#' 
#' @param x an object of class sudoku.
#' @param ... additional arguments.
#' @export
print.sudoku <- function(x, ...) print_sudoku(x)

#' Summarize a sudoku puzzle
#' 
#' @param object an object of class sudoku.
#' @param ... additional arguments.
#' @export
summary.sudoku <- function(object, ...) analyze_sudoku(object)

#' Solve a sudoku.
#' 
#' @param a an object of class sudoku.
#' @param ... additional arguments.
#' @export
solve.sudoku <- function(a, ...) solve_sudoku(a)

#' Verify that a sudoku is a sudoku.
#' 
#' @param x an object of class sudoku.
#' @param ... additional arguments.
#' @export
is.sudoku <- function(x) inherits(x, "sudoku")

#' Plot a sudoku puzzle.
#' @importFrom graphics abline par plot text
#' @param x an object of class sudoku.
#' @param ... additional arguments.
#' @export
plot.sudoku <- function(x, ...) {
  locations <- data.frame(xcoord = rep(seq(0.5, 8.5, 1), 9),
                          ycoord = rep(seq(8.5, 0.5, -1), each = 9),
                          answer = c(x))
  par(mar = c(0, 0, 0, 0))
  plot(0:9, 0:9, col = 'white', xaxt = 'n', yaxt = 'n', yaxs = 'i', xaxs = 'i')
  abline(h = 0:9, v = 0:9, col = 'grey')
  abline(h = c(0, 3, 6, 9), v = c(0, 3, 6, 9), lwd = 2)
  text(locations$xcoord, locations$ycoord, locations$answer, cex = 2.5)
}

