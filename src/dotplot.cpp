#include <Rcpp.h>
using namespace Rcpp;


//' Generate a dotplot matrix by comparing sequence 1 and sequence 2 using the
//' given window size and percent match
//'
//' @param seq1 The first sequence
//' @param seq2 The second sequence
//' @param wsize The window of the size to use
//' @param wstep the size in chars for the steps of the moving window. Use wstep == wsize for non-overlapping windows.
//' @param nmatch if the number of match per window is greater than or equal to nmatch then a dot is produced.
//' @return Returns a matrix
//' @export
// [[Rcpp::export]]
NumericMatrix mkDotPlotMatrix(std::string seq1, std::string seq2, int wsize, int wstep, int nmatch ) {

  // Check arguments:

  if(wsize < 1) stop("non allowed value for wsize");
  if(wstep < 1) stop("non allowed value for wstep");
  if(nmatch < 1) stop("non allowed value for nmatch");
  if(nmatch > wsize) stop("nmatch > wsize is not allowed");

  int s1l = seq1.length();
  int s2l = seq2.length();

  int xl = 1 +  (s1l - wsize) / wstep;
  int yl = 1 + (s2l - wsize) / wstep;

  NumericMatrix X(xl, yl);
  std::fill(X.begin(), X.end(), 1.0);
  // Brute force, inefficient with overlapping comparisons
  for(int i=0; i < (s1l - wsize); i += wstep) {
    for(int j=0; j < (s2l - wsize); j += wstep) {
      int nm =0;
      for(int k=0; k < wsize; k++) {
        if (seq1[i+k] == seq2[j+k]) nm++;
      }
      if (nm >= nmatch) {
        X(i, j) = 0.0;
      }
    }
  }
  return X;
}

//' Generate a dotplot matrix by comparing sequence 1 and sequence 2 using the
//' given window size and percent match
//'
//' @param seq1 The first sequence
//' @param seq2 The second sequence
//' @param wsize The window of the size to use
//' @param wstep the size in chars for the steps of the moving window. Use wstep == wsize for non-overlapping windows.
//' @param nmatch if the number of match per window is greater than or equal to nmatch then a dot is produced.
//' @return Returns a matrix
//' @export
// [[Rcpp::export]]
DataFrame mkDotPlotDataFrame(std::string seq1, std::string seq2, int wsize, int wstep, int nmatch ) {

  // Check arguments:

  if(wsize < 1) stop("non allowed value for wsize");
  if(wstep < 1) stop("non allowed value for wstep");
  if(nmatch < 1) stop("non allowed value for nmatch");
  if(nmatch > wsize) stop("nmatch > wsize is not allowed");

  int s1l = seq1.length();
  int s2l = seq2.length();

  std::vector<double> X;
  std::vector<double> Y;
  // Brute force, inefficient with overlapping comparisons
  for(int i=0; i < (s1l - wsize); i += wstep) {
    for(int j=0; j < (s2l - wsize); j += wstep) {
      int nm =0;
      for(int k=0; k < wsize; k++) {
        if (seq1[i+k] == seq2[j+k]) { nm++; }
      }
      if (nm >= nmatch) {
        X.push_back(static_cast<double>(i));
        Y.push_back(static_cast<double>(j));
      }
    }
  }
  Rcout << X.size();
  return DataFrame::create(_["x"] = X,
                           _["y"] = Y);
}

