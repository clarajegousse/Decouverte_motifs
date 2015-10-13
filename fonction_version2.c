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
	if(caract_voulu[1])
	{
		caract_voulu[1] = '\0';
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
	int i;
	for (i = 0; i < nb_seq; ++i)
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
		m->tete_seq = NULL;
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
		seq->tete_occ = NULL;
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
	printf("motif: %s ;\tnb_seq_quorum: %d.\n", motif_courant->motif, motif_courant->nb_seq_quorum);
}

TMotif* Creer_Un_Motif_T1(char* chaine, int longueur_motif) 
{
	//char buffer = chaine[0]; /* type char uniquement dans le cas des motif de taille 1, sinon type char* */
	TMotif* nouveau_motif;
	
	nouveau_motif = Alloue_TMotif();
	nouveau_motif->motif = (char*)malloc(sizeof(char)*longueur_motif);
	
	/* on copie le motif */
	if(longueur_motif == 1)
	{
			strcpy(nouveau_motif->motif, "");
	}
	strcat(nouveau_motif->motif, chaine);
	printf("Le motif inseré est : %s\n", nouveau_motif->motif);

	nouveau_motif->nb_seq_quorum = 0;
	nouveau_motif->next = NULL;

	return nouveau_motif;
}

/*void Ajouter_Sequence_motif(TSequence* sequence, int seq)
{
	puts("creation des nouvelles variables");
	TSequence* sequence_courante = Alloue_TSequence();
	sequence_courante = sequence;
	TSequence* nouvelle_sequence = Alloue_TSequence();
	nouvelle_sequence = NULL;
	puts("nouvelles variables crées");
	if(sequence == NULL)
	{
		puts("il n'y a pas de nouvelles sequences pour ce motif il faut le creer");
		printf("la nouvelle sequence porte le numero : %d\n", seq+1);
		sequence->num_seq = seq+1;
		printf("la nouvelle sequence porte le numero : %d\n", nouvelle_sequence->num_seq);
		sequence = nouvelle_sequence;
		//motif_courant->nb_seq_quorum++;
		puts("on a cree la nouvelle sequence on sort de la procedure");
		return;
	}
	while((sequence_courante->next != NULL) && (sequence_courante->num_seq != seq))
	{
		sequence_courante = sequence_courante->next;
	}
	if(sequence_courante->num_seq != seq)
	{
		nouvelle_sequence->num_seq = seq;
		sequence_courante->next = nouvelle_sequence;
		return;
	}
}*/
int existe_motif(TPMotif tete_motif, char* chaine, TPMotif* adr_prec_motif)
{
	*adr_prec_motif = NULL;
	TPMotif motif_courant;
	//motif_courant = Alloue_TMotif();
	motif_courant = tete_motif;
	while(motif_courant != NULL)
	{
		if( strcmp(motif_courant->motif, chaine) == 0 )
		{
			return 1;
		}
		if( strcmp(motif_courant->motif, chaine) > 0 )
		{
			return 0;
		}
		*adr_prec_motif = motif_courant;
		motif_courant = motif_courant->next;
	}
	return 0;
}

int existe_sequence(TPSequence tete_seq, int seq, TPSequence* adr_prec_seq)
{
	*adr_prec_seq = NULL;
	TPSequence seq_courante;
	//seq_courante = Alloue_TSequence();
	seq_courante = tete_seq;
	while(seq_courante != NULL)
	{
		if( seq == seq_courante->num_seq )
		{
			return 1;
		}
		if( seq > seq_courante->num_seq )
		{
			return 0;
		}
		*adr_prec_seq = seq_courante;
		seq_courante = seq_courante->next;
	}
	return 0;
}

int existe_occ(TOccurrence* tete_occ, int occ, TOccurrence* adr_prec_occ)
{
	adr_prec_occ = NULL;
	TOccurrence* occ_courante;
	occ_courante = Alloue_TOccurrence();
	occ_courante = tete_occ;
	while(occ_courante != NULL)
	{
		if( occ == occ_courante->pos )
		{
			return 1;
		}
		if( occ > occ_courante->pos )
		{
			return 0;
		}
		adr_prec_occ = occ_courante;
		occ_courante = occ_courante->next;
	}
	return 0;
}

int existe(TDict* dict_t1, char* chaine, int seq, int occ, TPMotif* adr_prec_motif, TPSequence* adr_prec_seq, TPOccurrence* adr_prec_occ, int* adr_presence_sequence, int* adr_presence_motif)
{
	*adr_presence_motif = 0;
	*adr_presence_sequence = 0;
	//TMotif* motif_courant = Alloue_TMotif();
	//TSequence* sequence_courante = Alloue_TSequence();
	if(existe_motif(dict_t1.tete_motif, chaine, adr_prec_motif))
	{
		puts("le motif existe deja");
		*adr_presence_motif = 1;
		if(adr_prec_motif == NULL)
		{
			motif_courant = dict_t1->tete_motif;
		}
		else
		{
			motif_courant = adr_prec_motif->next;
		}
		if(existe_sequence(motif_courant->tete_seq, seq, adr_prec_seq))
		{
			puts("La sequence existe deja");
			*adr_presence_sequence = 1;
			if(adr_prec_seq == NULL)
			{
				sequence_courante = motif_courant->tete_seq;
			}
			else
			{
				sequence_courante = adr_prec_seq->next;
			}
			if(existe_occ(sequence_courante->tete_occ, occ, adr_prec_occ))
			{
				return 1;
			}
		}
	}
	return 0;
}

/*void Creer_Un_Motif(TMotif* tete_motif, char* chaine, TMotif* prec_motif)
{
	TMotif* new_motif = Alloue_TMotif();
	puts("on vient d'allouer de la memoire pour le nouveau motif");
	if (prec_motif == NULL)
	{
		puts("il faut inserer le nouveau motif en tete de liste");
		new_motif->next = tete_motif;
		new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
		strcpy(new_motif->motif, chaine);
		tete_motif = new_motif;
		puts("on a crée le nouveau motif on quitte la procédure");
		printf("le nouveau motif inseré est : %s\n", new_motif->motif);
		return;
	}
	new_motif->next = prec_motif->next;
	prec_motif->next = new_motif;
	new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
	strcpy(new_motif->motif, chaine);
	puts("on a crée le nouveau motif on quitte la procédure");
	printf("le nouveau motif inseré est : %s\n", new_motif->motif);
}

void Creer_Une_Sequence(TDict* dict, TSequence* tete_seq, int seq, TMotif* tete_motif, TSequence* prec_seq)
{
	TSequence* new_seq = Alloue_TSequence();
	if (prec_seq == NULL)
	{
		new_seq->next = tete_seq;
		new_seq->num_seq = seq;
		tete_seq = new_seq;
		tete_motif->nb_seq_quorum++;
		return;
	}
	new_seq->next = prec_seq->next;
	prec_seq->next = new_seq;
	new_seq->num_seq = seq;
	tete_motif->nb_seq_quorum++;
}

void Creer_Une_Occurrence(TOccurrence* tete_occ, int occ, TOccurrence* prec_occ)
{
	TOccurrence* new_occ = Alloue_TOccurrence();
	if (prec_occ == NULL)
	{
		new_occ->next = tete_occ;
		new_occ->pos = occ;
		tete_occ = new_occ;
		return;
	}
	new_occ->next = prec_occ->next;
	prec_occ->next = new_occ;
	new_occ->pos = occ;
}*/

/*void Creer_Nouvelle_Occurrence(TDict* dict, char* chaine, int seq , int occ, int presence_motif, int presence_sequence, TMotif* prec_motif, TSequence* prec_seq, TOccurrence* prec_occ)
{
	if(!presence_motif)
	{
		puts("il faut creer le motif");
		Creer_Un_Motif(dict->tete_motif, chaine, prec_motif);
		prec_seq = NULL;
	}
	if(!presence_sequence)
	{
		puts("il faut creer la nouvelle sequence");
		if(prec_motif == NULL)
		{
			Creer_Une_Sequence(dict, dict->tete_motif->tete_seq, seq, dict->tete_motif, prec_seq);
		}
		else
		{
			Creer_Une_Sequence(dict, prec_motif->next->tete_seq, seq, prec_motif, prec_seq);
		}
		prec_occ = NULL;
	}
	if((prec_motif == NULL) && (prec_seq == NULL))
	{
		puts("insertion de l'occurrence pour le tout premier motif et la toute premiere sequence");
		Creer_Une_Occurrence(dict->tete_motif->tete_seq->tete_occ, occ, prec_occ);	
	}
	else if ((prec_motif != NULL) && (prec_seq == NULL))
	{
		puts("insertion de l'occurence pour un motif et pour la toute premiere sequence de ce motif");
		Creer_Une_Occurrence(prec_motif->next->tete_seq->tete_occ, occ, prec_occ);
	}
	else
	{
		puts("insertion a la d'une occurrence dans un motif y et une sequence x");
		Creer_Une_Occurrence(prec_seq->next->tete_occ, occ, prec_occ);
	}
}*/

void Creer_Dictionnaire_Motifs(TDict* dict, TTabSeq** tab_seq, int nb_seq)
{
	/* on crée les variables */
	int i, j; /* indices */
	//int longueur_motif = 1; /* cas des motifs de taille 1 */
	int longueur_seq;
	int presence_motif;
	int presence_sequence;
	char* base_courante;

	TPMotif prec_motif;
	prec_motif = Alloue_TMotif();
	TPSequence prec_seq;
	prec_seq = Alloue_TSequence();
	TPOccurrence prec_occ;
	prec_occ = Alloue_TOccurrence();
	for (i = 0; i < nb_seq; i++)
	{
		/* on trouve la longueur de la sequence i */
		longueur_seq = strlen(tab_seq[i]->sequence);
		printf("la longueur de la sequence courante est : %d\n", longueur_seq);

		/* pour tout les bases j de la sequences */
		for (j = 0; j < longueur_seq; j++)
		{
			base_courante = Recuperer_Char(tab_seq[i]->sequence[j]);
			printf("la base courante est : %s\n", base_courante);
			printf("on travaille sur la position %d de la sequence courante\n", j);
			/* s'il n'y a pas de motif dans le dictionaire */
			if(!existe(dict, base_courante, i, j+1, &prec_motif, &prec_seq, &prec_occ, &presence_motif, &presence_sequence)) /* j+1 pour compter les positions en humains */
			{
				puts("Il faut creer la nouvelle occurrence et si necessaire la nouvelle sequence et le nouveau motif");
				//Creer_Nouvelle_Occurrence(dict, base_courante, i , j+1, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ);
			}
		}
	}
	//Affiche_Dictionnaire_Motifs(dict->tete_motif);
}
