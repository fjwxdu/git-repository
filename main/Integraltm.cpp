//Tm calculation

#include <iostream>
#include <math.h>

#include "../include/Integraltm.hpp"
#include "../include/Romberg.hpp"

const double pi=4.0*atan(1.0);
void Integraltm(int n,int m,double DataBeam[],double res[]){
	double s=DataBeam[2],X0=DataBeam[4],Y0=DataBeam[5],wavenumber0=DataBeam[1],z0=DataBeam[16];
	int l_order=DataBeam[9],p_order=DataBeam[10];
	double r0,Rloc,a1;
	r0=sqrt(X0*X0+Y0*Y0);
	Rloc=n+0.5;
	a1=2*s*s*wavenumber0*z0;
	
	int kmax=80,k,i,j;
	double lowlimit=0.0,uplimit=2.0*pi,length=uplimit-lowlimit,tmp[3];
	res[0]=res[1]=0.0;
	double step=(uplimit-lowlimit)/kmax;
	double IntFuncmax=0.0;
//	printf("%f\n",step);
	for(k=1;k<=kmax;k++){
		double a=lowlimit+(k-1)*step,b=lowlimit+k*step;
		int Int_ok=Romberg(n,m,a,b,DataBeam,tmp);
		for(j=0;j<=1;j++)
			res[j]+=tmp[j];
		if(IntFuncmax<tmp[2])
			IntFuncmax=tmp[2];
		if(IntFuncmax*1e-10>tmp[2])
			break;
	}
//	printf("%f\t%f\t",res[0],res[1]);
}
