/* Découverte de motif d'occurrence */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies */
#include "structures.c"
#include "fonctions_entree_sortie.h"

/* constantes */
//#define nom_fichier "sequences.fasta"

/* programme principal */
int main()
{
	printf("\t===================================\n");
  
  	/* déclaration des variables */
  	int i;
  	int nb_seq; 
	FILE* fp;
	
	fp = Ouvrir_Fichier();
	nb_seq = Compte_Nb_Seq(fp);
	printf("\t===================================\n");

	TTabSeq* tab_seq[nb_seq];
	
	for (i = 0; i < nb_seq; i++)
	{
		tab_seq[i] = Alloue_TTabSeq();
	}
	
	Lecture_Fichier_Sequences(fp, tab_seq);
	/* AfficheTTabSeq(tab_seq, nb_seq); */

	Creer_Dictionnaire_Motifs_T1(tab_seq, nb_seq);

	printf("\t===================================\n");
	
	/* fermeture du fichier */
	fclose(fp);

	return 0;
}
