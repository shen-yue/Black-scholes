
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;
enum OptionType{Call,Put};

 double cnorm(double x)
 {
 // constants
 double a1 =  0.254829592;
 double a2 = -0.284496736;
 double a3 =  1.421413741;
 double a4 = -1.453152027;
 double a5 =  1.061405429;
 double p  =  0.3275911;
 int sign = 1;
 if (x < 0)
 sign = -1;
 x = fabs(x)/sqrt(2.0);
 double t = 1.0/(1.0 + p*x);
 double y = 1.0 - (((((a5*t + a4)*t) + a3)*t + a2)*t + a1)*t*exp(-x*x);
 return 0.5*(1.0 + sign*y);
 }

double BsPricer(OptionType opType, double S0, double K, double r, double t, double sigma){
    double sigmaSqrt = sigma * sqrt(t);
    double d1 = (log(S0/K)+r*t)/sigmaSqrt+0.5*sigmaSqrt;
    double d2 = (log(S0/K)+r*t)/sigmaSqrt - 0.5*sigmaSqrt;
    double price;
    switch (opType){
        case Call:
            price=S0* cnorm(d1)-K*exp(-r*t)*cnorm(d2);
            break;
        case Put:
            price=K*exp(-r*t)*cnorm(-d2)-S0*cnorm(-d1);
            break;
        default:
            throw "unsupported option type";
    }
    return price;
}

int main(){
    OptionType opType;
    double S0,K,r,t,sigma;
    double V0;
    opType=Call;
    S0=95;
    K=100;
    r=0.02;
    t=3;
    sigma=0.25;
    V0 = BsPricer(opType,S0,K,r,t,sigma);
    cout<<V0<<endl;
    return 0;
}
