// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// not_in_row_c
IntegerVector not_in_row_c(IntegerMatrix sudoku_df, int row);
RcppExport SEXP _sudoku_not_in_row_c(SEXP sudoku_dfSEXP, SEXP rowSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    Rcpp::traits::input_parameter< int >::type row(rowSEXP);
    rcpp_result_gen = Rcpp::wrap(not_in_row_c(sudoku_df, row));
    return rcpp_result_gen;
END_RCPP
}
// not_in_col_c
IntegerVector not_in_col_c(IntegerMatrix sudoku_df, int col);
RcppExport SEXP _sudoku_not_in_col_c(SEXP sudoku_dfSEXP, SEXP colSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    Rcpp::traits::input_parameter< int >::type col(colSEXP);
    rcpp_result_gen = Rcpp::wrap(not_in_col_c(sudoku_df, col));
    return rcpp_result_gen;
END_RCPP
}
// not_in_box_c
IntegerVector not_in_box_c(IntegerMatrix sudoku_df, int box);
RcppExport SEXP _sudoku_not_in_box_c(SEXP sudoku_dfSEXP, SEXP boxSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    Rcpp::traits::input_parameter< int >::type box(boxSEXP);
    rcpp_result_gen = Rcpp::wrap(not_in_box_c(sudoku_df, box));
    return rcpp_result_gen;
END_RCPP
}
// can_bes_getter_index_c
IntegerVector can_bes_getter_index_c(IntegerMatrix sudoku_df, int index);
RcppExport SEXP _sudoku_can_bes_getter_index_c(SEXP sudoku_dfSEXP, SEXP indexSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    Rcpp::traits::input_parameter< int >::type index(indexSEXP);
    rcpp_result_gen = Rcpp::wrap(can_bes_getter_index_c(sudoku_df, index));
    return rcpp_result_gen;
END_RCPP
}
// cant_bes_getter_c
List cant_bes_getter_c(IntegerMatrix sudoku_df);
RcppExport SEXP _sudoku_cant_bes_getter_c(SEXP sudoku_dfSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    rcpp_result_gen = Rcpp::wrap(cant_bes_getter_c(sudoku_df));
    return rcpp_result_gen;
END_RCPP
}
// solve_backtracking_c
bool solve_backtracking_c(IntegerMatrix sudoku_df, IntegerVector empties);
RcppExport SEXP _sudoku_solve_backtracking_c(SEXP sudoku_dfSEXP, SEXP emptiesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    Rcpp::traits::input_parameter< IntegerVector >::type empties(emptiesSEXP);
    rcpp_result_gen = Rcpp::wrap(solve_backtracking_c(sudoku_df, empties));
    return rcpp_result_gen;
END_RCPP
}
// check_integrity_c
bool check_integrity_c(IntegerMatrix sudoku_df);
RcppExport SEXP _sudoku_check_integrity_c(SEXP sudoku_dfSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    rcpp_result_gen = Rcpp::wrap(check_integrity_c(sudoku_df));
    return rcpp_result_gen;
END_RCPP
}
// cant_bes_lengths_c
IntegerMatrix cant_bes_lengths_c(IntegerMatrix sudoku_df, List cant_bes);
RcppExport SEXP _sudoku_cant_bes_lengths_c(SEXP sudoku_dfSEXP, SEXP cant_besSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< IntegerMatrix >::type sudoku_df(sudoku_dfSEXP);
    Rcpp::traits::input_parameter< List >::type cant_bes(cant_besSEXP);
    rcpp_result_gen = Rcpp::wrap(cant_bes_lengths_c(sudoku_df, cant_bes));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_sudoku_not_in_row_c", (DL_FUNC) &_sudoku_not_in_row_c, 2},
    {"_sudoku_not_in_col_c", (DL_FUNC) &_sudoku_not_in_col_c, 2},
    {"_sudoku_not_in_box_c", (DL_FUNC) &_sudoku_not_in_box_c, 2},
    {"_sudoku_can_bes_getter_index_c", (DL_FUNC) &_sudoku_can_bes_getter_index_c, 2},
    {"_sudoku_cant_bes_getter_c", (DL_FUNC) &_sudoku_cant_bes_getter_c, 1},
    {"_sudoku_solve_backtracking_c", (DL_FUNC) &_sudoku_solve_backtracking_c, 2},
    {"_sudoku_check_integrity_c", (DL_FUNC) &_sudoku_check_integrity_c, 1},
    {"_sudoku_cant_bes_lengths_c", (DL_FUNC) &_sudoku_cant_bes_lengths_c, 2},
    {NULL, NULL, 0}
};

RcppExport void R_init_sudoku(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
