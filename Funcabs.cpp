//
// Created by fjwxdu on 1/14/2023 
// 
// Calculate the modulus of the complex number.
// Input:rez is the real part;imz is the imaginary part.
// Output:The modulus of the complex number.
//
#include <iostream>
#include <math.h>

#include "./include/Funcabs.hpp"

double Funcabs(double rez,double imz){
	if(rez<0.0) rez=-rez;
	if(imz<0.0) imz=-imz;
	if(rez>imz) return(rez*sqrt(1.0+pow(imz/rez,2)));
	else if(rez<imz) return(imz*sqrt(1.0+pow(rez/imz,2)));
	else return(rez*sqrt(2.0));
}
