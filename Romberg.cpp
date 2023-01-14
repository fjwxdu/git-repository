// Romberg integral

#include <iostream>
#include <math.h>

#include "./include/Romberg.hpp"
#include "./include/Integraltm0.hpp"
#include "./include/Funcabs.hpp"

int Romberg(int n,int m,double a,double b,double DataBeam[],double res[]){
	double s=DataBeam[2],X0=DataBeam[4],Y0=DataBeam[5],wavenumber0=DataBeam[1],z0=DataBeam[16];
	int l_order=DataBeam[9],p_order=DataBeam[10];
	double r0,Rloc,a1;
	r0=sqrt(X0*X0+Y0*Y0);
	Rloc=n+0.5;
	a1=2*s*s*wavenumber0*z0;	
	
	double h=b-a;					// integral range
	const double eps=1e-5;
	const int maxk=10;
	int i,j,k,ep;
	double res1[3],res2[3],R[maxk+2][2],RZ[2],Rp[2],cum[2];
	
//	fun(a,res1);
//	fun(b,res1);
	Integraltm0(a,n,m,DataBeam,res1);
	Integraltm0(a,n,m,DataBeam,res2);
	
	res[2]=(res1[2]<res2[2])? res2[2]:res1[2]; 
	
	for(i=0;i<=1;i++)
		R[0][i]=h*0.5*(res1[i]+res2[i]);
	double tmold,tmnew=Funcabs(R[0][0],R[0][1]);
	
	for(k=1;k<=maxk;k++){
		h*=0.5,ep=1<<(k-1);
		for(i=0;i<=1;i++)
			cum[i]=0.0;
			
		  for(j=1;j<=ep;j++){
//			fun(a+(2*j-1)*h,res1);
        Integraltm0(a+(2*j-1)*h,n,m,DataBeam,res1);
        if(res[2]<res1[2])
          res[2]=res1[2];
        for(i=0;i<=1;i++)
          cum[i]+=res1[i];
		  }
      for(i=0;i<=1;i++){
        RZ[i]=R[0][i];
        R[0][i]=h*cum[i]+0.5*RZ[i];
      }
      for(j=1;j<=k;j++){
          for(i=0;i<=1;i++){
            Rp[i]=R[j-1][i]+(R[j-1][i]-RZ[i])/(pow(4,j)-1);
            RZ[i]=R[j][i];
            R[j][i]=Rp[i];
          }
      }
      tmold=tmnew;
      tmnew=Funcabs(R[k][0],R[k][1]);
      if(k>4 && (fabs(tmold-tmnew)<=eps*tmnew || tmnew<1e-300)){
          for(i=0;i<=1;i++)
          res[i]=R[k][i];
  //		  	printf("%f\t%f\n",res[0],res[1]);
        return 1;
      }
	}
	for(i=0;i<=1;i++)
		res[i]=R[maxk][i];
//	printf("%f\t%f\t%f\t%f\t%f\t%f\n",res1[0],res1[1],res1[2],res2[0],res2[1],res2[2]);
//	printf("%f\t%f\n",res[0],res[1]);
	return 0;
}
