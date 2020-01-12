#' Convert a matrix, vector, or string to a sudoku.  Strings should be in the form "2..4.." etc, and have 81 characters
#' 
#' @param x object to be converted to a sudoku
#' @param ... additional arguments.
#' @export
as.sudoku <- function(x, ...) UseMethod("as.sudoku")

#' @export
as.sudoku.matrix <- function(x, ...) {
  if(nrow(x) != 9 | ncol(x) != 9) stop('matrix must be 9x9 to convert to sudoku')
  structure(x, class = c('sudoku', 'matrix'))
}


as_sudoku_chr <- function(x, ...) {
  s <- strsplit(x, "")[[1]]
  s[s == "."] <- NA
  s[s == 0] <- NA
  s <- as.integer(s)
  if(length(s) != 81) stop('sudoku must contain 81 elements')
  as.sudoku(matrix(s, nrow = 9))
}


#' @export
as.sudoku.default <- function(x, ...) {
  tryCatch({
    if(is.vector(x)) {
      if(is.character(x)) {
        as_sudoku_chr(x)
      } else if(is.numeric(x)) {
        as.sudoku(matrix(x, nrow = 9))
      }
    }
  }, error = function(e) print(e))
}



#' Print a sudoku puzzle
#' 
#' @param x an object of class sudoku.
#' @param ... additional arguments.
#' @export
print_sudoku <- function(x, ...) {
  sdf <- cbind(x, cbind(matrix(rep(rep(NA, 9), 4), ncol = 4)))[,c(10,1:3,11,4:6,12,7:9,13)]
  sdf <- rbind(sdf, rbind(matrix(rep(rep(NA, 13), 4), nrow = 4)))[c(10,1:3,11,4:6,12,7:9,13),]
  sdf <- apply(sdf, 2, function(x) ifelse(is.na(x), '', x))
  out <- matrix('', 13, 13)
  for(i in 1:13) {
    for(j in 1:13) {
      if(i %in% c(1, 5, 9, 13) & j %in% c(1, 5, 9, 13)) {
        out[i, j] <- '+'
      } else if(i %in% c(1, 5, 9, 13)) {
        out[i, j] <- '-'
      } else if(j %in% c(1, 5, 9, 13)) {
        out[i, j] <- '|'
      } else {
        out[i, j] <- sdf[i, j] 
      }
    }
  }
  dimnames(out) <- list(rep('', 13), rep('', 13))
  print(out, quote = F)
}

#' @export
print.sudoku <- function(x, ...) print_sudoku(x, ...)

#' Summarize a sudoku puzzle
#' 
#' @param object an object of class sudoku.
#' @param ... additional arguments.
#' @export
summary.sudoku <- function(object, ...) analyze_sudoku(object, ...)

#' Solve a sudoku.
#' 
#' @param a an object of class sudoku.
#' @param ... additional arguments.
#' @export
solve.sudoku <- function(a, ...) solve_sudoku(a, ...)

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
plot_sudoku <- function(x, ...) {
  locations <- data.frame(xcoord = rep(seq(8.5, 0.5, -1), each = 9),
                          ycoord = rep(seq(0.5, 8.5, 1), 9),
                          answer = rev(c(x)))
  par(mar = c(2, 2, 2, 2))
  plot(0:9, 0:9, col = 'white', xaxt = 'n', yaxt = 'n', yaxs = 'i', xaxs = 'i')
  abline(h = 0:9, v = 0:9, col = 'grey')
  abline(h = c(0, 3, 6, 9), v = c(0, 3, 6, 9), lwd = 2)
  text(locations$xcoord, locations$ycoord, locations$answer, cex = 2)
  par(mar = c(5.1, 4.1, 4.1, 2.1))
}

#' @export
plot.sudoku <- function(x, ...) plot_sudoku(x, ...)
