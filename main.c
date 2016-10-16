#include <stdio.h>
#include <stdlib.h>

#include "tri.h"


/*
void triRapide(int* tab, int deb, int fin) {
    int pivot;
    if(fin - deb < 2){
    	return;
    }
    if(fin - debut == 2){
    	if(tab[deb] > tab[fin]){
    		echangeTab(tab, deb, fin);
    		return;
    	}
    }
    pivot = deb + 1;
    while(){
    	if(tab[])
    }
}
*/
int main (int argc, char *argv[]) {
	int tab[10] = {556, 872, 422, 398, 502, 230, 100, 787, 42, 32};
	//afficheTas(tab, 9);
	//triShell(tab, 8);
	//triRapide(tab, 0, 8);
	triPairImpair(tab, 10);
	afficheTab(tab, 10);
	return 0;
}