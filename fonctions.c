/* Fonctions de gestion d'entrée et sortie */

/* librairies standards */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* librairies */
#include "structures.c"

/* Definition des constantes */
#define MATCH 0
#define SUBST 1
#define INS 2
#define DEL 3

	/*---------------------------------------------------*/
	/*---FONCTIONS ET PROCEDURES DE LECTURE DE FICHIER---*/
	/*---------------------------------------------------*/

/*---Fonctions de saisie utilisateur pour le nom du fichier de séquences---*/
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

/*-------------------------------------*/

/*--Fonction qui va récupérer chaque ligne du fichier de séquences---*/
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

/*-------------------------------------*/

/*---Fonction qui permet de récupérer un caractère et de le transformer en chaine de caractères---*/
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

/*-------------------------------------*/

/*---Fonction de lecture de fichier---*/
FILE* Ouvrir_Fichier()
{
	char* nom_fichier;
	FILE* fp;
	puts("Veuillez spécifier un fichier de séquences nucléotidiques (format fasta):");
	nom_fichier=Saisie_Mot();
	while((fp = fopen(nom_fichier, "r")) == NULL)
	{
			puts("Fichier inexistant ou droits insuffisants,");
			puts("Veuillez spécifier un nouveau nom de fichier de séquences nucléotidiques (format fasta):");
			nom_fichier=Saisie_Mot();
	}
	return fp;
}

/*-------------------------------------*/

/*---Fonction qui va renvoyer le nombre de séquences contenues dans le fichier---*/
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

/*-------------------------------------*/

/*---Fonction qui va lie le fichier ligne par ligne et récuperer les informations contenues---*/
void Lecture_Fichier_Sequences(FILE* fp, TTabSeq** tab_seq)
{
	int nb_seq = 0;
	int longueur_ligne;
    char ligne[500]; /* une chaine de 500 caractères max */
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
	
	/*---------------------------------------------------------------------------*/
	/*---PROCEDURE DE SAUVEGARDE DES RESULTATS DANS UN FICHIER TEXTE---*/
	/*---------------------------------------------------------------------------*/

/*---Fonction qui permet la sauvegarde dans un fichier texte des motifs contenus dans le dictionnaire final---*/
void Sauvegarde_Dictionnaire_Motifs(TPMotif tete_motif, int nb_seq)
{
	TPMotif motif_courant;
	motif_courant = tete_motif;
	FILE* f = fopen("dictionnaire_de_motifs.txt", "w");
	if (f == NULL)
	{
	    printf("Error opening file!\n");
	    exit(1);
	}
	
	fprintf(f, "DICTIONNAIRE DE MOTIFS\n");

	while( motif_courant != NULL)
	{
		fprintf(f, "motif: %s ;\tnb_seq_quorum: %f.\n", motif_courant->motif, (motif_courant->nb_seq_quorum/nb_seq));
		motif_courant = motif_courant->next;
	}

	fclose(f);
}

/*-------------------------------------*/

	/*-----------------------------------------------------*/
	/*---FONCTION NON SPECIFIQUE A LA RECHERCHE DE MOTIF---*/
	/*-----------------------------------------------------*/

/*---Fonction qui compare deux entier et renvoie le minimum---*/	
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

/*-------------------------------------*/
	
	/*------------------------------------*/
	/*---FONCTIONS D'ALLOCATION MEMOIRE---*/
	/*------------------------------------*/

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

/*-------------------------------------*/

TPMotif Alloue_TMotif()
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

/*-------------------------------------*/

TPSequence Alloue_TSequence()
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

/*-------------------------------------*/

TPOccurrence Alloue_TOccurrence()
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

	/*---------------------------*/
	/*---PROCEDURES D'AFFICHAGE---*/
	/*---------------------------*/

/*---Fonction qui permet l'affichage des motifs contenus dans le dictionnaire final---*/
void Affiche_Dictionnaire_Motifs(TPMotif tete_motif, int nb_seq)
{
	puts("AFFICHAGE DICTIONNAIRE DE MOTIFS");
	TPMotif motif_courant;
	motif_courant = tete_motif;

	while( motif_courant != NULL)
	{
		printf("motif: %s ;\tnb_seq_quorum: %f.\n", motif_courant->motif, (motif_courant->nb_seq_quorum/nb_seq));
		motif_courant = motif_courant->next;
	}
}

/*-------------------------------------*/

/*---Fonctions d'affichage des occurrences d'un motif sélectionné---*/
void Affiche_Occurrences_D_Un_Motif(TPMotif tete_motif, char* motif_recherche)
{
	TPMotif motif_lu = tete_motif;
	TPSequence sequence_lu;
	TPOccurrence occ_lu;
	bool trouve = false;
	while(motif_lu != NULL)
	{
		if(strcmp(motif_lu->motif, motif_recherche) == 0)
		{
			trouve = true;
			sequence_lu = motif_lu->tete_seq;
			while(sequence_lu != NULL)
			{
				occ_lu = sequence_lu->tete_occ;
				while(occ_lu != NULL)
				{
					printf("Numero de sequence : %d.\n", sequence_lu->num_seq);
					printf("Position dans la séquence : %d.\n", occ_lu->pos);
					puts("Nombre d'erreurs :");
					printf("\t%d substitutions.\n", occ_lu->nb_sub);
					printf("\t%d insertions.\n", occ_lu->nb_ins);
					printf("\t%d deletions.\n\n", occ_lu->nb_del);
					puts("++++++++++++++++++++++++++++++++++++\n");
					occ_lu = occ_lu->next;
				}
				sequence_lu = sequence_lu->next;
			}
			return;
		}
		motif_lu = motif_lu->next;
	}
	if(!trouve)
	{
		puts("Le motif saisi n'a pas été trouvé dans le dictionnaire...");
	}
}

	/*------------------------------------------------------------------------------*/
	/*---FONCTIONS ET PROCEDURES DE CONTROLE D'EXISTANCE ET DE PLACEMENT D'ESPION---*/
	/*------------------------------------------------------------------------------*/
	
/*-------------------------------------*/

/*---Fonction qui vérifie si un motif est déjà présent dans le dictionnaire et va déplacer un---*/
        /*---espion prec la ou devra être inséré le nouveau motif s'il n'existe pas---*/
bool existe_motif(TPMotif tete_motif, char* chaine, TPMotif* adr_prec_motif)
{
	*adr_prec_motif = NULL;
	TPMotif motif_courant = tete_motif;
	if(motif_courant == NULL)
	{
		// La liste de motif est vide, donc aucun motif n'existe encore
		return false; 
		// On renvoie faux et prec_motif est NULL
	}
	while(motif_courant != NULL)
	{
		if( strcmp(motif_courant->motif, chaine) == 0 )
		{
			// Le motif existe déjà dans le dictionnaire
			return true;
			// On renvoie vrai pour ne pas insérer ce nouveau motif, prec_motif seraplacé sur le motif d'avant
		}
		if( strcmp(motif_courant->motif, chaine) > 0 ) 
		{
			// On effectue une recherche par ordre lexicographique, si le motif d'après est plus grand dans cet ordre,
			// on n'a pas besoin d'aller voir plus loin, le motif n'existe pas
			return false; 
			// On renvoie faux et prec_motif est placé sur le dernier motif situé avant le motif à insérer
		}
		*adr_prec_motif = motif_courant;
		motif_courant = motif_courant->next;
	}
	// On est sorti de la boucle ce qui signifie que le motif à insérer n'existe pas dans le dictionnaire
	// Et qu'il doit être insérer à la fin du dictionnaire (plus grand que les autres par ordre lexicographique)
	return false;
	// On renvoie faux et prec_motif est placé sur le dernier motif du dictionnaire
}

/*-------------------------------------*/

/*---Fonction qui vérifie si une séquence est déjà présente pour un motif donné et va déplacer un---*/
      /*---espion prec la ou devra être insérée la nouvelle séquence s'elle n'existe pas---*/
bool existe_sequence(TPSequence tete_seq, int seq, TPSequence* adr_prec_seq)
{
	*adr_prec_seq = NULL;
	TPSequence seq_courante = tete_seq;
	if(seq_courante == NULL)
	{
		// La liste de séquence est vide
		return false;
		// On renvoie faux et prec_seq est a NULL
	}
	while(seq_courante != NULL)
	{
		if( seq == seq_courante->num_seq )
		{
			// La sequence existe déjà
			return true;
			// On renvoie vrai pour ne pas créer de séquence et prec_seq est placé sur la brique d'avant
		}
		if( seq < seq_courante->num_seq )
		{
			// Les séquences sont triées par odre croissant donc si on tombe sur un numero plus grand,
			// cela signifie que la séquence n'existe pas pour ce motif
			return false;
			// On renvoie faux et prec_seq est placé sur la dernière séquence qui à un numero plus petit
			// que celle que l'on désire insérer
		}
		*adr_prec_seq = seq_courante;
		seq_courante = seq_courante->next;
	}
	// On est sorti de la boucle, on n'as pas trouvé de séquence correspondante
	return false;
	// On renvoie faux et prec_seq sera sur la dernière brique de la liste
}

/*-------------------------------------*/

/*---Fonction qui va parcourir la liste d'occurrence pour un motif et une séquence donnée et va déplacer l'espion prec---*/
	/*---a la fin de la liste des occurrences, chaque occurrence étant unique, elle n'existera forcément pas---*/
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

/*-------------------------------------*/


/*---Fonction mère qui va renvoyer un booléen indiquant si le motif ou la séquence n'est pas présente---*/
	/*---et qui va placer tous les espions (motif, séquence et occurrence) au bon endroit---*/
bool existe(TDict dict, char* chaine, int seq, int occ, TPMotif* adr_prec_motif, TPSequence* adr_prec_seq, TPOccurrence* adr_prec_occ, bool* adr_presence_sequence, bool* adr_presence_motif)
{
	
	*adr_presence_motif = false;
	*adr_presence_sequence = false;
	TPMotif motif_courant = Alloue_TMotif();
	TPSequence sequence_courante = Alloue_TSequence();
	if(existe_motif(dict.tete_motif, chaine, adr_prec_motif))
	{
		// Le motif existe dans le dictionnaire donc on place le booléen presence_motif à vrai
		*adr_presence_motif = true;
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
			// La séquence éxiste dans le dictionnaire donc on place le booléen presence_sequence à vrai
			*adr_presence_sequence = true;
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
	// L'occurrence n'existera pas donc on renvoie faux dans tout les cas
	// Les booléeens présence_motif et présence_séquence nous indiquerons en fonction de leurs valeurs
	// s'il faut également insérer le motif et/ou la séquence
	return false;
}

	/*-----------------------------------------------------*/
	/*---PROCEDURES D'INSERTION D'ELEMENTS DANS UNE LISTE---*/
	/*-----------------------------------------------------*/
	
/*-------------------------------------*/

/*---Procédure qui va permettre la création d'une nouvelle brique motif avec ses informations---*/
			/*---et son chainage dans la liste de motif déja existante---*/
void Creer_Un_Motif(TPMotif* adr_tete_motif, char* chaine, TPMotif prec_motif)
{
	
	TPMotif new_motif = Alloue_TMotif();
	if (prec_motif == NULL) 
	{
		// La liste est vide ou alors il faut insérer le motif en tête de liste
		new_motif->next = *adr_tete_motif;
		new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
		strcpy(new_motif->motif, chaine);
		new_motif->tete_seq = (TPSequence)malloc(sizeof(TSequence));
		new_motif->tete_seq = NULL;
		*adr_tete_motif = new_motif;
		return;
		// Le nouveau motif est crée et inséré, on quitte la procédure
	}
	// L'insertion du motif se fait en milieu ou en queue de liste
	new_motif->next = prec_motif->next;
	prec_motif->next = new_motif;
	new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
	strcpy(new_motif->motif, chaine);
}

/*-------------------------------------*/

/*---Procédure qui va permettre la création d'une nouvelle brique séquence avec ses informations---*/
			/*---et son chainage dans la liste de séquence déja existante---*/
void Inserer_Une_Sequence(TPSequence* adr_tete_seq, int nb_seq, TPSequence prec_seq)
{
	
	TPSequence new_seq = Alloue_TSequence();
	if (prec_seq == NULL)
	{
		// La liste est vide ou la séquence doit être insérée en tête de liste
		new_seq->next = *adr_tete_seq;
		new_seq->num_seq = nb_seq;
		*adr_tete_seq = new_seq;
		return;
		// La nouvelle séquence est crée, on quitte la procédure
	}
	// La séquence doit être insérée en milieu ou en queue de liste
	new_seq->next = prec_seq->next;
	prec_seq->next = new_seq;
	new_seq->num_seq = nb_seq;
}

/*-------------------------------------*/

/*---Procédure qui va permettre la création d'une nouvelle brique occurrence avec ses informations---*/
			/*---et son chainage dans la liste d'occurrences déja existante---*/
void Inserer_Une_Occurrence(TPOccurrence* adr_tete_occ, int occ, TPOccurrence prec_occ, int operation, int num_sub, int num_ins , int num_del)
{
	
	TPOccurrence new_occ = Alloue_TOccurrence();
	if (prec_occ == NULL)
	{
		// La liste est vide ou l'occurrence doit être insérée en tête de liste 
		new_occ->next = *adr_tete_occ;
		new_occ->pos = occ;
		// Selon l'opération que l'on effectue, les informations ne sont pas les mêmes pour l'occurrence
		switch(operation)
		{
			case MATCH :
				new_occ->last = MATCH;
				new_occ->nb_ins = num_ins;
				new_occ->nb_del = num_del;
				new_occ->nb_sub = num_sub;
				break;
			case SUBST :
				new_occ->last = SUBST;
				new_occ->nb_ins = num_ins;
				new_occ->nb_del = num_del;
				new_occ->nb_sub = num_sub+1;
				break;
			case INS :
				new_occ->last = INS;
				new_occ->nb_ins = num_ins+1;
				new_occ->nb_del = num_del;
				new_occ->nb_sub = num_sub;
				break;
			case DEL : 
				new_occ->last = DEL;
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
		// L'occurrence est inserée, on quitte la procédure
	}
	// L'occurrence doit être inserée en milieu ou en queue de liste
	new_occ->next = prec_occ->next;
	new_occ->pos = occ;
	// Selon l'opération que l'on souhaite effectuer 
	switch(operation)
	{
		case MATCH :
			new_occ->last = MATCH;
			new_occ->nb_ins = num_ins;
			new_occ->nb_del = num_del;
			new_occ->nb_sub = num_sub;
			break;
		case SUBST : 
			new_occ->last = SUBST;
			new_occ->nb_ins = num_ins;
			new_occ->nb_del = num_del;
			new_occ->nb_sub = num_sub+1;
			break;
		case INS : 
			new_occ->last = INS;
			new_occ->nb_ins = num_ins+1;
			new_occ->nb_del = num_del;
			new_occ->nb_sub = num_sub;
			break;
		case DEL :
			new_occ->last = DEL;
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

/*-------------------------------------*/

/*---Fonction mère qui va permettre l'insertion de motifs et de séquences (en fonction des booléens présence)---*/
				/*---et dans tous les cas, l'insertions de l'occurrence---*/
void Creer_Nouvelle_Occurrence(TPMotif* adr_tete_motif, char* chaine, int seq , int occ, bool presence_motif, bool presence_sequence, TPMotif prec_motif, TPSequence prec_seq, TPOccurrence prec_occ, TPOccurrence occ_lu, int operation)
{
	
	TPMotif test_motif;
	if(!presence_motif) 
	{
		// Le motif n'existe pas, on doit le créer 
		Creer_Un_Motif(adr_tete_motif, chaine, prec_motif);
		test_motif = *adr_tete_motif;
		prec_seq = NULL;
	}
	if(!presence_sequence)
	{
		// La séquence n'existe pas, on doit la créer
		if(prec_motif == NULL)
		{
			//Si le motif est en tête de liste
			Inserer_Une_Sequence(&test_motif->tete_seq, seq, prec_seq);
			// On vient d'insérer une nouvelle séquence pour ce motif,
			// on doit alors incrémenter le quorum de ce motif
			test_motif->nb_seq_quorum++;
		}
		else
		{
			Inserer_Une_Sequence(&prec_motif->next->tete_seq, seq, prec_seq);
			// On vient d'insérer une nouvelle séquence pour ce motif,
			// on doit alors incrémenter le quorum de ce motif
			prec_motif->next->nb_seq_quorum++;
		}
		prec_occ = NULL;
	}
	// On réalise l'insertion de l'occurrence selon différents cas:
	// On est en tête de liste de motif et de séquence
	if((prec_motif == NULL) && (prec_seq == NULL))
	{
		Inserer_Une_Occurrence((&test_motif->tete_seq->tete_occ), occ, prec_occ, operation, occ_lu->nb_sub, occ_lu->nb_ins, occ_lu->nb_del);	
	}
	// On est au milieu de liste de motif et en tête de liste de séquence
	else if ((prec_motif != NULL) && (prec_seq == NULL))
	{
		Inserer_Une_Occurrence(&prec_motif->next->tete_seq->tete_occ, occ, prec_occ, operation, occ_lu->nb_sub, occ_lu->nb_ins, occ_lu->nb_del);
	}
	// On est au milieu d'une liste de motif et de séquence
	else
	{
		Inserer_Une_Occurrence(&prec_seq->next->tete_occ, occ, prec_occ, operation, occ_lu->nb_sub, occ_lu->nb_ins, occ_lu->nb_del);
	}
}

/*-------------------------------------*/

	/*-----------------------------------------------------------*/
	/*---PROCEDURES DE DESTRUCTION DE LISTES ET DE DICTIONNAIRE---*/
	/*-----------------------------------------------------------*/

/*---Procédure qui va supprimer une liste d'occurrence d'un motif et d'une séquence donnée---*/
void Free_liste_occurrence(TPOccurrence* adr_tete_occ)
{
	
	TPOccurrence occurrence_a_detruire;
	occurrence_a_detruire = *adr_tete_occ;
	TPOccurrence next;
	while(occurrence_a_detruire != NULL)
	{
		next = occurrence_a_detruire->next;
		// On libère la mémoire élément par élement
		free(occurrence_a_detruire);
		occurrence_a_detruire = next;
	}
	// La tête pointe maintenant vers NULL
	*adr_tete_occ = NULL;
}

/*-------------------------------------*/

/*---Procédure qui va supprimer une liste de séquence d'un motif donné---*/
void Free_liste_sequence(TPSequence* adr_tete_seq)
{
	
	TPSequence sequence_a_detruire;
	sequence_a_detruire = *adr_tete_seq;
	TPSequence next;
	while(sequence_a_detruire != NULL)
	{
		// On va détruire la liste d'occurrence associée a cette séquence
		Free_liste_occurrence(&sequence_a_detruire->tete_occ);
		next = sequence_a_detruire->next;
		// On libère la mémoire élément par élement
		free(sequence_a_detruire);
		sequence_a_detruire = next;
	}
	*adr_tete_seq = NULL;
}

/*-------------------------------------*/

/*---Procédure qui va supprimer tous les motifs de l'ancien dictionnaire et détruire toutes les séquences et occurrences associées---*/
void Destruction_dictionnaire(TPMotif* adr_tete_motif)
{
	
	TPMotif motif_a_detruire;
	motif_a_detruire = *adr_tete_motif;
	TPMotif next;
	while(motif_a_detruire != NULL)
	{
		// On détruit la liste de séquence associée à ce motif
		Free_liste_sequence(&motif_a_detruire->tete_seq);
		next = motif_a_detruire->next;
		// On libère la mémoire élement par élement
		free(motif_a_detruire);
		motif_a_detruire = next;
	}
	*adr_tete_motif = NULL;
}
	

/*-------------------------------------*/

	/*--------------------------------------------*/
	/*---PROCEDURES DE CREATION DE DICTIONNAIRE---*/
	/*--------------------------------------------*/
	
/*---Procédure de création du dictionnaire vide appellée au début de la recherche de motif---*/
void Creer_Dictionnaire_Motif_vide(TPMotif* adr_tete_motif, TTabSeq** tab_seq, int nb_seq, int nb_erreurs)
{
	// Indices 
	int i, j, k; 
	// i: parcourir les différentes séquences; j: parcourir chaque position d'une séquence; k: réaliser la série d'insertion
	int longueur_seq;
	int nb_max_insertions;
	// Création de la brique motif vide
	TPMotif motif_vide = Alloue_TMotif();
	motif_vide->motif = (char*)malloc(2*sizeof(char));
	strcpy(motif_vide->motif, "");
	motif_vide->nb_seq_quorum = 0;
	motif_vide->next = *adr_tete_motif;
	*adr_tete_motif = motif_vide;
	TPSequence prec_seq = Alloue_TSequence();
	TPOccurrence prec_occ = Alloue_TOccurrence();
	// Première boucle qui va permettre d'accèder aux séquences une par une
	for(i = 0; i < nb_seq; i++)
	{
		if(!existe_sequence(motif_vide->tete_seq, i+1, &prec_seq))
		{
			// La séquence n'existe pas, on l'insère
			Inserer_Une_Sequence(&motif_vide->tete_seq, i+1, prec_seq);
			// Incrémentation du quorum
			motif_vide->nb_seq_quorum++;
		}
		longueur_seq = strlen(tab_seq[i]->sequence);
		// Boucle qui parcours chaque position d'une séquence
		for(j = 0; j < longueur_seq; j++)
		{
			if(prec_seq == NULL) 
			{
				// Cas ou la premiere sequence vient tout juste d'etre inserée
				deplace_prec_occ(motif_vide->tete_seq->tete_occ, &prec_occ);
				Inserer_Une_Occurrence(&motif_vide->tete_seq->tete_occ, j+1, prec_occ,MATCH , 0, 0, 0);
				// Calcul du nombre d'erreurs possibles
				nb_max_insertions = minimum(nb_erreurs, longueur_seq-(j+1));
				// Réalisation de la série d'insertion
				for(k = 1; k <= nb_max_insertions; k++)
				{
					deplace_prec_occ(motif_vide->tete_seq->tete_occ, &prec_occ);
					Inserer_Une_Occurrence(&motif_vide->tete_seq->tete_occ, j+1, prec_occ,INS , 0, k-1, 0); /* k-1 pour éviter de compter une insertion de trop lors de la création du motif vide */
				}
			}
			else
			{
				deplace_prec_occ(prec_seq->next->tete_occ, &prec_occ);
				Inserer_Une_Occurrence(&prec_seq->next->tete_occ, j+1, prec_occ,MATCH , 0, 0, 0);
				// Calcul du nombre d'erreurs possibles
				nb_max_insertions = minimum(nb_erreurs, longueur_seq-(j+1));
				// Réalisation de la série d'insertions
				for(k = 1; k <= nb_max_insertions; k++)
				{
					deplace_prec_occ(prec_seq->next->tete_occ, &prec_occ);
					Inserer_Une_Occurrence(&prec_seq->next->tete_occ, j+1, prec_occ,INS , 0, k-1, 0);
				}
			}
		}
	}
}

/*-------------------------------------*/

void Decouvert_Exacte_Motif_Occurrences_Subst_Ins_Del(TDict* adr_dict, TTabSeq** tab_seq, int nb_seq, int taille_max_motif, int nb_max_erreurs, float quorum)
{
	//indices
	int i,k,l;
	// i: taille du motif; k: parcours du tableau d'alphabet nucléotidique; l: indice pour la série d'insertions
	int cpt;
	int pos_car_droite;
	int nb_erreurs_actuel;
	int nb_max_insertion;
	int nb_caracteres_disponibles_a_droite;
	char* base_courante;
	char* motif_a_inserer;
	char* precedent_motif;
	char alphabet[4] = {'A','C','G','T'};
	TDict dict_a_construire;
	dict_a_construire.tete_motif = NULL;
	TPMotif motif_lu;
	TPMotif prec_motif;
	TPMotif ancien_motif;
	TPMotif motif_a_supprimer;
	TPMotif motif_a_afficher;
	TPSequence sequence_a_afficher;
	TPOccurrence occ_a_afficher;
	TPSequence sequence_lu;
	TPSequence prec_seq;
	TPOccurrence occurrence_lu;
	TPOccurrence prec_occ;
	bool presence_motif;
	bool presence_sequence;
	bool match_possible;
	// Création du dictionnaire pour le motif vide
	Creer_Dictionnaire_Motif_vide(&adr_dict->tete_motif, tab_seq, nb_seq, nb_max_erreurs);
	// Debut de la boucle allant de la taille de motif 0 a la taille du motif final désiré 
	for(i = 0; i < taille_max_motif; i++)
	{
		motif_lu = adr_dict->tete_motif;
		// On parcours les motifs contenus dans le dictionnaire i-1
		while(motif_lu != NULL)
		{
			sequence_lu = motif_lu->tete_seq;
			// Parcours des sequences correspondants au motif lu actuellement
			while(sequence_lu != NULL)
			{
				occurrence_lu = sequence_lu->tete_occ;
				// Parcours des occurrences correspondantes a la sequence lue actuellement
				while(occurrence_lu != NULL)
				{
					// Calcul de la position du caractère a droite 
					pos_car_droite = occurrence_lu->pos + i + occurrence_lu->nb_ins - occurrence_lu->nb_del;
					if(pos_car_droite == strlen(tab_seq[sequence_lu->num_seq-1]->sequence))
					// sequence_lu->num_seq-1 = indice de la séquence considérée en C 
					{
						// On est à la fin de la séquence on met la valeur de -1 pour indiquer plus tard que l'on ne peut pas effectuer d'operation
						pos_car_droite = -1;
					}
					// Calcul du nombre d'erreurs deja prises en compte pour l'occurrence que l'on est en train de lire
					nb_erreurs_actuel = occurrence_lu->nb_sub + occurrence_lu->nb_ins + occurrence_lu->nb_del;
					
					// On traite d'abord le cas de la substitution
					// On regarde la dernière opération effectuée
					switch(occurrence_lu->last)
					{
						case MATCH:
							if((pos_car_droite != -1) && (nb_erreurs_actuel < nb_max_erreurs))
							{
								// On peut effectuer une erreur de substitution
								for(k = 0; k < 4; k++)
								{
									// On regarde dans le tableau d'alphabet nucléotidique les caractères différents de celui de la séquence
									if(alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1])
									{
										// On concatène le nouveau caractère avec l'ancien motif
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										// On insère l'occurrence et si besoin le motif et la séquence
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, SUBST);
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
							// On ne peut pas faire de substitution donc on continue la procédure
						break;
						case SUBST:
						case INS: // Si le last est une substitution ou une insertion
							if((pos_car_droite != -1) && (nb_erreurs_actuel < nb_max_erreurs))
							{
								// On peut effectuer une erreur de substitution
								for(k = 0; k < 4; k++)
								{
									// On regarde dans le tableau d'alphabet nucléotidique les caractères différents de celui de la séquence et de celui d'avant
									if((alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1]) && (alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-2]))
									{
										// On concatène le nouveau caractère avec l'ancien motif
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										// On insère l'occurrence et si besoin le motif et la séquence
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, SUBST);
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
							// On ne peut pas faire de substitution donc on continue la procédure
						break;
					}
					
					// On traite le cas de la deletion
					// On regarde la dernière opération effectuée
					switch(occurrence_lu->last)
					{
						// Si c'est un match ou une substitution
						case MATCH :
						case SUBST :
							if(nb_erreurs_actuel < nb_max_erreurs)
							{
								// On peut insérer une occurrence avec erreur de deletion
								for(k = 0; k < 4; k++)
								{
									if(alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-2])
									{	
										// Le caractère de l'alphabet est différent du caractère dans la séquence a la position -1
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, DEL);
										}
										else
										{
											puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
										}
									}
								}
							}
						break;
						case DEL :
							if(nb_erreurs_actuel < nb_max_erreurs)
							{
								// On peut insérer une occurrence avec erreur de deletion
								for(k = 0; k < 4; k++)
								{
									if(alphabet[k] != tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1])
									{
										// Le caractère de l'alphabet est différent du caractère dans la séquence a la position courante
										base_courante = Recuperer_Char(alphabet[k]);
										precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
										strcpy(precedent_motif, motif_lu->motif);
										motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
										motif_a_inserer = strcat(precedent_motif, base_courante);
										if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
										{
											Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, DEL);
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
					
					// On traite le cas du match
					match_possible = true;
					if(pos_car_droite == -1)
					{
						// On est à la fin de la séquence, on ne peut pas faire de match
						match_possible = false;
					}
					if(!match_possible)
					{
						// On passe à l'occurrence suivante
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					if((occurrence_lu->last == INS) && (tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1] == tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-2]))
					{		
						// Si la dernière opération était une insertion et que le caractère de la position courante 
						// est le même que celui de la position d'avant, on ne peut pas faire de match
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					base_courante = Recuperer_Char(tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1]);
					precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
					strcpy(precedent_motif, motif_lu->motif);
					motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
					motif_a_inserer = strcat(precedent_motif, base_courante);
					// On insère l'occurrence (et si besoin le motif et la séquence) avec un match
					if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
					{
						Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, MATCH);
					}
					else
					{
						puts("Erreur : L'occurrence existe deja dans le nouveau dictionnaire ce qui ne devrait pas être le cas");
					}
					// Enfin, on va effectuerla série d'insertions
					
					if(nb_erreurs_actuel == nb_max_erreurs)
					{
						// Le nombre d'erreurs maximum est attaint on ne peut pas faire d'insertions
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					// sequence_lu->num_seq-1 = indice de la séquence considérée en C
					if(pos_car_droite == strlen(tab_seq[sequence_lu->num_seq-1]->sequence))  
					{
						// On est à la fin de la séquence il n'y a plus rien a faire
						pos_car_droite = -1; 
					}
					nb_max_insertion = nb_max_erreurs - nb_erreurs_actuel;
					if(pos_car_droite == -1)
					{
						occurrence_lu = occurrence_lu->next;
						continue;
					}
					// Calcul du nombre max d'insertions à faire
					nb_caracteres_disponibles_a_droite = strlen(tab_seq[sequence_lu->num_seq-1]->sequence)-pos_car_droite-1;
					nb_max_insertion=minimum(nb_max_insertion, nb_caracteres_disponibles_a_droite);
					// Réalisation de la série d'insertions
					for(l = 1; l <= nb_max_insertion; l++)
					{
						base_courante = Recuperer_Char(tab_seq[sequence_lu->num_seq-1]->sequence[pos_car_droite-1]);
						precedent_motif = (char*)malloc((strlen(motif_lu->motif)+1)*sizeof(char));
						strcpy(precedent_motif, motif_lu->motif);
						motif_a_inserer = (char*)malloc((i+1)*sizeof(char));
						motif_a_inserer = strcat(precedent_motif, base_courante);
						if(!existe(dict_a_construire, motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif))
						{
							Creer_Nouvelle_Occurrence(&dict_a_construire.tete_motif , motif_a_inserer, sequence_lu->num_seq, occurrence_lu->pos, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ, occurrence_lu, INS);
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
		// Le dictionnaire des motifs de taille i est rempli on détruit le dictionnaire des motifs de taille i-1
		
		Destruction_dictionnaire(&adr_dict->tete_motif);
		adr_dict->tete_motif = dict_a_construire.tete_motif;
		dict_a_construire.tete_motif = NULL;	
		
		
		// On regarde pour chaque motif si la contrainte du quorum est respectée, si ce n'est pas le cas,
		// les occurrences, séquences et ce motif sont supprimés du dictionnaire 
		motif_lu = adr_dict->tete_motif;
		ancien_motif = adr_dict->tete_motif;
		cpt = 0;
		while(motif_lu != NULL)
		{
			if((motif_lu->nb_seq_quorum/nb_seq) < quorum)
			{
				ancien_motif->next = motif_lu->next;
				motif_a_supprimer = motif_lu;
				if( cpt == 0)
				{
					adr_dict->tete_motif = ancien_motif->next;
				}
				motif_lu = ancien_motif->next;
				Free_liste_sequence(&motif_a_supprimer->tete_seq);
				free(motif_a_supprimer);
				continue;
			}
			ancien_motif = motif_lu;
			motif_lu = motif_lu->next;
			cpt++;
		}		
		
	}
}

/*-------------------------------------*/


