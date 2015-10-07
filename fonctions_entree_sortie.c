/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies */
#include "structures.c"

char* SaisieMot()
{

	char* mot = NULL;
	char temp[100]; // variable temporaire pour stocker la longueur du nom
	int i = 0; // compteur

	scanf("%s", temp); // lecture de chaine de caractère saisie au clavier

	mot=(char*)malloc(strlen(temp)* sizeof(char)); // allocation de mémoire

	if(mot==NULL)
	{
		printf("Erreur d'allocation de mémoire pour SaisieMot.\n");
	}
	else
	{
		for (i= 0; i<= strlen(temp); ++i)
		{
			mot[i] = temp[i];
		}
	}
	return mot; // On retourne le pointeur qui nous dirige vers la premiere lettre du mot 
}

FILE* Ouvrir_Fichier()
{
	char* nom_fichier;
	FILE* fp;

	puts("Veuillez spécifier un fichier de séquences nucléotidiques (format fasta):");
	nom_fichier=SaisieMot();

    if((fp = fopen(nom_fichier, "r")) == NULL)
    {
    	puts("Erreur d'ouverture du fichier: fichier inexistant ou droits insuffisants.");
    	exit(1);
    }
    else
    {
    	return fp;
    } 
}

/* fonction pour charger et ouvrir un fichier texte fasta */
int Compte_Nb_Seq(FILE* fp)
{
	int nb_seq = 0;
	int nb_id =0; 
    char ligne[500]; 

	/* tant qu'on est pas à la fin du fichier */
	while( fgets(ligne, 1000, fp) != NULL)
	{
		if(ligne[0] == '>')
		{
			nb_id++;
		}
		else
		{
			if(ligne[0] == 'A' || ligne[0] == 'T' || ligne[0] == 'T' || ligne[0] == 'C')
    		{
    			nb_seq++;
    		}
		}
	}	

	if( nb_id != nb_seq )
	{
		puts("Le nombre d'identifiant ne correcpond pas au nombre de sequences.\n Veuillez verifier le format de la liste de séquences.");
		exit(1);
	}
    return nb_seq;
}

/* fonction pour charger et ouvrir un fichier texte fasta */
void Lecture_Fichier_Sequences(FILE* fp)
{
	int nb_seq = 0;
	int longueur_ligne;
    char ligne[500]; /* une chaine de 500 caractères */

	/* tant qu'on est pas à la fin du fichier */
	while( !feof(fp) )
	{
		fgets(ligne, 1000, fp); /* on lit la ligne */
 
    	longueur_ligne = strlen(ligne); /* on récupère la longueur de la ligne */
    	
    	if(ligne[longueur_ligne-1] == '\n') /* si le retour chariot est le dernier caractère */
    	{
    		ligne[longueur_ligne-1] = '\0'; /* on le remplace par le symbole de fin de chaine */
    	}
    	printf("%s\n", ligne);
	}
    
}

TTabSeq* AlloueTTabSeq()
{
	TTabSeq* tab_seq = (TTabSeq*)malloc(sizeof(TTabSeq));
	if(tab_seq == NULL)
	{
		printf("Erreur d'allocation de mémoire de AlloueTTabSeq !!\n");
	}
	else
	{
		tab_seq->sequence=NULL;
		tab_seq->identifiant_seq=NULL;
	}
	return tab_seq;
}

void SaisieTTabSeq(TTabSeq* tab_seq)
{
	puts("Saisir identifiant:");
	tab_seq->identifiant_seq = SaisieMot();
	puts("Saisir séquence:");
	tab_seq->sequence = SaisieMot();
}

void AfficheTTabSeq(TTabSeq** tab_seq, int nb_seq)
{
	for (int i = 0; i < nb_seq; ++i)
	{
		printf(">%s \n", tab_seq[i]->identifiant_seq);
		printf("%s\n", tab_seq[i]->sequence);
	}
}


