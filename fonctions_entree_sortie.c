/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* librairies */
#include "structures.c"


/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

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
	return mot; 
}

/*------------------------------------------------------------------------------------------------------------*/

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
	if(caract_voulu[1])
	{
		caract_voulu[1] = '\0';
	}
	return caract_voulu; // On retourne le pointeur qui nous dirige vers la premiere lettre du mot
}

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

void Affiche_TTabSeq(TTabSeq** tab_seq, int nb_seq)
{
	int i;
	for (i = 0; i < nb_seq; ++i)
	{
		printf("%s \n", tab_seq[i]->identifiant_seq);
		printf("%s\n", tab_seq[i]->sequence);
	}
}

/*------------------------------------------------------------------------------------------------------------*/

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
		m->tete_seq = NULL;
	}
	return m;
}

/*------------------------------------------------------------------------------------------------------------*/

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
		seq->tete_occ = NULL;
	}
	return seq;
}

/*------------------------------------------------------------------------------------------------------------*/

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

/*------------------------------------------------------------------------------------------------------------*/

void Affiche_Dictionnaire_Motifs(TPMotif tete_motif)
{
	puts("AFFICHAGE DICTIONNAIRE DE MOTIFS");
	TPMotif motif_courant = Alloue_TMotif();
	motif_courant = tete_motif;

	while( motif_courant->next != NULL)
	{
		printf("motif: %s ;\tnb_seq_quorum: %d.\n", motif_courant->motif, motif_courant->nb_seq_quorum);
		motif_courant = motif_courant->next;
	}
	printf("motif: %s ;\tnb_seq_quorum: %d.\n", motif_courant->motif, motif_courant->nb_seq_quorum);
}

/*------------------------------------------------------------------------------------------------------------*/

bool existe_motif(TPMotif tete_motif, char* chaine, TPMotif* adr_prec_motif)
{
	*adr_prec_motif = NULL;
	TPMotif motif_courant = tete_motif;
	if(motif_courant == NULL)
	{
		return false; /* La liste de motif est vide, donc aucun motif n'existe encore */
	}
	while(motif_courant != NULL)
	{
		if( strcmp(motif_courant->motif, chaine) == 0 )
		{
			return true; /* on a trouvé un motif qui match, le motif existe donc on renvoie true */
		}
		if( strcmp(motif_courant->motif, chaine) > 0 ) 
		{
			return false; /* le motif courant est plus grand que la chaine on n'as donc pas trouvé de motif correspondant a cette chaine */
		}
		*adr_prec_motif = motif_courant;
		motif_courant = motif_courant->next;
	}
	return false; /* On n'est sorti ens sortie de boucle sans trouver de match entre un motif existant et la chaine que l'on a donc le motif n'existe pas */
}

/*------------------------------------------------------------------------------------------------------------*/

bool existe_sequence(TPSequence tete_seq, int seq, TPSequence* adr_prec_seq)
{
	*adr_prec_seq = NULL;
	TPSequence seq_courante = tete_seq;// = Alloue_TSequence();
	//seq_courante = tete_seq;
	if(seq_courante == NULL)
	{
		return false;
	}
	while(seq_courante != NULL)
	{
		if( seq == seq_courante->num_seq )
		{
			return true;
		}
		if( seq < seq_courante->num_seq )
		{
			return false;
		}
		*adr_prec_seq = seq_courante;
		seq_courante = seq_courante->next;
	}
	return false;
}

/*------------------------------------------------------------------------------------------------------------*/

bool existe_occ(TOccurrence* tete_occ, int occ, TPOccurrence* adr_prec_occ)
{
	*adr_prec_occ = NULL;
	TOccurrence* occ_courante = tete_occ;
	while(occ_courante != NULL)
	{
		if( occ == occ_courante->pos )
		{
			return true;
		}
		if( occ > occ_courante->pos )
		{
			return false;
		}
		*adr_prec_occ = occ_courante;
		occ_courante = occ_courante->next;
	}
	return false;
}

/*------------------------------------------------------------------------------------------------------------*/

void deplace_prec_occ(TPOccurrence tete_occ, TPOccurrence* adr_prec_occ)
{
	*adr_prec_occ = NULL;
	TOccurrence* occ_courante = tete_occ;
	while(occ_courante != NULL)
	{
		*adr_prec_occ = occ_courante;
		occ_courante = occ_courante->next;
	}
}

/*------------------------------------------------------------------------------------------------------------*/

bool existe(TDict dict, char* chaine, int seq, int occ, TPMotif* adr_prec_motif, TPSequence* adr_prec_seq, TPOccurrence* adr_prec_occ, bool* adr_presence_sequence, bool* adr_presence_motif)
{
	
	*adr_presence_motif = false;
	*adr_presence_sequence = false;
	TPMotif motif_courant = Alloue_TMotif();
	TPSequence sequence_courante = Alloue_TSequence();
	if(existe_motif(dict.tete_motif, chaine, adr_prec_motif))
	{
		*adr_presence_motif = true; /* Le motif que l'on teste est deja présent dans le dictionnaire */
		if(*adr_prec_motif == NULL)
		{
			motif_courant = dict.tete_motif;
		}
		else
		{
			motif_courant = (*adr_prec_motif)->next;
		}
		if(existe_sequence(motif_courant->tete_seq, seq, adr_prec_seq))
		{
			*adr_presence_sequence = 1;
			if(*adr_prec_seq == NULL)
			{
				sequence_courante = motif_courant->tete_seq;
			}
			else
			{
				sequence_courante = (*adr_prec_seq)->next;
			}
			deplace_prec_occ(sequence_courante->tete_occ, adr_prec_occ);
		}
	}
	return false;
}

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Un_Motif(TPMotif* adr_tete_motif, char* chaine, TPMotif prec_motif)
{
	
	TPMotif new_motif = Alloue_TMotif();
	if (prec_motif == NULL) /* il faut inserer le nouveau motif en tete de liste */
	{
		new_motif->next = *adr_tete_motif;
		new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
		strcpy(new_motif->motif, chaine);
		new_motif->tete_seq = (TPSequence)malloc(sizeof(TSequence));
		new_motif->tete_seq = NULL;
		*adr_tete_motif = new_motif;
		return; /* on a crée le nouveau motif on quitte la procédure */
	}
	new_motif->next = prec_motif->next;
	prec_motif->next = new_motif;
	new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
	strcpy(new_motif->motif, chaine);
} /* on a crée le nouveau motif on quitte la procédure */

/*------------------------------------------------------------------------------------------------------------*/

void Inserer_Une_Sequence(TPSequence* adr_tete_seq, int nb_seq, TPSequence prec_seq)
{
	
	TPSequence new_seq = Alloue_TSequence();
	if (prec_seq == NULL)
	{
		new_seq->next = *adr_tete_seq;
		new_seq->num_seq = nb_seq;
		*adr_tete_seq = new_seq;
		return;
	}
	new_seq->next = prec_seq->next;
	prec_seq->next = new_seq;
	new_seq->num_seq = nb_seq;
}

/*------------------------------------------------------------------------------------------------------------*/

void Inserer_Une_Occurrence(TPOccurrence* adr_tete_occ, int occ, TPOccurrence prec_occ, int operation, int num_sub, int num_ins , int num_del)
{
	
	TPOccurrence new_occ = Alloue_TOccurrence();
	if (prec_occ == NULL)
	{
		new_occ->next = *adr_tete_occ;
		new_occ->pos = occ;
		switch(operation)
		{
			case 0 : /* 0 pour un match */
				new_occ->last = 0;
				new_occ->nb_ins = num_ins;
				new_occ->nb_del = num_del;
				new_occ->nb_sub = num_sub;
				break;
			case 1 : /* 1 pour une substitution */
				new_occ->last = 1;
				new_occ->nb_ins = num_ins;
				new_occ->nb_del = num_del;
				new_occ->nb_sub = num_sub+1;
				break;
			case 2 : /* 2 pour une insertion */
				new_occ->last = 2;
				new_occ->nb_ins = num_ins+1;
				new_occ->nb_del = num_del;
				new_occ->nb_sub = num_sub;
				break;
			case 3 : /* 3 pour une deletion */
				new_occ->last = 3;
				new_occ->nb_ins = num_ins;
				new_occ->nb_del = num_del+1;
				new_occ->nb_sub = num_sub;
				break;	
			default :
			puts("erreur pendant le choix du last de la procédure Inserer_Une_Occurrence");
			exit(1);
		}
		*adr_tete_occ = new_occ;
		return;
	}
	new_occ->next = prec_occ->next;
	new_occ->pos = occ;
	switch(operation)
	{
		case 0 : /* 0 pour un match */
			new_occ->last = 0;
			new_occ->nb_ins = num_ins;
			new_occ->nb_del = num_del;
			new_occ->nb_sub = num_sub;
			break;
		case 1 : /* 1 pour une substitution */
			new_occ->last = 1;
			new_occ->nb_ins = num_ins;
			new_occ->nb_del = num_del;
			new_occ->nb_sub = num_sub+1;
			break;
		case 2 : /* 2 pour une insertion */
			new_occ->last = 2;
			new_occ->nb_ins = num_ins+1;
			new_occ->nb_del = num_del;
			new_occ->nb_sub = num_sub;
			break;
		case 3 : /* 3 pour une deletion */
			new_occ->last = 3;
			new_occ->nb_ins = num_ins;
			new_occ->nb_del = num_del+1;
			new_occ->nb_sub = num_sub;
			break;	
		default :
			puts("erreur pendant le choix du last de la procédure Inserer_Une_Occurrence");
			exit(1);
	}
	prec_occ->next = new_occ;
	
}

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Nouvelle_Occurrence(TPMotif* adr_tete_motif, char* chaine, int seq , int occ, bool presence_motif, bool presence_sequence, TPMotif prec_motif, TPSequence prec_seq, TPOccurrence prec_occ, TPOccurrence occ_lu, int operation)
{
	
	TPMotif test_motif;
	if(!presence_motif) /* Si le motif n'existe pas, on doit le créer */
	{
		Creer_Un_Motif(adr_tete_motif, chaine, prec_motif);
		test_motif = *adr_tete_motif;
		prec_seq = NULL;
	}
	if(!presence_sequence)
	{
		if(prec_motif == NULL)
		{
			Inserer_Une_Sequence(&test_motif->tete_seq, seq, prec_seq);
			test_motif->nb_seq_quorum++;
		}
		else
		{
			Inserer_Une_Sequence(&prec_motif->next->tete_seq, seq, prec_seq);
			prec_motif->next->nb_seq_quorum++;
		}
		prec_occ = NULL;
	}
	if((prec_motif == NULL) && (prec_seq == NULL))
	{
		Inserer_Une_Occurrence((&test_motif->tete_seq->tete_occ), occ, prec_occ, operation, occ_lu->nb_sub, occ_lu->nb_ins, occ_lu->nb_del);	
	}
	else if ((prec_motif != NULL) && (prec_seq == NULL))
	{
		Inserer_Une_Occurrence(&prec_motif->next->tete_seq->tete_occ, occ, prec_occ, operation, occ_lu->nb_sub, occ_lu->nb_ins, occ_lu->nb_del);
	}
	else
	{
		Inserer_Une_Occurrence(&prec_seq->next->tete_occ, occ, prec_occ, operation, occ_lu->nb_sub, occ_lu->nb_ins, occ_lu->nb_del);
	}
}

/*------------------------------------------------------------------------------------------------------------*/

int minimum(int a, int b)
{
	if (a < b)
	{
		return a;
	}
	else
	{
		return b;
	}
}

/*------------------------------------------------------------------------------------------------------------*/

void Free_liste_occurrence(TPOccurrence* adr_tete_occ)
{
	
	TPOccurrence occurrence_a_detruire;
	occurrence_a_detruire = *adr_tete_occ;
	TPOccurrence next;
	while(occurrence_a_detruire != NULL)
	{
		next = occurrence_a_detruire->next;
		free(occurrence_a_detruire);
		occurrence_a_detruire = next;
	}
	*adr_tete_occ = NULL;
}

/*------------------------------------------------------------------------------------------------------------*/

void Free_liste_sequence(TPSequence* adr_tete_seq)
{
	
	TPSequence sequence_a_detruire;
	sequence_a_detruire = *adr_tete_seq;
	TPSequence next;
	while(sequence_a_detruire != NULL)
	{
		Free_liste_occurrence(&sequence_a_detruire->tete_occ);
		next = sequence_a_detruire->next;
		free(sequence_a_detruire);
		sequence_a_detruire = next;
	}
	*adr_tete_seq = NULL;
}

/*------------------------------------------------------------------------------------------------------------*/

void Destruction_dictionnaire(TPMotif* adr_tete_motif)
{
	
	TPMotif motif_a_detruire;
	motif_a_detruire = *adr_tete_motif;
	TPMotif next;
	while(motif_a_detruire != NULL)
	{
		Free_liste_sequence(&motif_a_detruire->tete_seq);
		next = motif_a_detruire->next;
		free(motif_a_detruire);
		motif_a_detruire = next;
	}
	*adr_tete_motif = NULL;
}
	

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Dictionnaire_Motif_vide(TPMotif* adr_tete_motif, TTabSeq** tab_seq, int nb_seq, int nb_erreurs)
{
	puts("Création du dictionnaire des motifs de taille vide...");
	/* Déclaration des variables */
	
	int i, j, k; /* indices */
	int longueur_seq;
	int nb_max_insertions;
	TPMotif motif_vide = Alloue_TMotif();
	motif_vide->motif = (char*)malloc(2*sizeof(char));
	strcpy(motif_vide->motif, "");
	motif_vide->nb_seq_quorum = 0;
	motif_vide->next = *adr_tete_motif;
	*adr_tete_motif = motif_vide;
	TPSequence prec_seq = Alloue_TSequence();
	TPSequence test_seq = Alloue_TSequence();
	TPOccurrence prec_occ = Alloue_TOccurrence();
	TPOccurrence test_occ = Alloue_TOccurrence();
	for(i = 0; i < nb_seq; i++)
	{
		if(!existe_sequence(motif_vide->tete_seq, i+1, &prec_seq))
		{
			Inserer_Une_Sequence(&motif_vide->tete_seq, i+1, prec_seq);
			motif_vide->nb_seq_quorum++;
		}
		longueur_seq = strlen(tab_seq[i]->sequence);
		for(j = 0; j < longueur_seq; j++)
		{
			if(prec_seq == NULL) // cas ou la premiere sequence vient tout juste d'etre inserée
			{
				deplace_prec_occ(motif_vide->tete_seq->tete_occ, &prec_occ);
				Inserer_Une_Occurrence(&motif_vide->tete_seq->tete_occ, j+1, prec_occ,0 , 0, 0, 0);
				nb_max_insertions = minimum(nb_erreurs, longueur_seq-(j+1));
				for(k = 1; k <= nb_max_insertions; k++)
				{
					deplace_prec_occ(motif_vide->tete_seq->tete_occ, &prec_occ);
					Inserer_Une_Occurrence(&motif_vide->tete_seq->tete_occ, j+1, prec_occ,2 , 0, k-1, 0); /* k-1 pour éviter de compter une insertion de trop lors de la création du motif vide */
				}
			}
			else
			{
				deplace_prec_occ(prec_seq->next->tete_occ, &prec_occ);
				Inserer_Une_Occurrence(&prec_seq->next->tete_occ, j+1, prec_occ,0 , 0, 0, 0);
				nb_max_insertions = minimum(nb_erreurs, longueur_seq-(j+1));
				for(k = 1; k <= nb_max_insertions; k++)
				{
					deplace_prec_occ(prec_seq->next->tete_occ, &prec_occ);
					Inserer_Une_Occurrence(&prec_seq->next->tete_occ, j+1, prec_occ,2 , 0, k-1, 0);
				}
			}
		}
	}
	/*test_seq = motif_vide->tete_seq;
	while(test_seq != NULL)
	{
		puts("================================================================");
		printf("la sequences insérée est la numero : %d\n", test_seq->num_seq);
		test_occ = test_seq->tete_occ;
		while(test_occ != NULL)
		{
			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++");
			printf("l'occurrence insérée est a la position : %d\n", test_occ->pos);
			printf("l'operation effectuée est : %d\n", test_occ->last);
			printf("le nombre d'insertion est de : %d\n", test_occ->nb_ins);
			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++");
			test_occ = test_occ->next;
		}
		test_seq = test_seq->next;
		puts("================================================================");
	}*/
	puts("Dictionnaire des motifs de taille vide crée...");
}

/*------------------------------------------------------------------------------------------------------------*/

void Decouvert_Exacte_Motif_Occurrences_Subst_Ins_Del(TTabSeq** tab_seq, int nb_seq, int taille_max_motif, int nb_max_erreurs, float quorum)
{
	
	/* Déclaration des variables */
	
	int i,k,l, cpt;
	int pos_car_droite;
	int nb_erreurs_actuel;
	int nb_max_insertion;
	int nb_caracteres_disponibles_a_droite;
	char* base_courante;
	char* motif_a_inserer;
	char* precedent_motif;
	char alphabet[4] = {'A','C','G','T'};
	TDict dict_courant;
	TDict dict_a_construire;
	dict_a_construire.tete_motif = NULL;
	dict_courant.tete_motif = NULL;
	TPMotif motif_lu = Alloue_TMotif();
	TPMotif prec_motif;
	TPMotif ancien_motif = Alloue_TMotif();
	TPMotif motif_a_supprimer = Alloue_TMotif();
	TPMotif motif_a_afficher;
	TPSequence sequence_a_afficher;
	TPOccurrence occ_a_afficher;
	TPSequence sequence_lu = Alloue_TSequence();
	TPSequence prec_seq;
	TPOccurrence occurrence_lu = Alloue_TOccurrence();
	TPOccurrence prec_occ;
	bool presence_motif;
	bool presence_sequence;
	bool match_possible;
	
	/* Construction du dictionnaire des motifs de taille vide */
	Creer_Dictionnaire_Motif_vide(&dict_courant.tete_motif, tab_seq, nb_seq, nb_max_erreurs);
	/* Debut de la boucle allant de la taille de motif 0 a la taille du motif final désiré */
	for(i = 0; i < taille_max_motif; i++)
	{
		//printf("Le dictionnaire qui est lu comporte des motifs de taille : %d\n", i);
		motif_lu = dict_courant.tete_motif;
		
		/* On parcours les motifs contenus dans le dictionnaire i-1 */
		while(motif_lu != NULL)
		{
			sequence_lu = motif_lu->tete_seq;
			/* Parcours des sequences correspondants au motif lu actuellement */
			while(sequence_lu != NULL)
			{
				occurrence_lu = sequence_lu->tete_occ;
				/* Parcours des occurrences correspondantes a la sequence lue actuellement */
				while(occurrence_lu != NULL)
				{
					/* Calcul de la position du caractère a droite */
					
					pos_car_droite = occurrence_lu->pos + i + occurrence_lu->nb_ins - occurrence_lu->nb_del;
					if(pos_car_droite == strlen(tab_seq[sequence_lu->num_seq-1]->sequence))
					/* sequence_lu->num_seq-1 = indice de la séquence considérée en C */
					{
						 /* On est à la fin de la séquence on met la valeur de -1 pour indiquer plus tard que l'on ne peut pas effectuer d'operation */
						pos_car_droite = -1;
					}
					
					/* Calcul du nombre d'erreurs deja prises en compte pour l'occurrence que l'on est en train de lire */
					
					nb_erreurs_actuel = occurrence_lu->nb_sub + occurrence_lu->nb_ins + occurrence_lu->nb_del;
					
					/* Cas de la substitution */
					switch(occurrence_lu->last)
					{
						case 0:
						case 1:
							if((pos_car_droite != -1) && (nb_erreurs_actuel < nb_max_erreurs))
							{
								for(k = 0; k < 4; k++)
								{
									if(alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite])
									{
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, 1); /* dernier paramètre pour préciser l'operation que l'on effectue */
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
						break;
						case 2: 
							if((pos_car_droite != -1) && (nb_erreurs_actuel < nb_max_erreurs))
							{
								for(k = 0; k < 4; k++)
								{
									if((alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite]) && (alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1]))
									{
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, 1);
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
						break;
					}
					
					/* Cas de la deletion? */
					switch(occurrence_lu->last)
					{
						case 0 :
						case 1 :
							if(nb_erreurs_actuel < nb_max_erreurs)
							{
								for(k = 0; k < 4; k++)
								{
									if(alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1])
									{
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, 3);
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
						break;
						case 3 :
							if(nb_erreurs_actuel < nb_max_erreurs)
							{
								for(k = 0; k < 4; k++)
								{
									if(alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite])
									{
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, 3);
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
						break;
					}
					
					/* Cas du match? */
					match_possible = true;
					if(pos_car_droite == -1)
					{
						match_possible = false;
					}
					if(!match_possible)
					{
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					if((occurrence_lu->last == 2) && (tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite] == tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1]))
					{					
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					base_courante = Recuperer_Char(tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1]);
					precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
					strcpy(precedent_motif, motif_lu->motif);
					motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
					motif_a_inserer = strcat(precedent_motif, base_courante);
					if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
					{
						Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, 0);
					}
					else
					{
						puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
					}
					/* Série d'insertions? */
					
					if(nb_erreurs_actuel == nb_max_erreurs)
					{
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					pos_car_droite++;
					if(pos_car_droite == strlen(tab_seq[sequence_lu->num_seq-1]->sequence)) /* sequence_lu->num_seq-1 = indice de la séquence considérée en C */
					{
						pos_car_droite = -1; /* On est à la fin de la séquence il n'y a plus rien a faire */
					}
					nb_max_insertion = nb_max_erreurs - nb_erreurs_actuel;
					if(pos_car_droite == -1)
					{
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					nb_caracteres_disponibles_a_droite = strlen(tab_seq[sequence_lu->num_seq-1]->sequence)-pos_car_droite-1;
					nb_max_insertion=minimum(nb_max_insertion, nb_caracteres_disponibles_a_droite);
					for(l = 1; l <= nb_max_insertion; l++)
					{
						base_courante = Recuperer_Char(tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite]);
						precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
						strcpy(precedent_motif, motif_lu->motif);
						motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
						motif_a_inserer = strcat(precedent_motif, base_courante);
						if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
						{
							Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, 2);
						}
						else
						{
							puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
						}
						pos_car_droite++;
					}
					occurrence_lu = occurrence_lu->next;
				}
				sequence_lu = sequence_lu->next;
			}
			motif_lu = motif_lu->next;
		}
				
		/* Destruction du dictionnaire de taille i-1 */
		
		Destruction_dictionnaire(&dict_courant.tete_motif);
		dict_courant.tete_motif = dict_a_construire.tete_motif;
		dict_a_construire.tete_motif = NULL;
		
		/* On regarde pour chaque motif si la contrainte du quorum est respectée, si ce n'est pas le cas, les occurrences, séquences et ce motif sont supprimés du dictionnaire */
		//puts("Verification de la contrainte du quorum");
		motif_lu = dict_courant.tete_motif;
		ancien_motif = dict_courant.tete_motif;
		cpt = 0;
		while(motif_lu != NULL)
		{
			if((motif_lu->nb_seq_quorum/nb_seq) < quorum)
			{
				ancien_motif->next = motif_lu->next;
				motif_a_supprimer = motif_lu;
				if( cpt == 0)
				{
					dict_courant.tete_motif = ancien_motif->next;
				}
				motif_lu = ancien_motif->next;
				Free_liste_sequence(&motif_a_supprimer->tete_seq);
				free(motif_a_supprimer);
				continue;
			}
			ancien_motif = motif_lu;
			motif_lu = motif_lu->next;
		}
	}
	motif_a_afficher = dict_courant.tete_motif;
	while(motif_a_afficher != NULL)
	{
		puts("================================================================");
		printf("Premier motif trouvé : %s\n", motif_a_afficher->motif);
		printf("Quorum de ce motif : %f\n",(motif_a_afficher->nb_seq_quorum/nb_seq));
		sequence_a_afficher = motif_a_afficher->tete_seq;
		while(sequence_a_afficher != NULL)
		{
			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
			printf("la sequences insérée est la numero : %d\n", sequence_a_afficher->num_seq);
			occ_a_afficher = sequence_a_afficher->tete_occ;
			while(occ_a_afficher != NULL)
			{
				puts("------------------------------------------------------");
				printf("l'occurrence insérée est a la position : %d\n", occ_a_afficher->pos);
				printf("l'operation effectuée est : %d\n", occ_a_afficher->last);
				printf("le nombre d'insertion est de : %d\n", occ_a_afficher->nb_ins);
				printf("Le nombre de substitution est de  : %d\n", occ_a_afficher->nb_sub);
				printf("Le nombre de deletion est de  : %d\n", occ_a_afficher->nb_del);
				puts("------------------------------------------------------");
				occ_a_afficher = occ_a_afficher->next;
			}
			sequence_a_afficher = sequence_a_afficher->next;
			puts("++++++++++++++++++++++++++++++++++++++++++++++++++++++");
		}
		motif_a_afficher = motif_a_afficher->next;
		puts("================================================================");
	}
}

/*------------------------------------------------------------------------------------------------------------*/


