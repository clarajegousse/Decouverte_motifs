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
	TPMotif motif_courant = Alloue_TMotif();
	motif_courant = tete_motif;
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
	puts("on teste ensuite la presence de la sequence");
	*adr_prec_seq = NULL;
	TPSequence seq_courante = Alloue_TSequence();
	seq_courante = tete_seq;
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
			puts("La sequence existe deja");
			*adr_presence_sequence = 1;
			if(*adr_prec_seq == NULL)
			{
				sequence_courante = motif_courant->tete_seq;
			}
			else
			{
				sequence_courante = (*adr_prec_seq)->next;
			}
			if(existe_occ(sequence_courante->tete_occ, occ, adr_prec_occ))
			{
				return true;
			}
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
		printf("le nouveau motif inseré est : %s\n", new_motif->motif);
		return; /* on a crée le nouveau motif on quitte la procédure */
	}
	new_motif->next = prec_motif->next;
	prec_motif->next = new_motif;
	new_motif->motif = (char*)malloc((strlen(chaine)+1)*sizeof(char));
	strcpy(new_motif->motif, chaine);
	printf("le nouveau motif inseré est : %s\n", new_motif->motif);
} /* on a crée le nouveau motif on quitte la procédure */

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Une_Sequence(TPSequence* adr_tete_seq, int seq, TPMotif* adr_tete_motif, TPSequence prec_seq)
{
	TPSequence new_seq = Alloue_TSequence();
	if(*adr_tete_seq == NULL)
	{
		puts("la liste de séquence est vide");
	}
	if (prec_seq == NULL)
	{
		puts("il n'y a pas de sequence d'inseréé ");
		puts("on fais pointer la nouvelle brique vrs la tete de sequence du motif ");
		new_seq->next = *adr_tete_seq;
		puts("on donne comme valeur a la brique le numero de sequence");
		new_seq->num_seq = seq;
		puts("on fais pointer la tete de sequence du motif vers la nouvelle brique");
		*adr_tete_seq = new_seq;
		puts("la nouvelle brique est crée on quitte la procédure");
		return;
	}
	new_seq->next = prec_seq->next;
	prec_seq->next = new_seq;
	new_seq->num_seq = seq;
}

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Une_Occurrence(TPOccurrence* adr_tete_occ, int occ, TOccurrence* prec_occ)
{
	TPOccurrence new_occ = Alloue_TOccurrence();
	if (prec_occ == NULL)
	{
		new_occ->next = *adr_tete_occ;
		new_occ->pos = occ;
		*adr_tete_occ = new_occ;
		return;
	}
	new_occ->next = prec_occ->next;
	prec_occ->next = new_occ;
	new_occ->pos = occ;
}

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Nouvelle_Occurrence(TPMotif* adr_tete_motif, char* chaine, int seq , int occ, bool presence_motif, bool presence_sequence, TPMotif prec_motif, TPSequence prec_seq, TPOccurrence prec_occ)
{
	TPMotif test_motif;
	if((!presence_motif) && ((strcmp(chaine, "A") ==0) || (strcmp(chaine, "C") ==0) || (strcmp(chaine, "G") ==0) || (strcmp(chaine, "T") ==0))) /* Si le motif n'existe pas, on doit le créer */
	{
		Creer_Un_Motif(adr_tete_motif, chaine, prec_motif);
		test_motif = *adr_tete_motif;
		prec_seq = NULL;
	}
	if(!presence_sequence)
	{
		//puts("il faut creer la nouvelle sequence");
		if(prec_motif == NULL)
		{
			//puts("on est dans le cas du premier motif inseré");
			/*if(test_motif->tete_seq == NULL)
			{
				//puts("la tete de sequence est vide");
			}*/
			Creer_Une_Sequence(&test_motif->tete_seq, seq, &test_motif, prec_seq);
			test_motif->nb_seq_quorum++;
		}
		else
		{
			//puts("Il y a deja des motifs d'insérés");
			Creer_Une_Sequence(&prec_motif->next->tete_seq, seq, &prec_motif, prec_seq);
			prec_motif->next->nb_seq_quorum++;
		}
		prec_occ = NULL;
	}
	if((prec_motif == NULL) && (prec_seq == NULL))
	{
		puts("insertion de l'occurrence pour le tout premier motif et la toute premiere sequence");
		Creer_Une_Occurrence((&test_motif->tete_seq->tete_occ), occ, prec_occ);	
	}
	else if ((prec_motif != NULL) && (prec_seq == NULL))
	{
		puts("insertion de l'occurence pour un motif et pour la toute premiere sequence de ce motif");
		Creer_Une_Occurrence(&prec_motif->next->tete_seq->tete_occ, occ, prec_occ);
	}
	else
	{
		puts("insertion a la d'une occurrence dans un motif y et une sequence x");
		Creer_Une_Occurrence(&prec_seq->next->tete_occ, occ, prec_occ);
	}
}

/*------------------------------------------------------------------------------------------------------------*/

void Creer_Dictionnaire_Motifs(TDict dict, TTabSeq** tab_seq, int nb_seq)
{
	/* on crée les variables */
	int i, j; /* indices */
	int longueur_seq;
	bool presence_motif;
	bool presence_sequence;
	bool test_existe;
	char* base_courante;
	TPMotif prec_motif;
	TPMotif regard_motif;
	TPSequence prec_seq;
	TPSequence regard_sequence;
	TPOccurrence prec_occ;
	for (i = 0; i < nb_seq; i++)
	{
		longueur_seq = strlen(tab_seq[i]->sequence); /* on trouve la longueur de la sequence i */
		for (j = 0; j < longueur_seq; j++) /* pour tout les bases j de la sequences */
		{
			base_courante = Recuperer_Char(tab_seq[i]->sequence[j]);
			test_existe = existe(dict, base_courante, i, j+1, &prec_motif, &prec_seq, &prec_occ, &presence_sequence, &presence_motif); /* j+1 pour compter les positions en humains */
			if(!test_existe) /* s'il n'y a pas de motif dans le dictionaire  */
			{
				Creer_Nouvelle_Occurrence(&dict.tete_motif , base_courante, i , j+1, presence_motif, presence_sequence, prec_motif, prec_seq, prec_occ); /* Il faut creer la nouvelle occurrence et si necessaire la nouvelle sequence et le nouveau motif */
				/*regard_motif = dict.tete_motif;
				while(regard_motif != NULL)
				{
					printf("le motif contenu dans la brique : %s\n", regard_motif->motif);
					printf("le nombre de sequences contenu pour ce motif : %d\n", regard_motif->nb_seq_quorum);
					regard_sequence = regard_motif->tete_seq;
					while(regard_sequence != NULL)
					{
						printf("le numero de la sequence contenue par ce motif : %d\n", regard_sequence->num_seq);
						regard_sequence = regard_sequence->next;
					}
					regard_motif = regard_motif->next;
				}*/
			}
		}
	}
}
