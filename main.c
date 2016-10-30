#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "tri.h"
#include "triAffichage.h"


int main (int argc, char *argv[]) {
	srand(time(NULL));

	// Nombre de tableau à trier
	int nbTab = 5;
	// Nombre d'élément par tableau
	int nbEleTab = 100;
	// Taille du nombre compris entre 0 et la taille voulue
	int tailleEle = 1000;
	// Les algos (constantes) sont définis dans affichage.h
	int choixAlgo[] = {
		FUSION,
		RAPIDE_OPTIMISE,
		SHELL,
		PAIR_IMPAIR,
		RAPIDE_NON_OPTI,
		BULLE,
		PAR_TAS,
		SELECTION,
		INSERTION,
		COMPTAGE
	};

	int nbAlgo = sizeof(choixAlgo) / sizeof(int);
	lancementTriTabRand(nbTab, nbEleTab, tailleEle, choixAlgo, nbAlgo);
	//lancementTriTabCroiDesc(nbEleTab, choixAlgo, nbAlgo, TAB_CROISSANT);
	//lancementTriTabCroiDesc(nbEleTab, choixAlgo, nbAlgo, TAB_DECROISSANT);
	
	return 0;
}
