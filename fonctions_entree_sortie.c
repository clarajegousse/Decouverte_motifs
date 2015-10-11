/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* librairies */
#include "structures.c"

char* Saisie_Mot()
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
	return mot; /* On retourne le pointeur qui nous dirige vers la premiere lettre du mot */
}

char* Recuperer_Ligne(char* ligne)
{
	char* mot = NULL;
	int i = 0;
	
	mot=(char*)malloc(strlen(ligne)* sizeof(char)); // allocation de mémoire
	
	if(mot==NULL)
	{
		printf("Erreur d'allocation de mémoire pour Recuperer_Ligne.\n");
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

char* Recuperer_Char(char carac)
{
	char* caract_voulu = NULL;
	
	caract_voulu=(char*)malloc(2*sizeof(char)); // allocation de mémoire
	
	if(caract_voulu==NULL)
	{
		printf("Erreur d'allocation de mémoire pour Recuperer_Char.\n");
	}
	else
	{
		caract_voulu[0]=carac;
	}
	return caract_voulu; // On retourne le pointeur qui nous dirige vers la premiere lettre du mot
}

FILE* Ouvrir_Fichier()
{
	char* nom_fichier;
	FILE* fp;

	puts("Veuillez spécifier un fichier de séquences nucléotidiques (format fasta):");
	nom_fichier=Saisie_Mot();

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
    		
    		if(ligne[0]=='>') /* si la ligne debute par '>' on est sur un identifiant que l'on doit recupérer */
		{
			tab_seq[nb_seq]->identifiant_seq=Recuperer_Ligne(ligne); /* on introduit l'identifiant correspondant a la sequence courante */
		}
		else
		{
			tab_seq[nb_seq]->sequence=Recuperer_Ligne(ligne); /* On introduit la séquence courrante */
			nb_seq++; /* On incrémente le compteur pour passer à la séquence suivante */
		}
	}
    
}

TTabSeq* Alloue_TTabSeq()
{
	TTabSeq* tab_seq = (TTabSeq*)malloc(sizeof(TTabSeq));
	if(tab_seq == NULL)
	{
		printf("Erreur d'allocation de mémoire de AlloueTTabSeq !!\n");
	}
	else
	{
		tab_seq->sequence = NULL;
		tab_seq->identifiant_seq = NULL;
	}
	return tab_seq;
}


void Affiche_TTabSeq(TTabSeq** tab_seq, int nb_seq)
{
	for (int i = 0; i < nb_seq; ++i)
	{
		printf("%s \n", tab_seq[i]->identifiant_seq);
		printf("%s\n", tab_seq[i]->sequence);
	}
}

TMotif* Alloue_TMotif()
{
	TMotif* m = (TMotif*)malloc(sizeof(TMotif));
	if(m == NULL)
	{
		printf("Erreur d'allocation de mémoire de Alloue_TMotif !!\n");
	}
	else
	{
		m->motif = NULL;
		m->nb_seq_quorum = 0;
		m->next = NULL;
		m->prem_seq = NULL;
	}
	return m;
}

TSequence* Alloue_TSequence()
{
	TSequence* seq = (TSequence*)malloc(sizeof(TSequence));
	if(seq == NULL)
	{
		printf("Erreur d'allocation de mémoire de Alloue_TSequence !!\n");
	}
	else
	{
		seq->num_seq = 0;
		seq->next = NULL;
		seq->prem_occ = NULL;
	}
	return seq;
}

TOccurrence* Alloue_TOccurrence()
{
	TOccurrence* occ = (TOccurrence*)malloc(sizeof(TOccurrence));
	if(occ == NULL)
	{
		printf("Erreur d'allocation de mémoire de Alloue_TOccurrence !!\n");
	}
	else
	{
		occ->pos = 0;
		occ->nb_ins = 0;
		occ->nb_del = 0;
		occ->nb_sub = 0;
		occ->last = 0;
		occ->next = NULL;
	}
	return occ;
}

void Affiche_Dictionnaire_Motifs(TMotif* tete_motif)
{
	puts("AFFICHAGE DICTIONNAIRE DE MOTIFS");
	TMotif* motif_courant = tete_motif;

	while( motif_courant->next != NULL)
	{
		printf("motif: %s ;\tnb_seq_quorum: %d.\n", motif_courant->motif, motif_courant->nb_seq_quorum);
		motif_courant = motif_courant->next;
	}
}

TMotif* Creer_Un_Motif_T1(char* chaine, int longueur_motif) 
{
	char buffer = chaine[0]; /* type char uniquement dans le cas des motif de taille 1, sinon type char* */
	TMotif* nouveau_motif;
	
	nouveau_motif = Alloue_TMotif();
	nouveau_motif->motif = (char*)malloc(sizeof(char)*longueur_motif);
	
	/* on copie le motif */
	strcpy(nouveau_motif->motif, "");
	strcpy(nouveau_motif->motif, &buffer);

	nouveau_motif->nb_seq_quorum++;
	nouveau_motif->next = NULL;

	return nouveau_motif;
}

void Creer_Dictionnaire_Motifs_T1(TTabSeq** tab_seq, int nb_seq)
{
	/* on crée les variables */

	int i, j; /* indices */
	int longueur_motif = 1; /* cas des motifs de taille 1 */
	int longueur_seq;

	TMotif* tete_motif; /* on déclare une tête de liste */
	TMotif* motif_courant; /* on déclare le motif courant */

	TMotif* nouveau_motif; /* on déclare un nouveau motif */

	for (i = 0; i < nb_seq; i++)
	{
		/* on trouve la longueur de la sequence i */
		longueur_seq = strlen(tab_seq[i]->sequence);

		/* pour tout les bases j de la sequences */
		for (j = 0; j < longueur_seq; j++)
		{
			/* s'il n'y a pas de motif dans le dictionaire */
			if (tete_motif == NULL)
			{
				/* on crée le premier motif de la liste : la tête de liste */
				tete_motif = Creer_Un_Motif_T1(&tab_seq[i]->sequence[j], longueur_motif);
			}
			else
			{
				/* on commence par la tete de la liste */
				motif_courant = tete_motif;
				
				/* TODO: ajouter motif seulement s'il n'est pas déjà dans la liste */
				
				/* tant qu'on est pas à la fin de la liste */
				while ( motif_courant->next != NULL )
				{
					/* on avance dans la liste */
					motif_courant = motif_courant->next;
				} /* quand on arrive à la fin de la liste */

				/* on crée un nouveau motif */
				nouveau_motif = Creer_Un_Motif_T1(&tab_seq[i]->sequence[j], longueur_motif);

				/* on crée le lien entre le motif courant et le nouveau motif */
				motif_courant->next = nouveau_motif;	
			}
		}
	}
	Affiche_Dictionnaire_Motifs(tete_motif);
}