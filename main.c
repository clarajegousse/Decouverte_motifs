/* Découverte de motif d'occurrence */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* librairies */
#include "structures.c"
#include "fonctions.h"

/* programme principal */
int main()
{
	printf("\t===================================\n");
  
  	/* déclaration des variables */
  	int i;
  	int nb_seq; 
	int nb_erreurs;
	int l_max;
	float quorum;
	FILE* fp;
	TDict dict_vide; 
	dict_vide.tete_motif = NULL;
	fp = Ouvrir_Fichier();
	nb_seq = Compte_Nb_Seq(fp);
	printf("le nombre de sequences est : %d\n", nb_seq);
	printf("\t===================================\n");
	TTabSeq* tab_seq[nb_seq];
	for (i = 0; i < nb_seq; i++)
	{
		tab_seq[i] = Alloue_TTabSeq();
	}
	Lecture_Fichier_Sequences(fp, tab_seq);
	puts("veuillez préciser un nombre d'erreurs maximal");
	scanf("%d", &nb_erreurs);
	puts("veuillez préciser la taille maximale du motif");
	scanf("%d", &l_max);
	puts("Selectionnez le quorum désiré (doit etre compris entre 0 et 100)");
	scanf("%f", &quorum);
	//Creer_Dictionnaire_Motifs(dict_t1, tab_seq, nb_seq);
	//Creer_Dictionnaire_Motif_vide(&dict_vide.tete_motif, tab_seq, nb_seq, nb_erreurs);
	Decouvert_Exacte_Motif_Occurrences_Subst_Ins_Del( tab_seq, nb_seq, l_max, nb_erreurs, quorum);
	printf("\t===================================\n");
	
	/* fermeture du fichier */
	fclose(fp);

	return 0;
}
