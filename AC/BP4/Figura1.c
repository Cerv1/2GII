#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct {
    int a;
    int b;
    
}s[5000];

int main(){
    
    clock_t cgt1, cgt2;
    double ncgt=0;
    
    int ii,X1,X2,i,R[40000];
    
    cgt1=clock();
    
    for (ii=0; ii<40000;ii++) {
        X1=0; X2=0;
        for(i=0; i<5000;i++) X1+=2*s[i].a+ii;
        for(i=0; i<5000;i++) X2+=3*s[i].b-ii;
        if (X1<X2)
            R[ii]=X1;
        else
            R[ii]=X2;
    }
    
    cgt2 = clock();
    ncgt = (double) (cgt2 - cgt1) / CLOCKS_PER_SEC;
    printf("\tTime:\t%8.6f\n", ncgt);
    
return 0;
}
