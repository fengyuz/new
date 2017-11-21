#include <Rcpp.h>

using namespace std;
using namespace Rcpp;

// Do not forget to add documentation for your package using roxygen2


void viterbiLP(NumericMatrix& obs, NumericVector ts,
                 NumericMatrix& delta, IntegerMatrix& phi, double theta) {
    int m = (int)ts.size();
    double ns = (int)obs.nrow();
    NumericVector store(m);
    NumericVector index(m);
    fill(store.begin(), store.end(), -1);
    double sumd = 0;
    for(int i=0; i < ns; ++i){
        delta(i,0) = (1/ns)*obs(i, 0);
        sumd += delta(i,0);
        if (store[0] < delta(i,0)){
            store[0] = delta(i,0);
            index[0] = i;
            }
        }
    for (int i=0;i<ns;i++){
        delta(i,0) /= sumd;
    }
    index[0] /= sumd;
    for(int t=1; t < m; ++t) {
        for(int i=0; i < ns; ++i) {
            double trans1 = store[t-1]* 1/ns*(1-exp(-(ts[t]-ts[t-1])*theta));
            double trans2 = delta(i,t-1)*(1-(ns-1)/ns*(1-exp(-(ts[t]-ts[t-1])*theta)));
            if(trans1 < trans2){
                delta(i,t) = trans2;
                phi(i,t)=i;
                }
            else{ 
                delta(i,t) = trans1;
                phi(i,t) = index[t-1];
                }
            delta(i,t) *= obs(i, t);
            
            if (store[t] < delta(i,t)){
                store[t] = delta(i,t);
                index[t] = i;
                }
        }
        double sumd=0;
        for (int i=0;i<ns;i++){
            sumd+=delta(i,t);
        }
        for (int i=0;i<ns;i++){
            delta(i,t)/=sumd;
        }
        store[t]/=sumd;
    }
    
}



// [[Rcpp::export]]
IntegerVector ctmcViterbi(NumericVector ts, double theta, NumericMatrix obs) {
  int m = (int)ts.size();  
  int n = (int)obs.nrow();
  if ( obs.ncol() != m )
    stop("The input matrix does not conform to the other parameters");
  IntegerVector viterbiPath(m);
  NumericMatrix delta(n, m);
  IntegerMatrix phi(n, m);
  viterbiLP(obs, ts,delta, phi, theta);
  double ml = -1;
  for(int i=0; i < n; ++i) {
      if ( ml < delta(i,m-1) ) {
          ml = delta(i,m-1);
          viterbiPath[m-1] = i;
      }
  }
  for(int i=m-1; i > 0; --i) {
      viterbiPath[i-1] = phi(viterbiPath[i],i);
  }
  return viterbiPath;
}





// Do not forget to add documentation for your package using roxygen2


void forwardLoop(NumericVector ts, double theta, NumericMatrix obs, NumericMatrix& alpha) {
    int m = (int)ts.size();  
    double n = (double)obs.nrow();
    double sum =0;
    
    for(int i=0; i < n; ++i){ 
        alpha(i,0) = (1/n) * obs(i,0);
        sum+=alpha(i,0);
    }
    for(int i=0;i<n;i++)
        alpha(i,0)/=sum;
    for(int t=1;t<m;t++){
        for(int i=0;i<n;i++){
            alpha(i,t)=1/double(n)*(1-exp(-(ts[t]-ts[t-1])*theta)) +
                    alpha(i,t-1)*(1-(1-exp(-(ts[t]-ts[t-1])*theta)));
            alpha(i,t)*=obs(i,t);
        }
        sum=0;
        for(int i=0;i<n;i++){
            sum+=alpha(i,t);
        }
        for(int i=0;i<n;i++){
            alpha(i,t)/=sum;
        }
    }
}


void backwardLoop(NumericVector ts, double theta, NumericMatrix obs, NumericMatrix& beta) {
    int m = (int)ts.size();  
    double n = (double)obs.nrow();
    NumericMatrix store(n,m);
    double sumb=0;
    for(int i=0;i<n;i++){
        beta(i,m-1)=1;
        store(i,m-1)=obs(i,m-1);
        sumb+=beta(i,m-1);
    }
    for(int i=0;i<n;i++){
        beta(i,m-1)/=sumb;
        store(i,m-1)/=sumb;
    }
    
    for(int t=m-2; t >=0; --t) {
        double sum=0;
        for(int i=0;i<n;i++){
            sum += store(i,t+1);
        }
        sum *= 1/n*(1-exp(-(ts[t+1]-ts[t])*theta));
        for(int i=0;i<n;i++){
            beta(i,t)=sum + store(i,t+1)*(1-(1-exp(-(ts[t+1]-ts[t])*theta)));
            store(i,t)=beta(i,t)*obs(i,t);
        }
        double sumb=0;
        for(int i=0;i<n;i++){
            sumb+=beta(i,t);
        }
        for(int i=0;i<n;i++){
            beta(i,t)/=sumb;
            store(i,t)/=sumb;
        }
    }
}
// [[Rcpp::export]]
NumericMatrix ctmcForwardBackward(NumericVector ts, double theta, NumericMatrix obs) {
  int m = (int)ts.size();  
  int n = (int)obs.nrow();
  if ( obs.ncol() != m )
    stop("The input matrix does not conform to the other parameters");  
  NumericMatrix condProb(n,m);
  // TODO : Implement your function here
  NumericMatrix alpha(n, m);
  NumericMatrix beta(n, m);
  forwardLoop(ts, theta, obs, alpha);
  backwardLoop(ts, theta, obs, beta);
  for(int t=0; t < m; ++t) {
      double sum = 0;
      
      for(int i=0; i < n; ++i) 
          sum += ( alpha(i,t) * beta(i,t) );
      for(int i=0; i < n; ++i) 
          condProb(i,t) = alpha(i,t) * beta(i,t) / sum;
  }
  return condProb;

}



