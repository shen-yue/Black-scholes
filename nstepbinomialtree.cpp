//
//  nstepbinomialtree.cpp
//  Third
//
//  Created by 沈越 on 28/07/19.
//  Copyright © 2019年 沈越. All rights reserved.
//

#include <cmath>
#include <vector>
#include <iostream>

enum OptionType{Call, Put};
using namespace std;

double payoff(OptionType opType,double S, double K){
    double payprice;
    switch (opType) {
        case Call:
            payprice = S>K? (S-K):0;
            break;
        case Put:
            payprice = S<K? (K-S):0;
            break;
        default:
            throw "unsupported option type";
    }
    return payprice;
}

double nBinomialTree(OptionType opType,int N,double S0, double K, double r, double T, double sigma){
    double t=T/N;
    double erDt= exp(r*t);
    double erDtsigma = exp((2*r+sigma*sigma)*t);
    double u=(erDtsigma +1+sqrt((erDtsigma+1)*(erDtsigma+1)-4*erDt*erDt))/(2*erDt);
    double d=1/u;
    double p=(exp(r*t)-d)/(u-d);
    vector<double> endstates(N+1);
    double endprice;
    for (int i=0;i<=N;i++){
        endprice = S0*pow(u,N-i)*pow(d,i);
        endstates[i] = payoff(opType,endprice,K);
    }
    for (int step=N-1;step>=0;step--){
        for (int i=0; i<=step;i++){
            endstates[i]=p*endstates[i] + (1-p)*endstates[i+1];
        }
    }
    return exp(-r*T)*endstates[0];
}

int main(){
    cout<<nBinomialTree(Call,40,95,100,0.02,3,0.25)<<endl;
}
