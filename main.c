/* Découverte de motif d'occurrence */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies */
#include "structures.c"
#include "fonctions_entree_sortie.h"

/* constantes */
/* #define EXEMPLE 100 */

/* programme principal */
int main(){
  
  	/* déclaration des variables */
	char nom_fichier[100]; 
	nom_fichier=(char*)malloc(sizeof(char)*101);
	
	printf("Veuillez spécifier un fichier de séquences nucléotidiques (format fasta):\n");
	gets(nom_fichier);
	//printf("%s\n",nom_fichier);
	Charger_Fichier(nom_fichier);

	printf("Fin\n");
	
	return 0;
}
