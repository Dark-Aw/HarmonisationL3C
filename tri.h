#ifndef TRI
#define TRI

#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


/*
	-nb1, nb2 : indice de la valeur à échanger
	-tab : Le tableau à modifier

	Echange deux éléments d'un tableau
*/
void echangeTab(int* tab, const int nb1, const int nb2);

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
/*
	-tab : Le tableau à trier
	-deb : Début du tableau
	-fin : Fin du tableau
	NB : Il faut appeler la fonction avec n - 1 pour la fin du tab

	Le tri rapide va choisir une valeur dit "pivot" (Le choix est fixe dans notre cas). Le pivot va être placé à la fin pour ne pas l'affecter pendant le traitement.
	Le tri va comparer les valeurs du tableau avec celle du pivot pour pouvoir les déplacer si nécessaire en deux catégories : 
	- Valeurs plus grandes que la valeur du pivot -> Situées à droite
	- Valeurs plus petites que la valeur du pivot -> Situées à gauche
	Une fois fait, on echange le pivot avec la l'emplacement de la première valeur plus grande que la valeur du pivot.
	Puis on partitionne le tableau en deux sous tableau, un avant l'emplacement du pivot et un apres.
	On appel récursivement la fonction sur les deux nouveaux tableaux et ainsi de suite.
*/
void triRapide(int* tab, int deb, int fin);
/*
	-tab : Le tableau à trier
	-deb : Début du tableau
	-fin : Fin du tableau
	NB : Il faut appeler la fonction avec n - 1 pour la fin du tab

	Le tri rapide optimisé fonctionne de la même façon que le tri rapide classique.
	La différence se trouve dans le traitement
	
*/
void triRapideOptimise(int* tab, int deb, int fin);

/*
	-tab : Le tableau à trier
	-deb : Début du tableau
	-fin : Fin du tableau
	NB : Il faut appeler la fonction avec n - 1 pour la fin du tab

	(Tri Fusion)
	Découpe le tableau en deux partie, chaque partie est redécoupée en deux récursivement.
	La découpe stop quand le tableau n'a plus qu'un élément.
*/
void decoupage(int* tab, int deb, int fin);

/*
	-tab : Le tableau à trier
	-deb : Début du premier sous tableau
	-nTab1 : Fin du premier sous tableau
	-nTab2 : Début du deuxième sous tableau
	-fin : Fin du deuxième sous tableau
	
	(Tri Fusion)
	Fusion des deux sous tableaux.
	Pendant la fusion, on tri le tableau final directement à l'insertion.
	(Cela n'est possible que si les deux sous tableaux sont déjà triés)
*/
void fusion(int* tab, int deb, int nTab1, int nTab2, int fin);

void estTrie(int* tab, int n);

void triParSelection(int tab[],int taille);
//tab : correspond au tableau à trier
//taille : correspond à la taille du tableau
// l'objectif du tri par insertion est de parcourir un tableau d'entier en plaçant l'élément nécéssitant un déplacement au bon endroit en opérant un décalage des autres valeurs
// de cette façon l'élément à placer est affecté au vide créé par le décalage des valeurs.
void triParInsertion(int tab[],int taille);
//tab : correspond au tableau à trier
//taille : correspond à la taille du tableau
// Le tri à bulle compare deux éléments d'un tableau et les échange si nécéssaire de cette façon , les éléments les plus grands se retrouvent en fin de tableau
void triAbulle(int tab[],int taille);
//tab : le tableau qui sera parcouru
//taille : la taille du tableau
//Cette fonction parcours le tableau envoyé en paramètre et en renvoie la valeur maximale de celui-ci qui sera réutilisée lors du tri par comtpage
int borneMax(int tab[],int taille);
//tab : correspond au tableau à trier
//taille : correspond à la taille du tableau
//Le tri par comptage consiste à compter le nombre de fois qu'une valeur apparait dans un tableau et stocké ce nombre dans un tableau de comtpage intermédiaire
//qui nous sert ensuite à réaliser le tableau trié proprement dit
void triComptage(int tab[],int taille);
//tab:correspond au tableau utilisé dans les fonctions realisationTas et triParTAs
//i et j : correspond au valeur à permutter
//Cette fonction échange les valeurs i et j envoyées en paramètre
void permutationTas(int tab[],int i,int j);
//tab:correspond à transformer en arbre binaire
//i:correspond au noeud traité par la fonction
//taille: correspond à la taille du tableau
//Cette fonction transforme le tableau envoyé en paramètre en tas
void realisationTas(int tab[],int noeud,int taille);
//tab:correspond au tableau à trier
//taille: correspond à la taille du tableau
//Le tri par tas transforme dans un premier temps le tableau a trié en arbre , ou chaque sous-ensemble de 3 éléments forme un noeud
//"La racine"de cet arbre sera le premier élément du tableau
void triParTas(int tab[],int taille);

#endif
