// integrand

#include <iostream>
#include <math.h>
#include <complex.h>

#include "./include/Integraltm0.hpp"
#include "./include/Funcabs.hpp"
#include "./include/Laguerre.hpp"

void Integraltm0(double gamma,int n,int m,double DataBeam[],double res[]){
	double s=DataBeam[2],X0=DataBeam[4],Y0=DataBeam[5],wavenumber0=DataBeam[1],z0=DataBeam[16];
	int l_order=DataBeam[9],p_order=DataBeam[10];
	double r0,Rloc,a1;
	r0=sqrt(X0*X0+Y0*Y0);
	Rloc=n+0.5;
	a1=2*s*s*wavenumber0*z0;
	
	double w1=sqrt(pow(Rloc,2)+pow(r0,2)-2*Rloc*r0*cos(gamma));
	double kappa=asin(r0*sin(gamma)/w1);
	double fa=2*pow(w1*s,2)/(1+pow(a1,2));
	_Complex double fun=cexp(I*l_order*kappa+I*(l_order-m)*gamma-(pow(w1*s,2)/(1-I*a1)))*pow(sqrt(2)*w1*s,l_order)*Laguerre(l_order,p_order,fa);
	res[0]=creal(fun);
	res[1]=cimag(fun);
	res[2]=Funcabs(res[0],res[1]);
}
