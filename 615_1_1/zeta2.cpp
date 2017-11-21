#include <Rcpp.h>
// [[Rcpp::export]]
double zeta2(int n) {
  double sum = 0;
  for(int i=n; i > 0; --i)
    sum += 1.0/i/i;
  return sum;
}
