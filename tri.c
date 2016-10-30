#include <stdio.h>
#include <stdlib.h>
#include "tri.h"

#define TRUE 1
#define FALSE 0

void estTrie(int* tab, int n){
	int i, trie = 1;
	for(i = 0; i < n - 1; i++){
		if(tab[i] > tab[i + 1]){
			printf("Est Trie : NON %d:%d\n", i + 1, tab[i + 1]);
			trie = 0;
			return;
		}
	}
	if(trie == 1){
		printf("Est Trie : OUI\n");
	}
}

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

void triRapide(int* tab, int deb, int fin){
	// Si il n'y a aucun ou un élément dans le tableau
	if(deb >= fin){
		// On considère le tableau trié
		return;
	}
	// S'il n'y a que deux éléments dans le tableau (Evite de créer un pivot pour seulement deux éléments)
	if(deb == fin - 1){
		// Echange les deux éléments si nécéssaire
		if(tab[deb] > tab[fin]){
			echangeTab(tab, deb, fin);
			// Le tableau est trié
			return;
		}
	}

	// Stock l'indice du pivot	
	int pivot = fin;
	// Echange le pivot avec l'élément en fin de tableau
	echangeTab(tab, pivot, fin);
	// Stock la valeur du pivot
	int valPivot = tab[fin];
	// i : l'indice du tableau, j : l'indice du premier élément plus grand que le pivot
	int i, j = deb;
	// Parcours le 
	for(i = deb; i <= fin - 1; i++){
		if(tab[i] <= valPivot){
			echangeTab(tab, i, j);
			j++;
		}
	}
	// Replace le pivot au bon endroit dans le tableau
	echangeTab(tab, fin, j);
	// Stock l'indice du nouvel emplacement du pivot
	pivot = j;
	// Tri la partie gauche du tableau à partir du pivot
	triRapide(tab, deb, pivot - 1);
	// Tri la partie droite du tableau à partir du pivot
	triRapide(tab, pivot + 1, fin);

}

void triRapideOptimise(int* tab, int deb, int fin){
	// Si il n'y a aucun ou un élément dans le tableau
	if(deb >= fin){
		// On considère le tableau trié
		return;
	}
	// S'il n'y a que deux éléments dans le tableau (Evite de créer un pivot pour seulement deux éléments)
	if(deb == fin - 1){
		// Echange les deux éléments si nécéssaire
		if(tab[deb] > tab[fin]){
			echangeTab(tab, deb, fin);
			// Le tableau est trié
			return;
		}
	}

	// Stock l'indice du pivot	
	int pivot = fin;
	// Echange le pivot avec l'élément en fin de tableau
	echangeTab(tab, pivot, fin);
	// Stock la valeur du pivot
	int valPivot = tab[fin];
	// Création de deux curseurs, un qui part de la fin, et l'autre du début tableau
	int curseurDroite = fin - 1, curseurGauche = deb;
	// Tant que les curseurs ne se sont pas croisés
	while(curseurGauche < curseurDroite){
		// On avance le crurseur de gauche dans que sa valeur est inférieur à celle du pivot
		while(tab[curseurGauche] <= valPivot && curseurGauche < curseurDroite){
			curseurGauche++;
		}
		// On recule le curseur de droite tant que sa valeur est suppérieur à celle du pivot
		while(tab[curseurDroite] > valPivot && curseurGauche < curseurDroite){
			curseurDroite--;
		}
		// Si les deux curseurs ne sont pas aux même indice (Evite un echange inutile)
		if(curseurGauche != curseurDroite){
			// Echange des valeurs des deux curseurs (Permet de faire l'équilibre : valeur plus petite que la valeur du pivot, à gauche du pivot et plus grande que le pivot, à sa droite)
			echangeTab(tab, curseurGauche, curseurDroite);
		}
	}

	// Dans le cas où il y a au moins une valeur plus grande que le pivot, on échange
	// Cette condition est vérifiée avec la valeur du curseur car on  considère que tout le tableau a été parcouru (L'équilibre fait que la valeur du crurseur est forcément plus grande que celle du pivot)
	if(tab[fin] < tab[curseurGauche]){		
		echangeTab(tab, curseurGauche, fin);
		pivot = curseurGauche;
	}	

	// Tri la partie gauche du tableau à partir du pivot
	triRapideOptimise(tab, deb, pivot - 1);
	// Tri la partie droite du tableau à partir du pivot
	triRapideOptimise(tab, pivot + 1, fin);
}


void fusion(int* tab, int deb, int nTab1, int nTab2, int fin){
	// Création d'un tableau avec comme taille tous les éléments (Des deux sous tableaux)
	int* tabTmp = (int *)(malloc(sizeof(int) * ((nTab1 - deb) + (fin - nTab2) + 2)));
	int i;
	// Pour tous les éléments
	for(i = 0; i < fin - deb + 1; i++){
		// On les copies dans le tableau temporaire
		tabTmp[i] = tab[deb + i];
	}
	// Permet de modifier la bonne zone dans le tableau (+1 après chaque modification)
	int compteur = 0;
	// Indice des débuts des deux sous tableaux mais par rapport au tableau temporaire (qui n'a pas les mêmes indices)
	// Ces indices s'incrémentes si la valeur en cours est traitée
	int iTab1 = 0, iTab2 = (fin - deb) / 2 + 1;
	// Pour chaque élément
	for(i = 0; i < fin - deb + 1; i++){
		// Si l'indice du premier sous tableau ne dépasse pas la fin du premier sous tableau
		// Si l'indice du deuxième sous tableau ne dépasse pas la fin du deuxième sous tableau
		// NB : Les indices sont adaptés aux tableau temporaire
		if(iTab1 != (fin - deb) / 2 + 1 && iTab2 != fin - deb + 1){
			// Si la valeur de l'indice de traitement du premier tableau est plus grand que le deuxième
			if(tabTmp[iTab1] > tabTmp[iTab2]){
				// On stock la valeur dans la zone des sous tableaux 
				tab[deb + compteur] = tabTmp[iTab2];
				// On incrémente l'indice du sous tableau traité
				iTab2++;
				// On ajoute un au compteur pour stocker la prochaine valeur a la suite dans le tableau
				compteur++;
			}else{ // Si la valeur de l'indice de traitement du premier tableau est plus petit que le deuxième
				tab[deb + compteur] = tabTmp[iTab1];
				iTab1++;
				compteur++;
			}
		// Dans le cas où seul le deuxième sous tableau est totalement traité
		}else if(iTab1 != (fin - deb) / 2 + 1){
			tab[deb + compteur] = tabTmp[iTab1];
			iTab1++;
			compteur++;
		// Dans le cas où seul le premier sous tableau est totalement traité
		}else{
			tab[deb + compteur] = tabTmp[iTab2];
			iTab2++; 
			compteur++;
		}
	}
	// Free
	free(tabTmp);
}


void decoupage(int* tab, int deb, int fin){
	// Si il ne reste qu'un élément dans le tableau
	if(fin - deb == 0){
		// On stop
		return;
	}else{
		// Indice de la moitié du tableau
		int nTab1 = ((fin - deb) / 2) + deb;
		// Indice de la moitié du tableau + 1
		int nTab2 = nTab1 + 1;
		// Découpage du tableau du début à la moitié
		decoupage(tab, deb, nTab1);
		// Découpage du tableau de la moitié du tableau + 1 à la fin
		decoupage(tab, nTab2, fin);
		// Fusion des deux sous tableau
		fusion(tab, deb, nTab1, nTab2, fin);
	}
}

void triAbulle(int tab[],int taille){
	int tmp,i,j;
	for (j=0;j<taille-1;j++)
	{
		// On compare la valeur actuelle de tab[i] avec celle de la case suivante , si celle si est inférieure on permute les valeurs des deux cases
		//Afin d'avoir les plus grands éléments en fin de tableau
		for(i=0;i<taille-1;i++)
		{
			if(tab[i]>tab[i+1])
		 	{	
		 	tmp=tab[i];
		 	tab[i]=tab[i+1];
		 	tab[i+1]=tmp;
		 	}
		}
	}
}

void triParSelection(int tab[],int taille){
	int min,i,j,tmp;
	for (i=0;i<taille;i++)
	{
		// on considère que le plus petit élément du tableau se trouve toujours à l'indice représenté par i
		min = tab[i];
		for (j=i;j<taille;j++)
		{
		//Si l'on rencontre une valeur plus petite , on l'échange en suivant le même procédé que celui du tri à bulle
			if (tab[j]<min)
			{		
				min=tab[j];
				tmp=tab[j];
				tab[j]=tab[i];
				tab[i]=tmp;
			}
	
		
		}
	}
	
}
void triParInsertion(int tab[],int taille){
	int i,j,nb;
	for(i=0;i<taille;i++){
	// on affecte à nb la valeur représentée par la variable i qui nous sert d'indice
		nb = tab[i];
	// on démare la boucle à l'emplace de i car on considère que la partie gauche du tableau est triée
		for(j=i;j>0&&tab[j-1]>nb;j--)
		{
	// si l'on rencontre une valeur plus grande que nb on déplace vers la droite les éléments du tableau plus grands que lui
			tab[j]=tab[j-1];
		}
	// on place nb dans l'emplacement vide créé par le décalage des éléments précédents
		tab[j]=nb;
	}
	
}

int borneMax(int tab[],int taille)
{
	int i,borneMax=tab[0];
	/* Recherche de la valeur maximale du tableau envoyé en paramètre , valeur qui servira à borner le tableau de comptage de la fonction "triComptage"*/
	for(i=1;i<taille;i++)
	{
		if (tab[i]>borneMax)
		{
			borneMax=tab[i];
		}
	}
	return borneMax;	
}

void triComptage(int tab[],int taille)
{
	
	int tailleTabComptage = borneMax(tab,taille);
	//tabComptage est borné en fonction de la valeur maximale contenue dans le tableau envoyé en paramètre
	int *tabComptage=(int*)(malloc(sizeof(int) * (tailleTabComptage+1)));
	int indice=0,i,j;
	/*Initialisation de toutes les cases du tableau de comptage à 0 */
	for (i=0;i<=tailleTabComptage;i++)
	{
		tabComptage[i]=0;
	}
	/*On compte le nombre de fois qu'une valeur apparait dans tab[i] et on incrémente de 1 à chaque fois que cette valeur est rencontrée*/
	for(i=0;i<taille;i++)
	{
		tabComptage[tab[i]]=tabComptage[tab[i]]+1;
	}
	//Parcours du tableau de comptage
	for(i=0;i<=tailleTabComptage;i++)
	{
		//Les éléments du tableau sont triés grâce à la variable i qui sert de compteur
		//Lorsqu'une valeur est présente tab[indice] prend la valeur de i qui s'est incrémentée jusque la
		for(j=0;j<tabComptage[i];j++)
		{
			tab[indice]=i;
			indice++;
		}
	}
	free(tabComptage);
}
/* Fonction permettant l'affichage du tableau envoyé en paramètre*/
void affichageTableau(int tab[],int taille)
{
	int i;
	for(i=0;i<taille;i++)
	{
		printf("la valeur de la case est : %d\n",tab[i]);
	}
}
/* Cette fonction sert à permuter les "fils" du noeud envoyé en paramètre de la fonction realisationTAs*/
void permutationTas(int tab[],int i,int j)
{
	int tmp;
	tmp=tab[i];
	tab[i]=tab[j];
	tab[j]=tmp;
}
void realisationTas(int tab[],int noeud,int taille)
{
	int i=noeud;
	int j = i*2;
	while (j<taille)
	{
		//si le noeud actuel est déja le plus petit élément on passe au noeud suivant
		if(j<taille&&tab[j]<tab[j+1])
			j++;
		//on s'assure que le noeud parent soit toujours inférieur au noeud enfant
		//si ce n'est pas le cas on permute la valeur de tab[i] et tab[j]
		if(tab[i]<tab[j])
		{
			permutationTas(tab,i,j);
			i=j;
			j=2*i;
		}
		//Dans le cas ou aucune des conditions précédents n'est vérifiées , on replace la variable j à la fin du tableau
		else  
			j=taille;
	}
}
void triParTas(int tab[],int taille)
{
	int i;
	//Cette boucle sert à réaliser les noeuds du tableau à trier
	for(i=taille/2;i>=0;i--)
	{
		//boucle servant à la création des tas
		//I est ici le "parent" envoyé en paramètre de la fonction réalisationTas
		realisationTas(tab,i,taille);
		
	}
	//Création du tableau trié,chaque indice traité par la boucle peut ensuite être ignoré puisque celui-ci est trié
	//à cet effet, chaque nouveau noeud est ensuite reconstruit en s'assurant que le noeud parent est toujours plus petit que ses noeuds enfant
	for(i=taille-1;i>0;i--)
	{
		// Ici i correspond à l'indice du noeaud concerné qui est ensuite envoyé en paramètre à la fonction permutationTAs
		permutationTas(tab,i,0);
		//On réeffectue les tas après chaque permutation tout en s'assurant que le noeud "parent" soit plus petit  que ses noeuds enfant
		realisationTas(tab,0,i-1);
	}
}