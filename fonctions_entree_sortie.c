/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* fonction pour charger et ouvrir un fichier texte fasta */
void Charger_Fichier(char* nom_fichier)
{
    int i = 1;
    FILE* fp;
    char *ligne = NULL;
    size_t len = 0;
    ssize_t read;
	
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
	
	/* Lecture des séquences fasta ligne par ligne */
	while ((read = getline(&ligne, &len, fp)) != -1)
	{
		if(ligne[0] == '>')
		{
			// create new sequence
			printf("SEQUENCE %d\n", i);
			i++;
		}
		// if (ligne[0] != '>')
		if ( strlen(ligne) == 71) // une ligne de sequence à 71 caractère
		{
			// printf("Retrieved line of length %zu :\n", read);
			 printf("%s", ligne);
		}
	}
}
