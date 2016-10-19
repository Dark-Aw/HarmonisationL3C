#ifndef TRI
#define TRI

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

/*
	-nb1, nb2 : indice de la valeur à échanger
	-tab : Le tableau à modifier

	Echange deux deux éléments d'un tableau
*/
void echangeTab(int* tab, const int nb1, const int nb2);
/*
	-tab : Le tableau à trier
	-n : La taille du tableau
*/
int* triBase(int* tab, const int n, int k);
/*
	-tab : Le tableau à trier
	-n : La taille du tableau
	
	Tri le tableau selon une distance (index du tableau) qui varie par rapport à la taille 
	du tableau. Cette distance va décroitre petit à petit. L'algo qui tri est similaire 
	au tri par insertion. Il est répété pour chaque distance.
*/
void triShell(int* tab,int n);
void afficheTab(const int* tab, const int n);
void afficheTas(const int* tab, const int n);
/*
	-tab : Le tableau à trier
	-n : La taille du tableau

	Le tri pair/impair ressemble beaucoup au tri à bulle (Il compare deux valeurs et les échanges si besoin).
	Tant que le tableau n'est pas trié, l'algo va s'executer en deux temps. 
	Il va comparer et échanger (si besoin) la valeur dont l'indice du tableau est :
	- Pair avec l'élément d'après (Pair comparé à impair)
	- Impair avec l'élément d'après (Impair comparé à pair)
	Pour chaque temps, les comparaisons se font sur tout le tableau.
	Si pour chacun des deux temps il n'y a aucun changement, le tableau est considéré comme trié.
*/
void triPairImpair(int* tab, const int n);
void triParSelection(int tab[],int taille);
void triParInsertion(int tab[],int taille);
void triAbulle(int tab[],int taille);
void generationTableau(int tab[],int taille);
#endif
