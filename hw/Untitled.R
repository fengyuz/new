
#include <Rcpp.h>
#include <iostream>
#include <algorithm>
using namespace Rcpp;
using namespace std;



void merge_sort(NumericVector x, int l, int r) {
    if( r -l > 1){
        int mid = int((l+r)/2);
        merge_sort(x, l, mid);
        merge_sort(x, mid, r);
        NumericVector y(mid - l);
        for(int a = 0; a<mid-l; a++){
            y[a] = x[a+l];
        }
        int nl = mid - l;
        int nr = r - mid;
        int i = 0, j = 0, k = l;
        while(i < nl && j < nr){
            if (y[i] <x[j + mid]){
                x[k] = y[i];
                i++;
            }
            else {
                x[k] = x[j + mid];
                j++;
            }
            k++;
        }
        while (i < nl && j == nr){
            x[k] = y[i];
            i++;
            k++;
        }
        while (j < nr && i == nl){
            x[k] = x[j + mid];
            j++;
            k++;
        }
    }
    
}

// [[Rcpp::export]]
NumericVector merge_sort(NumericVector x) {
    // Do not modify this function.
    // This function simply calls the merge_sort function above
    // that uses divide-and-conquer algorithm
    merge_sort(x, 0, (int)x.size());
    return x;
}
