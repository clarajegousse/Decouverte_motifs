/* Découverte de motif d'occurrence */

/* librairies */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* constante */
/* #define MAX 100 */

/* programme principale */
int main(){
  
  /* déclaration des variables */
  char* nom_fichier; 
	nom_fichier=(char*)malloc(sizeof(char)*101);
	
	printf("veuiller spécifier un fichier de séquences (format fasta)\n");
	//fgets(nom_fichier,100, stdin);
	printf("%s\n",nom_fichier);
	Charger_Fichier(nom_fichier);
	printf("fin\n");

  return 0;
}
