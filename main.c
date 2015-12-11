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
  	/* déclaration des variables */
  	int i;
  	int nb_seq; 
	int nb_erreurs;
	int l_max;
	int choix;
	int menu1, menu2;
	float quorum;
	char* motif_choisi;
	FILE* fp;
	TDict dict; 
	dict.tete_motif = NULL;
	menu1 = 1;
	while(menu1 == 1)
	{
		printf("\t==========================================================================================\n");
		printf("\t=DECOUVERTE EXACTE DE MOTIF APPROCHES AVEC ERREURS DE SUBSTITUTION, INSERTION ET DELETION=\n");
		printf("\t==========================================================================================\n");
		fp = Ouvrir_Fichier();
		nb_seq = Compte_Nb_Seq(fp);
		printf("le nombre de sequences est : %d\n", nb_seq);
		TTabSeq* tab_seq[nb_seq];
		for (i = 0; i < nb_seq; i++)
		{
			tab_seq[i] = Alloue_TTabSeq();
		}
		Lecture_Fichier_Sequences(fp, tab_seq);
		/* fermeture du fichier */
		fclose(fp);
		menu2 = 1;
		printf("\t============================================================\n");
		puts("veuillez préciser la taille maximale du motif");
		scanf("%d", &l_max);
		while(l_max < 0)
		{
			puts("Taille de motif non permise, veuillez en selectionner une autre.");
			scanf("%d", &l_max);
		}
		printf("\t============================================================\n");
		puts("veuillez préciser un nombre d'erreurs maximal");
		scanf("%d", &nb_erreurs);
		while(nb_erreurs < 0)
		{
			puts("Nombre d'erreurs non permis, veuillez en selectionner un autre.");
			scanf("%d", &nb_erreurs);
		}
		printf("\t============================================================\n");
		puts("Selectionnez le quorum désiré (doit etre compris entre 0 et 100)");
		scanf("%f", &quorum);
		while((quorum < 0) || (quorum > 1))
		{
			puts("Quorum sélectionné incorrect, veuillez spécifiez un réel entre 0 et 1 (ratio).");
			scanf("%d", &quorum);
		}
		printf("\t============================================================\n");
		puts("Debut de la procédure de recherche de motifs...");
		printf("Taille de motif recherché : %d.\n", l_max);
		printf("Nombre d'erreurs maximum autorisées : %d.\n", nb_erreurs);
		printf("Le quorum : %f.\n", quorum);
		Decouvert_Exacte_Motif_Occurrences_Subst_Ins_Del(&dict, tab_seq, nb_seq, l_max, nb_erreurs, quorum);
		puts("Procédure achevée avec succès.");
		printf("\t============================================================\n");
		Affiche_Dictionnaire_Motifs(dict.tete_motif, nb_seq);
		printf("\t============================================================\n");
		do
		{
			puts("1: Consulter les occurrences d'un motif donné.");
			puts("2: Effectuer une nouvelle recherche.");
			puts("3: Quitter le programme.");
			scanf("%d", &choix);
			switch(choix)
			{
				case 1:
					puts("veuillez rentrer un motif à consultez dans la liste suivante:");
					Affiche_Dictionnaire_Motifs(dict.tete_motif, nb_seq);
					motif_choisi = Saisie_Mot();
					puts("++++++++++++++++++++++++++++++++++++\n");
					Affiche_Occurrences_D_Un_Motif(dict.tete_motif, motif_choisi);
					// TODO : Affichage des occurrences selon un motif donné
				break;
				case 2: 
					Destruction_dictionnaire(&dict.tete_motif);
					dict.tete_motif = NULL;
					menu2 = 0;
				break;
				case 3: 
					puts("Fin du programme...");
					menu2 = 0;
					menu1 = 0;
				break;
				default :
					puts("Mauvaise option selectionnée veuillez en spécifier une nouvelle.");
			}
		}while(menu2 == 1);
		
	}
	return 0;
}
