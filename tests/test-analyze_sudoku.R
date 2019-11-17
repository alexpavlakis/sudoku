library(sudokuplyr)

# Make sure that analyze_sudoku gets things right
analyzed_sudoku <- analyze_sudoku(sudoku)

if(analyzed_sudoku$clues != 32 | !analyzed_sudoku$legal_solution | !analyzed_sudoku$unique) {
  stop('analyze sudoku did not properly analyze sudoku')
} else {
  print('analyze sudoku is working as expected')
}
