/* Découverte de motif d'occurrence */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies */
#include "structures.c
#include "fonctions_entree_sortie.h"

/* constante */
/* #define MAX 100 */

/* programme principale */
int main(){
  
  	/* déclaration des variables */
	char* nom_fichier; 
	nom_fichier=(char*)malloc(sizeof(char)*101);
	
	printf("Veuillez spécifier un fichier de séquences nucléotidiques (format fasta):\n");
	//fgets(nom_fichier,100, stdin);
	//printf("%s\n",nom_fichier);
	//Charger_Fichier(nom_fichier);

	printf("Fin\n");
	
	return 0;
}
