#include <iostream>
#include <math.h>
#include <complex.h>
#include <string.h>
#include <stdio.h>

#include "../include/ReadDataBeam.hpp"
#include "../include/def.hpp"
#include "../include/Integraltm.hpp"

const double pi=4.0*atan(1.0);
int main(){
	
	double DataBeam[20];
	int OrderBeam[3];
	ReadDataBeam(DataBeam,OrderBeam);	
	
//	int *serm=(int*)malloc((nmaxBeam+5)*sizeof(int));
//	int *sersp=(int*)malloc((nmaxBeam+5)*sizeof(int));
//	double *VBSC=(double*)malloc(10*sizeof(double));
//	int BSCreadok=0;
	
//	double nref;
	double k=DataBeam[1];
	double x0=DataBeam[14],y0=DataBeam[15],w0=DataBeam[12],z0=DataBeam[16];
	double X0=DataBeam[4],Y0=DataBeam[5];
	double r0=sqrt(X0*X0+Y0*Y0),s=DataBeam[2];
	double kosai0,a1;
	int p_order=DataBeam[10],l_order=DataBeam[9],m,n;
	double Rloc;
	_Complex double fact_tm;
	_Complex double Unm;
	
	char fid1[100],fid2[100],fid3[100];
	strcpy(fid1,"Anm.txt");
	strcpy(fid2,"Bnm.txt");
	strcpy(fid3,"Module.csv");
	
	FILE *fp1,*fp2,*fp3;
	fp1=fopen(fid1,"w"),fp2=fopen(fid2,"w"),fp3=fopen(fid3,"w");
	
	kosai0=atan2(y0,x0);		//rad

	a1=2.0*pow(s,2)*k*z0;
	fact_tm=(-1/(2*pi))*cpow(1+I*a1,p_order)/cpow(1-I*a1,(l_order+p_order+1));	//fact of Tm
	int nbg=40;
	double res1[2],res2[2];
	_Complex double Anm[82][41],Bnm[82][41];
	_Complex double tm1,tm2,Tm1,Tm2;
	m=0; 
	double moduleA;
	for(n=1;n<=200;n++){
		Rloc=n+0.5;				//correction factor
		Unm=cpow(I,1-m)*pow(Rloc,0.5-abs(m))*sqrt(def(n+abs(m),n-abs(m)));
		Integraltm(n,m-1,DataBeam,res1);
		Integraltm(n,m+1,DataBeam,res2);
		tm1=res1[0]+I*res1[1];
		tm2=res2[0]+I*res2[1];
		Tm1=fact_tm*tm1;
		Tm2=fact_tm*tm2;
		Anm[m+nbg+1][n]=Unm*cexp(-1*I*k*z0)*(cexp(-1*I*(m-l_order-1)*kosai0)*Tm1+cexp(-1*I*(m-l_order+1)*kosai0)*Tm2);
		Bnm[m+nbg+1][n]=Unm*cexp(-1*I*k*z0)*(cexp(-1*I*(m-l_order-1)*kosai0)*Tm1-cexp(-1*I*(m-l_order+1)*kosai0)*Tm2)/I;
		fprintf(fp1,"%d\t%d\t%e\t%e\n",n,m,creal(Anm[m+nbg+1][n]),cimag(Anm[m+nbg+1][n]));
		fprintf(fp2,"%d\t%d\t%e\t%e\n",n,m,creal(Bnm[m+nbg+1][n]),cimag(Bnm[m+nbg+1][n]));
		moduleA=sqrt(creal(Anm[m+nbg+1][n])*creal(Anm[m+nbg+1][n])+cimag(Anm[m+nbg+1][n])*cimag(Anm[m+nbg+1][n]));
		
		fprintf(fp3,"%e\n",moduleA);
		
		printf("%d\t%d\t%e\t%e\t%e\t%e\n",n,m,creal(Anm[m+nbg+1][n]),cimag(Anm[m+nbg+1][n]),creal(Bnm[m+nbg+1][n]),cimag(Bnm[m+nbg+1][n]));
		printf("%e\n",moduleA);
	}
	return 0;
}
