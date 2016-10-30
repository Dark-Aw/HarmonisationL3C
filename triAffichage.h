#ifndef TRI_AFFICHAGE
#define TRI_AFFICHAGE

#include <stdio.h>
#include <stdlib.h>

/*
	NB : EN CAS DE MODIFICATION, SUPPRESSION OU AJOUT D'UN TRIE, LES FONCTIONS SUIVANTES DOIVENT ETRE MODIFIEES :
	
	nomAlgoAffichage
	calculerTempsTri
*/
#define RAPIDE_OPTIMISE 0
#define SHELL 1
#define PAIR_IMPAIR 2
#define FUSION 3
#define RAPIDE_NON_OPTI 4
#define BULLE 5
#define PAR_TAS 6
#define SELECTION 7
#define INSERTION 8
#define COMPTAGE 9

#define TAB_CROISSANT 0
#define TAB_DECROISSANT 1

/*
	-tab : Tableau à analyser
	-nbTab : Nombre de tableau à analyser
	-triEnCours : L'algo à traiter
	return : La moyenne des temps de l'algo
*/
double moyenneAlgo(double** tab, int nbTab, int triEnCours);

/*
	-tab : Tableau à analyser
	-nbTab : Nombre de tableau à analyser
	-triEnCours : L'algo à traiter
	return : Le temps le plus faible
*/
double plusPetitAlgo(double** tab, int nbTab, int triEnCours);

/*
	-tab : Tableau à analyser
	-nbTab : Nombre de tableau à analyser
	-triEnCours : L'algo à traiter
	return : Le temps le plus grand
*/
double plusGrandAlgo(double** tab, int nbTab, int triEnCours);

/*
	-tab : Tableau à analyser
	-nbAlgo : Nombre d'algo de tri

	Modifie le tableau pour stocker la classement des algo par rapport à leur moyenne
	(L'indice est égal à l'algo)
*/
void classementAlgo(double* tab, int nbAlgo);

/*
	-tempsAlgo : Stock les temps d'execution pour chaque algo
	-nbAlgo : Nombre d'algo de tri
	-nbTab : Nombre de tableau par algo
	-choixAlgo : Indique les algos à traiter

	La fonction va exporter en format HTML les différents temps des tableaux triés de chaque algo.
	Génère aussi un fichier CSS pour une meilleur présentation. 
*/
void algoStats(double** tempsAlgo, int nbAlgo, int nbTab, int* choixAlgo, int nbEleTab);

/*
	-tabBase : Tableau à copier
	-tab : Copie du tableau de base
	-n : La taille du tableau
	-nbEleTab : Nombre d'élément dans les tableaux à trier

	Créée une copie du tableau de base dans le deuxième tableau en paramètre
*/
void copieTab(const int* tabBase, int* tab, int n);

/*
	-nbEleTab : Nombre d'élément dans les tableaux à trier
	-tailleEle : La taille de chaque élément compris entre 0 et la valeur choisie	
	-nbAlgo : Nombre d'algo de tri
	-nbTab : Nombre de tableau par algo
	-tempsAlgo : Stock les temps d'execution pour chaque algo
	-choixAlgo : Indique les algos à traiter

	La fonction va créer des tableaux selon les paramètres indiqués.
	Chaque tableau créer à des éléments aléatoirs (Il ne sont théoriquement pas triés).
	Pour que les tests soient égaux entre les algos, chaque tableau généré aléatoirement est dupliqué pour chaque algo. Les algos ont donc les mêmes tableaux à trier.
*/
void triTabRand(int nbEleTab, int tailleEle, int nbAlgo, int nbTab, double** tempsAlgo, int* choixAlgo);

/*
	algo : L'algo en cours
	return : Le nom de l'algo en cours de traitement
*/
char* nomAlgoAffichage(int algo);

/*
	-nbAlgo : Nombre d'algo de tri
	-nbTab : Nombre de tableau par algo
	-choixAlgo : Indique les algos à traiter
	-nbEleTab : Nombre d'élément dans les tableaux à trier	
	-tabATrier : Tableaux à trier pour chaque algo
	-tempsAlgo : Stock les temps d'execution pour chaque algo
	
	La fonction va exécuter les fonctions de trie pour trier les tableaux liés à chaque algo.
	Les temps d'exécutions sont stockés dans le tableau tempsAlgo
*/
void calculerTempsTri(int nbAlgo, int nbTab, int* choixAlgo, int nbEleTab, int*** tabATrier, double** tempsAlgo);

/*
	-nbTab : Nombre de tableau par algo
	-nbEleTab : Nombre d'élément dans les tableaux à trier	
	-tailleEle : La taille de chaque élément compris entre 0 et la valeur choisie
	-choixAlgo : Indique les algos à traiter
	-nbAlgo : Nombre d'algo de tri

	Lance les algos de trie selon les paramètres.
	Les tableaux seront composés d'éléments aléatoirs.
	Les temps d'exécutions seront exportés dans un format HTML pour une meilleure lisibilité.
*/
void lancementTriTabRand(int nbTab, int nbEleTab, int tailleEle, int* choixAlgo, int nbAlgo);

/*
	-nbEleTab : Nombre d'élément dans les tableaux à trier	
	-nbAlgo : Nombre d'algo de tri
	-tempsAlgo : Stock les temps d'execution pour chaque algo
	-choixAlgo : Indique les algos à traiter	
	-choixCroiDesc : Utiliser un tableau croissant ou décroissant

	La fonction va créer un tableau croissant ou décroissant de taille nbEleTab.
	Pour que les tests soient égaux entre les algos, chaque tableau généré est dupliqué pour chaque algo. Les algos ont donc les mêmes tableaux à trier.
*/
void triTabCroissantDecroissant(int nbEleTab, int nbAlgo, double** tempsAlgo, int* choixAlgo, int choixCroiDesc);

/*
	-nbEleTab : Nombre d'élément dans les tableaux à trier
	-choixAlgo : Indique les algos à traiter
	-nbAlgo : Nombre d'algo de tri
	-choixCroiDesc : Utiliser un tableau croissant ou décroissant

	Lance les algos de trie selon les paramètres.
	Le tableau sera composés d'éléments croissant ou décroissant.
	Les temps d'exécutions seront exportés dans un format HTML pour une meilleure lisibilité.
*/
void lancementTriTabCroiDesc(int nbEleTab, int* choixAlgo, int nbAlgo, int choixCroiDesc);

#endif