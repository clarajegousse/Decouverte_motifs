/* Prototypes des fonctions de gestion d'entrée et de sortie */

char* Saisie_Mot();

char* Recuperer_Ligne(char* ligne);

char* Recuperer_Char(char carac);

FILE* Ouvrir_Fichier();

int Compte_Nb_Seq(FILE* fp);

void Lecture_Fichier_Sequences(FILE* fp, TTabSeq** tab_seq);

TTabSeq* Alloue_TTabSeq();

void Affiche_TTabSeq(TTabSeq** tab_seq, int nb_seq);

TMotif* Alloue_TMotif();

TSequence* Alloue_TSequence();

TOccurrence* Alloue_TOccurrence();

void Affiche_Un_Motif(TMotif* m);

TMotif* Creer_Un_Motif_T1(char c, int longueur_motif);

void Affiche_Dictionnaire_Motifs(TMotif* tete_motif);

void Creer_Dictionnaire_Motifs_T1(TTabSeq** tab_seq, int nb_seq);



