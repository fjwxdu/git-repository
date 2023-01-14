#include <iostream>

#include "../include/def.hpp"

double def(int fx,int fy){
	double fact=1.0;
	int i;
	if(fx==fy)
		return 1.0;
	else if(fx>fy){
		for(i=1;i<=fx-fy;i++)
			fact=fact*(fy+i);
		return fact;
	}
	else if(fx<fy){
		for(i=1;i<=fy-fx;i++)
			fact=fact*(fx+i);
		return 1.0/fact;
	}
}
