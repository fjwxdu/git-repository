//
// Created by fjwxdu on 1/14/2023
//
// The factorial calculation
//

#include <iostream>

int factorial(double x){
    int i;
    int result=1;
    if(x<0)
        result=0;
    else
        for(i=1; i<=x; ++i)
            result *= i;
    return result;
}
