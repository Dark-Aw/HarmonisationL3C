#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

void echangeTab(int* tab, const int nb1, const int nb2){
	int tmp = tab[nb1];
	tab[nb1] = tab[nb2];
	tab[nb2] = tmp;
}

void afficheTab(const int* tab, const int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%d", tab[i]);
		if(i != n - 1){
			printf(":");
		}
	}
	printf("\n");
}

void afficheTas(const int* tab, const int n){
	int i, c = 1;
	for(i = 1; i <= n; i++){
		if(i == c){
			printf("|");
			c *= 2;
		}else{
			printf(":");
		}
		printf("%d", tab[i-1]);
		
	}
	printf("\n");
}

int* triBase(int* tab, const int n, int k){
	int i;
	for(i = 0; i < n; i++){
		tab[i] = tab[i] % 100;
	}
	return tab;
}

void triShell(int* tab,int n){
	int distance = 0, i, j, valeurTmp;
	while(3 * distance + 1 < n){
		// Distance max calculée par rapport à la taille du tableau
		// Distance optimale selon Donald Shell 
		distance = 3 * distance + 1;
	}
	// Pour chaque distance (Décroissante)
	for(distance = distance; distance > 0; distance /= 3){
		// Parcours chaque élément du tableau
		for (i = distance; i < n; ++i){
			// Stock la valeur en cours de traitement
			valeurTmp = tab[i];
			// Stock l'index de la valeur en cours de traitement
			j = i;
			// Tant que l'index j est suppérieur à la distance (empêche la sortie de tableau)
			// Et tant que la prochaine valeur à traiter selon la distance est suppérieur à la valeur de traitement
			while(j >= distance && tab[j - distance] > valeurTmp){
				// On déplace le tableau petit à petit toujours selon la distance
				tab[j] = tab[j - distance];
				// On change l'index selon la distance 
				j -= distance;
			}
			// On insère la valeur en cours de traitement dans le nouvel emplacement
			tab[j] = valeurTmp;
		}
	}
 }

void triPairImpair(int* tab, const int n){
	int i, estTrie = FALSE;
	// Tant que le tableau n'est pas trié
	while(!estTrie){
		// Le tableau est considéré comme trié si il n'y a aucun changement dans le tableau
		// Sinon on refait une boucle
		estTrie = TRUE;
		// Pour chaque indice pair du tableau
		for(i = 0; i < n - 1; i+=2){
			if(tab[i] > tab[i + 1]){
				echangeTab(tab, i, i + 1);
				estTrie = FALSE;
			}
		}
		// Pour chaque indice impair du tableau
		for (i = 1; i < n - 1; i += 2){
			if(tab[i] > tab[i + 1]){
				echangeTab(tab, i, i + 1);
				estTrie = FALSE;
			}
		}
	}
}
