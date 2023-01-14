// Read beam information

#include <iostream>
#include <math.h>
#include <stdio.h>

#include "../include/ReadDataBeam.hpp"

const double pi=4.0*atan(1.0);
int ReadDataBeam(double DataBeam[],int OrderBeam[])
{
	double w0x,w0y,wavel0,x0,y0,z0;
	double l_order,p_order;
	FILE *fp;
	fp=fopen("../DataBeam/Parameters of incident beam.txt","r");
	fscanf(fp,"%lf\t%lf\t\t%lf\n",&w0x,&w0y,&wavel0);
	fscanf(fp,"%lf\t%lf\t%lf\n",&x0,&y0,&z0);
	fscanf(fp,"%lf\t%lf\n",&l_order,&p_order);
	fclose(fp);
//	***************************************************************************************
	double wavenumber0=2.0*pi/wavel0;
	double X0=wavenumber0*x0,Y0=wavenumber0*y0,Z0=wavenumber0*z0;
	double sx=1.0/wavenumber0/w0x,sy=1.0/wavenumber0/w0y;
//	***************************************************************************************
//	nminBeam,nmaxBeam
	double zRx=pi*w0x*w0x/wavel0,zRy=pi*w0y*w0y/wavel0;
	double wzx=w0x*sqrt(1.0+pow(z0/zRx,2));
	double wzy=w0y*sqrt(1.0+pow(z0/zRy,2));
	double Wzx=wzx*wavenumber0,Wzy=wzy*wavenumber0;
	double R0=sqrt(X0*X0+Y0*Y0);
	double wratio=sqrt(10.0*log(10.0));
	double wwx=Wzx*wratio,wwy=Wzy*wratio,Rmax=0.0;
	for(int ialpha=0;ialpha<720;ialpha++)
	{
		double alpha=ialpha*pi/360.0;
		double Ralpha=sqrt(pow(X0+wwx*cos(alpha),2)+pow(Y0+wwy*sin(alpha),2));
		if(Rmax<Ralpha) Rmax=Ralpha;
	}
	int nmaxBeam=int(Rmax)+1;
	int nminBeam=1;
	int nmidBeam=int(R0+0.5);

//	***************************************************************************************
//	Keywords: Beam-Profile
//	DataBeam[0]		ruon=n+0.5
//	DataBeam[1]		wavenumber0
//	DataBeam[2->18]
	DataBeam[1]=wavenumber0,DataBeam[2]=sx,DataBeam[3]=sy,DataBeam[4]=X0,DataBeam[5]=Y0,DataBeam[6]=Z0,DataBeam[7]=Wzx,DataBeam[8]=Wzy;
	DataBeam[9]=l_order;DataBeam[10]=p_order;
	DataBeam[11]=wavel0,DataBeam[12]=w0x,DataBeam[13]=w0y,DataBeam[14]=x0,DataBeam[15]=y0,DataBeam[16]=z0,DataBeam[17]=wzx,DataBeam[18]=wzy;
	OrderBeam[0]=nminBeam,OrderBeam[1]=nmaxBeam,OrderBeam[2]=nmidBeam;
	
	return 1;
}
