/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies maisons */
#include "structures.c"

/* fonction pour charger et ouvrir un fichier texte fasta */
int Charger_Fichier(char* nom_fichier)
{
	int i;
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
			//printf("SEQUENCE %d\n", i);
			i++;
		}
		if (ligne[0] != '>')
		//if ( strlen(ligne) == 71) // une ligne de sequence à 71 caractère
		{
			// printf("Retrieved line of length %zu :\n", read);
			//printf("%s", ligne);
		}
	}
	return i;
}

void Creer_Tableau_Sequences(int nb_seq, char* nom_fichier)
{
	int i = 0;
    FILE* fp;
    char *ligne = NULL;
    char* anc_ligne = NULL; // buffer
    size_t len = 0;
    ssize_t read;
    int long_ligne = 0; // longueur de la sequence lue ligne par ligne
    TTabSeq sequences_fichier[nb_seq];
	
	/* ouverture du fichier */
	fp=fopen(nom_fichier, "r");
	
	/* gestion d'erreur d'ouverture du fichier */
	if(fp==NULL)
	{
		printf("erreur lors de l'ouverture du fichier spécifié");
	}
	else
	{
		//printf("Fichier ouvert avec succès\n");
	}

	while ((read = getline(&ligne, &len, fp)) != -1)
	{
		if(ligne[0] == '>')
		{
			//printf("SEQUENCE %d\n", i);
			//printf("Longueur ligne %lu\n", strlen(ligne));

			sequences_fichier[i].identifiant_seq = (char*)malloc((strlen(ligne))*sizeof(char)); // +1 pour caractère de fin de ligne
			sequences_fichier[i].identifiant_seq = ligne;
			printf("%s\n", sequences_fichier[i].identifiant_seq);

			i++;
		}
		if (ligne[0] != '>') // une ligne de sequence à 71 caractère
		{
			//printf("Retrieved line of length %zu :\n", read);
			//printf("%s", ligne);
		
			long_ligne = long_ligne + strlen(ligne);
			anc_ligne = (char*)malloc((long_ligne)*sizeof(char));
			
			if(anc_ligne == NULL)
			{
				anc_ligne = ligne;
			}
			else
			{
				anc_ligne = strcat(anc_ligne, ligne);
			}
			printf("%s\n", anc_ligne);
		}
	}
}