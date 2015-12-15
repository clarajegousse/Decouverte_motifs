/*---Prototypes des fonctions de gestion d'entrée et de sortie---*/

/*---Fonctions et Procédures de lecture de fichier---*/

char* Saisie_Mot();

char* Recuperer_Ligne(char* ligne);

char* Recuperer_Char(char carac);

FILE* Ouvrir_Fichier();

int Compte_Nb_Seq(FILE* fp);

void Lecture_Fichier_Sequences(FILE* fp, TTabSeq** tab_seq);

/*---Procédure de sauvegarde des résultats dans un fichier---*/

void Sauvegarde_Dictionnaire_Motifs(TPMotif tete_motif, int nb_seq);

/*---Fonction non spécifique à la recherche de motif---*/

int minimum(int a, int b);

/*---Fonctions d'allocation mémoire---*/

TTabSeq* Alloue_TTabSeq();

TPMotif Alloue_TMotif();

TPSequence Alloue_TSequence();

TPOccurrence Alloue_TOccurrence();

/*---Procédures d'affichage---*/

void Affiche_Dictionnaire_Motifs(TPMotif tete_motif, int nb_seq);

void Affiche_Occurrences_D_Un_Motif(TPMotif tete_motif, char* motif_recherche);

/*---Fonctions et procédures de contrôle d'existance et de placement d'espion*/

bool existe_motif(TPMotif tete_motif, char* chaine, TPMotif* adr_prec_motif);

bool existe_sequence(TPSequence tete_seq, int seq, TPSequence* adr_prec_seq);

void deplace_prec_occ(TPOccurrence tete_occ, TPOccurrence* adr_prec_occ);

bool existe(TDict dict, char* chaine, int seq, int occ, TMotif* adr_prec_motif, TSequence* adr_prec_seq, TOccurrence* adr_prec_occ, bool* adr_presence_sequence, bool* adr_presence_motif);

/*---Procédures d'insertions d'éléments dans une liste---*/

void Creer_Un_Motif(TPMotif* adr_tete_motif, char* chaine, TPMotif prec_motif);

void Inserer_Une_Sequence(TPSequence* adr_tete_seq, int nb_seq, TPSequence prec_seq);

void Inserer_Une_Occurrence(TPOccurrence* adr_tete_occ, int occ, TPOccurrence prec_occ, int last, int num_sub, int num_ins , int num_del);

void Creer_Nouvelle_Occurrence(TPMotif* adr_tete_motif, char* chaine, int seq , int occ, bool presence_motif, bool presence_sequence, TPMotif prec_motif, TPSequence prec_seq, TPOccurrence prec_occ, TPOccurrence occ_lu, int operation);

/*---Procédures de destruction de listes et de dictionnaire---*/

void Free_liste_occurrence(TPOccurrence* adr_tete_occ);

void Free_liste_sequence(TPSequence* adr_tete_seq);

void Destruction_dictionnaire(TPMotif* adr_tete_motif);

/*---Procédures de création de dictionnaire---*/

void Creer_Dictionnaire_Motif_vide(TPMotif* adr_tete_motif, TTabSeq** tab_seq, int nb_seq, int nb_erreurs);

void Decouvert_Exacte_Motif_Occurrences_Subst_Ins_Del(TDict* adr_dict, TTabSeq** tab_seq, int nb_seq, int taille_max_motif, int nb_max_erreurs, float quorum);
