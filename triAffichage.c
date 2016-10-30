#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tri.h"
#include "triAffichage.h"

void lancementTriTabRand(int nbTab, int nbEleTab, int tailleEle, int* choixAlgo, int nbAlgo){
	int i;
	// Permet de stocker les temps de tri de chaque tableau par rapport à l'algo utilisé
	// tempsAlgo[algo][tempsDuTableau]
	double** tempsAlgo = (double**)(malloc(sizeof(double*) * nbAlgo));
	for(i = 0; i < nbAlgo; i++){
		tempsAlgo[i] = (double*)(malloc(sizeof(double) * nbTab));
	}
	
	// On tri avec des tableaux générés aléatoirements
	triTabRand(nbEleTab, tailleEle, nbAlgo, nbTab, tempsAlgo, choixAlgo);
	// On affiche les temps
	algoStats(tempsAlgo, nbAlgo, nbTab, choixAlgo, nbEleTab);

	// Free
	for(i = 0; i < nbAlgo; i++){
		free(tempsAlgo[i]);
	}	
	free(tempsAlgo);
}

void lancementTriTabCroiDesc(int nbEleTab, int* choixAlgo, int nbAlgo, int choixCroiDesc){
	int i;
	// Permet de stocker les temps de tri de chaque tableau par rapport à l'algo utilisé
	// tempsAlgo[algo][numeroDeTab] -> temps du tab
	double** tempsAlgo = (double**)(malloc(sizeof(double*) * nbAlgo));
	for(i = 0; i < nbAlgo; i++){
		tempsAlgo[i] = (double*)(malloc(sizeof(double) * 1));
	}
	// On tri un tableau croissant ou décroissant
	triTabCroissantDecroissant(nbEleTab, nbAlgo, tempsAlgo, choixAlgo, choixCroiDesc);
	// On affiche les temps
	algoStats(tempsAlgo, nbAlgo, 1, choixAlgo, nbEleTab);

	// Free
	for(i = 0; i < nbAlgo; i++){
		free(tempsAlgo[i]);
	}	
	free(tempsAlgo);
}

void algoStats(double** tempsAlgo, int nbAlgo, int nbTab, int* choixAlgo, int nbEleTab){
	// Tableau permettant de faire un classement entre les différents algo (On classe les moyenne stockées)
	// tabClassement[algo] -> valeur du classement
	double* tabClassement = (double*)(malloc(sizeof(double) * nbAlgo));
	double moyenne;
	int i, j;

	// Création du fichier CSS
	FILE *fcss = fopen("style.css", "w");
	if (fcss == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}

	fprintf(fcss, "body{font-family: 'Helvetica Neue', Helvetica, Arial;\nfont-size: 14px;\nline-height: 20px;\nfont-weight: 400;\ncolor: #3b3b3b;\n-webkit-font-smoothing: antialiased;\nfont-smoothing: antialiased;\nbackground: #2b2b2b;}"
		"\n\n.wrapper{margin: 0 auto;\npadding: 80px 40px;\nmax-width: 800px;}"
		"\n\n.table{margin: 0 0 40px 0;\nwidth: 100%%;\nbox-shadow: 0 1px 3px rgba(0,0,0,0.2);\ndisplay: table;}"
		"\n\n.row{display: table-row;\nbackground: #f6f6f6;}"
		"\n\n.row:nth-of-type(odd){background: #e9e9e9;}"
		"\n\n.header{font-weight: 900;\ncolor: #ffffff;\nbackground: #2980b9 !important;}"
		"\n\n.cell{padding: 6px 12px;\ndisplay: table-cell;}");
	fclose(fcss);

	// Création du fichier HTML
	FILE *fhtml = fopen("index.html", "w");
	if (fhtml == NULL){
	    printf("Error opening file!\n");
	    exit(1);
	}
	// En-Tête + balises ouvrantes body
	fprintf(fhtml, "<!DOCTYPE html>\n<html>\n\t<head>\n\t\t<meta charset=\"utf-8\" />\n\t\t<link rel=\"stylesheet\" href=\"style.css\" />\n\t\t<title>Performances des algorithmes</title>\n\t</head>\n\t<body>\n\t\t<div class=\"wrapper\">\n");
	
	//Legende
	fprintf(fhtml, "\t\t\t<p class=\"row\">\n"
		"\t\t\t\tLes temps sont en seconde</br>\n"
		"\t\t\t\tNombre de tableau : %d</br>\n"
		"\t\t\t\tNombre d'élément par tableau : %d\n"
		"\t\t\t</p>\n", nbTab, nbEleTab);

	// Début du tableau de données 
	fprintf(fhtml, "\t\t\t<div class=\"table\">\n");	
	
	// Titre de chaque colonne
	fprintf(fhtml, "\t\t\t\t<div class=\"row header\">\n");
	fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%s</div>\n", "");
	for (i = 0; i < nbAlgo; ++i){
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%s</div>\n", nomAlgoAffichage(choixAlgo[i]));
	}
	fprintf(fhtml, "\t\t\t\t</div>\n");
	
	// Rempli le tableau avec les temps mesurés pour chaque algo
	for(i = 0; i < nbTab; i++){
		fprintf(fhtml, "\t\t\t\t<div class=\"row\">\n");
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\"></div>\n");
		for (j = 0; j < nbAlgo; j++){
			fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%lf</div>\n", tempsAlgo[j][i]);
		}
		fprintf(fhtml, "\t\t\t\t</div>\n");
	}

	//Separateur
	fprintf(fhtml, "\t\t\t\t<div class=\"row\">\n");
	fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\"></div>\n");
	for (i = 0; i < nbAlgo; i++){
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\"></div>\n");
	}
	fprintf(fhtml, "\t\t\t\t</div>\n");

	// Moyenne
	fprintf(fhtml, "\t\t\t\t<div class=\"row\">\n");
	fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">Moyenne</div>\n");
	for (i = 0; i < nbAlgo; i++){
		moyenne = moyenneAlgo(tempsAlgo, nbTab, i);
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%lf</div>\n", moyenne);
		// On stock la moyenne dans le tab de classement. Elle sera elle-même remplacée par le classement
		tabClassement[i] = moyenne;
	}
	fprintf(fhtml, "\t\t\t\t</div>\n");

	// Plus petit
	fprintf(fhtml, "\t\t\t\t<div class=\"row\">\n");
	fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">Plus petit</div>\n");
	for (i = 0; i < nbAlgo; i++){
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%lf</div>\n", plusPetitAlgo(tempsAlgo, nbTab, i));
	}
	fprintf(fhtml, "\t\t\t\t</div>\n");

	// Plus grand
	fprintf(fhtml, "\t\t\t\t<div class=\"row\">\n");
	fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">Plus grand</div>\n");
	for (i = 0; i < nbAlgo; i++){
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%lf</div>\n", plusGrandAlgo(tempsAlgo, nbTab, i));
	}
	fprintf(fhtml, "\t\t\t\t</div>\n");

	//Classement (Moyenne)
	classementAlgo(tabClassement, nbAlgo);
	fprintf(fhtml, "\t\t\t\t<div class=\"row\">\n");
	fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">Classement (Moy.)</div>\n");
	for (i = 0; i < nbAlgo; i++){
		fprintf(fhtml, "\t\t\t\t\t<div class=\"cell\">%.0lf</div>\n", tabClassement[i]);
	}
	fprintf(fhtml, "\t\t\t\t</div>\n");

	// Fin du fichier
	fprintf(fhtml, "\t\t\t</table>\n\t\t</div>\n\t</body>\n</html>");
	fclose(fhtml);	
	free(tabClassement);
}

void triTabCroissantDecroissant(int nbEleTab, int nbAlgo, double** tempsAlgo, int* choixAlgo, int choixCroiDesc){
	int i, j, ele;
	// Les tableaux à trier pour chaque algo
	// TabATrier[algo][numeroDeTableau][indice] -> Valeur d'un tableau
	int*** tabATrier = (int***)malloc(sizeof(int**) * nbAlgo);

	// Malloc
	for (i = 0; i < nbAlgo; i++){
		tabATrier[i] = (int**)malloc(sizeof(int*) * 1);
	}
	for (i = 0; i < nbAlgo; i++){
		tabATrier[i][0] = (int*)malloc(sizeof(int) * nbEleTab);
	}
	
	// Pour le nombre d'élément voulu
	for(ele = 0; ele < nbEleTab; ele++){
		// Si nous voulons un tableau croissant
		if(choixCroiDesc == TAB_CROISSANT){
			// Pour chaque algo
			for(j = 0; j < nbAlgo; j++){
				// On rempli le tableau avec des éléments croissants
				tabATrier[j][0][ele] = ele;
			}
		// Si nous voulons un tableaux décroissant
		}else if(choixCroiDesc == TAB_DECROISSANT){
			// Pour chaque algo
			for(j = 0; j < nbAlgo; j++){
				// On rempli le tableau avec des éléments décroissants
				tabATrier[j][0][ele] = nbEleTab - ele;
			}
		}		
	}
	
	calculerTempsTri(nbAlgo, 1, choixAlgo, nbEleTab, tabATrier, tempsAlgo);

	// Free
	for (i = 0; i < nbAlgo; i++){
		free(tabATrier[i][0]);
	}
	for (i = 0; i < nbAlgo; i++){
		free(tabATrier[i]);
	}
	free(tabATrier);
}

void triTabRand(int nbEleTab, int tailleEle, int nbAlgo, int nbTab, double** tempsAlgo, int* choixAlgo){		
	int i, j, ele;
	// Les tableaux à trier pour chaque algo
	// TabATrier[algo][numeroDeTableau][indice] -> Valeur d'un tableau
	int*** tabATrier = (int***)malloc(sizeof(int**) * nbAlgo);
	// Tableau de référence à copier pour chaque algo
	int* tabDeRef = (int*)(malloc(sizeof(int) * nbEleTab));

	// Malloc
	for (i = 0; i < nbAlgo; i++){
		tabATrier[i] = (int**)malloc(sizeof(int*) * nbTab);
	}
	for (i = 0; i < nbAlgo; i++){
		for(j = 0; j < nbTab; j++){
			tabATrier[i][j] = (int*)malloc(sizeof(int) * nbEleTab);
		}
	}
	// Création des tableaux
	for(i = 0; i < nbTab; i++){
		// Création du tableau de référence
		for(ele = 0; ele < nbEleTab; ele++){
			// On stock un élément aléatoir compris entre 0 et tailleEle
			tabDeRef[ele] = rand() % tailleEle;
		}
		// Pour chaque algo
		for(j = 0; j < nbAlgo; j++){
			// On copie le tableau de référence dans la zone de tableau à trier
			copieTab(tabDeRef, tabATrier[j][i], nbEleTab);
		}		
	}	

	// Calcul les temps de tri
	calculerTempsTri(nbAlgo, nbTab, choixAlgo, nbEleTab, tabATrier, tempsAlgo);

	// Free
	for (i = 0; i < nbAlgo; i++){
		for(j = 0; j < nbTab; j++){
			free(tabATrier[i][j]);
		}
	}
	for (i = 0; i < nbAlgo; i++){
		free(tabATrier[i]);
	}
	free(tabATrier);
	free(tabDeRef);
}

char* nomAlgoAffichage(int algo){
	// Selon l'algo, on retourne son nom
	switch(algo){
		case RAPIDE_OPTIMISE:
			return "Tri Rapide Optimisé";
		break;
		case SHELL:
			return "Tri Shell";
		break;
		case PAIR_IMPAIR:
			return  "Tri Pair / Impair";
		break;
		case FUSION:
			return "Tri Fusion";
		break;
		case RAPIDE_NON_OPTI:
			return "Tri Rapide Non Optimisé";
		break;
		case BULLE:
			return "Tri A Bulle";
		break;
		case PAR_TAS:
			return "Tri Par Tas";
		break;
		case SELECTION:
			return "Tri Par Selection";
		break;
		case INSERTION:
			return "Tri Par Insertion";
		break;
		case COMPTAGE:
			return "Tri Par Comptage";
		break;
	}
	return "";
}

void calculerTempsTri(int nbAlgo, int nbTab, int* choixAlgo, int nbEleTab, int*** tabATrier, double** tempsAlgo){		
	int i, j;
	// Stock le tic de début et de fin
	clock_t toc, tic;
	// Coentient le temps en seconde (Utilise tic et toc)
	double time_spent;
	// Pour chaque algo
	for(i = 0; i < nbAlgo; i++){
		// Pour chaque tableau
		for(j = 0; j < nbTab; j++){
			// Début du timer
			tic = clock();
			// On tri selon les algos choisis par l'utilisateurs
			switch(choixAlgo[i]){
				case RAPIDE_OPTIMISE:
					triRapideOptimise(tabATrier[i][j], 0, nbEleTab - 1);
				break;
				case SHELL:
					triShell(tabATrier[i][j], nbEleTab);
				break;
				case PAIR_IMPAIR:
					triPairImpair(tabATrier[i][j], nbEleTab);
				break;
				case RAPIDE_NON_OPTI:
					triRapide(tabATrier[i][j], 0, nbEleTab - 1);
				break;
				case FUSION:
					decoupage(tabATrier[i][j], 0, nbEleTab - 1);
				break;
				case BULLE:
					triAbulle(tabATrier[i][j], nbEleTab);
				break;
				case PAR_TAS:
					triParTas(tabATrier[i][j], nbEleTab);
				break;
				case SELECTION:
					triParSelection(tabATrier[i][j], nbEleTab);
				break;
				case INSERTION:
					triParInsertion(tabATrier[i][j], nbEleTab);
				break;
				case COMPTAGE:
					triComptage(tabATrier[i][j], nbEleTab);
				break;
			}
			// fin du timer
			toc = clock();
			// Calcul le temps du tri en seconde
			time_spent = (double)(toc - tic) / CLOCKS_PER_SEC;
			// Stock le temps du tri par rapport à l'algo
			tempsAlgo[i][j] = time_spent;			
		}
	}
}

double moyenneAlgo(double** tab, int nbTab, int triEnCours){
	double moyenne = 0;
	int i;
	for(i = 0; i < nbTab; i++){
		// On ajoute le temps de tout les tableaux pour un algo
		moyenne += tab[triEnCours][i];
	}
	// On divise le résultat par le nombre de tableau pour trouver la moyenne 
	return moyenne / nbTab;
}

double plusPetitAlgo(double** tab, int nbTab, int triEnCours){
	// Stock le premier élément du tableau pour en faire une réference
	double plusPetit = tab[triEnCours][0];
	int i;
	// Pour chaque éléments du tableau sauf le premier
	for (i = 1; i < nbTab; ++i){
		// Si le temps en cours de traitement est plus petit
		if(tab[triEnCours][i] < plusPetit){
			// On le stock
			plusPetit = tab[triEnCours][i];
		}
	}
	return plusPetit;
}

double plusGrandAlgo(double** tab, int nbTab, int triEnCours){
	// Stock le premier élément du tableau pour en faire une réference
	double plusGrand = tab[triEnCours][0];
	int i;
	// Pour chaque éléments du tableau sauf le premier
	for (i = 1; i < nbTab; ++i){
		// Si le temps en cours de traitement est plus grand
		if(tab[triEnCours][i] > plusGrand){
			// On le stock
			plusGrand = tab[triEnCours][i];
		}
	}
	return plusGrand;
}

void classementAlgo(double* tab, int nbAlgo){
	// Pour rappel, tab : tableau de moyennes dont l'indice est égal à l'algo
	// Stock le classement temporairement
	double* tabTmp = (double*)(malloc(sizeof(double) * nbAlgo));
	int i, j;
	// Pour chaque algo
	for (i = 0; i < nbAlgo; i++){
		// Le classment est de 1 par défaut
		tabTmp[i] = 1;
		// Pour chaque algo
		for(j = 0; j < nbAlgo; j++){
			// Sauf celui en cours de traitement (i)
			if(j != i && tab[i] > tab[j]){
				// On ajout 1 au classement si un algo est meilleur que celui en cours de traitement (i)
				tabTmp[i] += 1;
			}
		}
	}
	// Pour chaque algo
	for (i = 0; i < nbAlgo; i++){
		// On remplace la moyenne par le classement
		tab[i] = tabTmp[i];
	}
	// Free
	free(tabTmp);
}

void copieTab(const int* tabBase, int* tab, int n){
	int i;
	// Pour chaque élément du tableau
	for(i = 0; i < n; i++){
		// On stock les éléments du tableau à copier dans le nouveau tableau
		tab[i] = tabBase[i];
	}
}