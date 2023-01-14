//L(l,p)
include <iostream>
include <math.h>

include "./include/Laguerre.hpp"
include "./include/factorial.hpp"

double Laguerre(double l_order,double p_order,double x){
    double tmp=0.0;
    int m;
    for(m=0;m<=p_order;m++)
        tmp=tmp+pow(-1.0,m)*factorial(l_order+p_order)*pow(x,m)/(factorial(p_order-m)*factorial(l_order+m)*factorial(m));
    return tmp;
}
