/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>

/* fonction pour charger et ouvrir un fichier texte fasta */
void Charger_Fichier(char* nom_fichier)
{
    FILE* fp;
	
	/* ouverture du fichier */
	fp=fopen(nom_fichier, "r");
	
	/* gestion d'erreur d'ouverture du fichier */
	if(fp==NULL)
	{
		printf("erreur lors de l'ouverture du fichier spécifié");
	}
	else
	{
		printf("Fichier ouvert avec succès\n");
	}
}
