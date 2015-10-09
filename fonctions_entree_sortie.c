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

char* Recuperer_ligne(char* ligne)
{
	char* mot = NULL;
	int i = 0;
	
	mot=(char*)malloc(strlen(ligne)* sizeof(char)); // allocation de mémoire
	
	if(mot==NULL)
	{
		printf("Erreur d'allocation de mémoire pour SaisieMot.\n");
	}
	else
	{
		for (i= 0; i<= strlen(ligne); ++i)
		{
			mot[i] = ligne[i];
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

    /* remettre le curseur au début du fichier texte */
    fseek(fp, 0, SEEK_SET);

	/* tant qu'on est pas à la fin du fichier */
	while( fgets(ligne, 1000, fp) != NULL)
	{
		if(ligne[0] == '>')
		{
			nb_id++;
		}
		else
		{
			if(ligne[0] == 'A' || ligne[0] == 'T' || ligne[0] == 'G' || ligne[0] == 'C')
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
void Lecture_Fichier_Sequences(FILE* fp, TTabSeq** tab_seq)
{
	int nb_seq = 0;
	int longueur_ligne;
    	char ligne[500]; /* une chaine de 500 caractères */

	/* remettre le curseur au début du fichier texte */
	fseek(fp, 0, SEEK_SET);

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
    		if(ligne[0]=='>') /*Si la ligne debute par '>' on est sur un identifiant que l'on doit recupérer */
		{
			tab_seq[nb_seq]->identifiant_seq=Recuperer_ligne(ligne); /* on introduit l'identifiant correspondant a la sequence courante */
		}
		else
		{
			tab_seq[nb_seq]->sequence=Recuperer_ligne(ligne); /* On introduit la séquence courrante */
			nb_seq++; /* On incrémente le compteur pour passer à la séquence suivante */
		}
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


void AfficheTTabSeq(TTabSeq** tab_seq, int nb_seq)
{
	for (int i = 0; i < nb_seq; ++i)
	{
		printf(">%s \n", tab_seq[i]->identifiant_seq);
		printf("%s\n", tab_seq[i]->sequence);
	}
}

TDict* AlloueTDict()
{
	TDict* dict_t1 = (TDict*)malloc(sizeof(TDict));
	if(dict_t1 == NULL)
	{
		printf("Erreur d'allocation de mémoire de AlloueTTabSeq !!\n");
	}
	else
	{
		dict_t1->motif=NULL;
		dict_t1->next=NULL;
		dict_t1->prem_seq=NULL;
	}
	return dict_t1;
}

void Creer_Dictionnaire_T1(TTabSeq** tab_seq, TDict* dict_t1, int nb_seq)
{
	int i;
	for(i=0;i<=nb_seq;i++)
	{
		
	}
}
