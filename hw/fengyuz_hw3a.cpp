#include <Rcpp.h>
#include <map>
#include <algorithm>

using namespace Rcpp;
using namespace std;

///////////////////////////////////////
// Skeleton code for Homework 3A
///////////////////////////////////////

// function to calculate factorial
int fac(int n) {
    if ( n < 2 ) return 1; // return 1 when n=0,1
    int ret = 1;
    for(int i=2; i <= n; ++i)
        ret *= i;  // calculate factorial
    return ret;
}

// compute choose(n,k) using factorial
// [[Rcpp::export]]
int choose_fac(int n, int k) {
    return fac(n)/fac(k)/fac(n-k);
}

// compute choose(n,k) using dynamic programming
int func(int n, int k, map<pair<int,int>, int > &C){
    pair<int, int> nk(n,k);
    if (C.find(nk) == C.end() ){
        if(k == 0 || k == n){
            C[nk]= 1;
        }
        else{
            C[nk] = func(n-1, k, C) + func(n-1, k-1, C);
            }
        }
    return C[nk];
}
// [[Rcpp::export]]
int choose_dp(int n, int k) {
    ///////////////////////////////////////////////////
    // TODO: FILL IN THE BLANK to return choose_dp(n,k)
    // following the dynamic programming algorithm.
    // You may define an additional function.
    //////////////////////////////////////////////////
    map<pair<int,int>, int > C;
    return func(n,k,C);
}

