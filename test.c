/* Découverte de motif d'occurrence */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies */
#include "structures.c"
#include "fonctions_entree_sortie.h"

/* constantes */
//#define NB_MAX_ELEM 100 

/* prototype des fonctions et procédures */
TTabSeq* AlloueTTabSeq();
char* SaisieMot();
void SaisieTTabSeq(TTabSeq* tab_seq);
void AfficheTTabSeq(TTabSeq** tab_seq, int nb_seq);

/* programme principal */
int main()
{
  
  	/* déclaration des variables */
  	int nb_seq = 4; 
  	int i;

  	TTabSeq* tab_seq[nb_seq];
	
	for (i = 0; i < nb_seq; i++)
	{
		tab_seq[i] = AlloueTTabSeq();
		SaisieTTabSeq(tab_seq[i]);
	}

	AfficheTTabSeq(tab_seq, nb_seq);

	return 0;
}

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
