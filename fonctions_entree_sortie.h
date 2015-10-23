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

bool existe_motif(TPMotif tete_motif, char* chaine, TPMotif* adr_prec_motif);

bool existe_sequence(TPSequence tete_seq, int seq, TPSequence* adr_prec_seq);

bool existe_occ(TPOccurrence tete_occ, int occ, TPOccurrence* adr_prec_occ);

void Creer_Un_Motif(TPMotif* adr_tete_motif, char* chaine, TPMotif prec_motif);

void Creer_Une_Sequence(TPSequence* adr_tete_seq, int seq, TPMotif* adr_tete_motif, TPSequence prec_seq);

void Creer_Une_Occurrence(TOccurrence* tete_occ, int occ, TOccurrence* prec_occ);

void Creer_Nouvelle_Occurrence(TPMotif* adr_tete_motif, char* chaine, int seq , int occ, bool presence_motif, bool presence_sequence, TPMotif prec_motif, TPSequence prec_seq, TPOccurrence prec_occ);

bool existe(TDict dict, char* chaine, int seq, int occ, TMotif* adr_prec_motif, TSequence* adr_prec_seq, TOccurrence* adr_prec_occ, bool* adr_presence_sequence, bool* adr_presence_motif);

void Creer_Dictionnaire_Motifs_T1(TDict dict, TTabSeq** tab_seq, int nb_seq);
