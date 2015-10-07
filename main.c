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
int main(){
  
  	/* déclaration des variables */
  	int i;
  	int nb_seq; 
  	
	FILE* fp = Ouvrir_Fichier();

	nb_seq = Compte_Nb_Seq(fp);
	Lecture_Fichier_Sequences(fp);

	/*TTabSeq* tab_seq[nb_seq];
	
	for (i = 0; i < nb_seq; i++)
	{
		tab_seq[i] = AlloueTTabSeq();
		SaisieTTabSeq(tab_seq[i]);
	}

	AfficheTTabSeq(tab_seq, nb_seq);*/

	printf("\t===================================\n");
	/* TODO: fermeture du fichier */

	return 0;
}
