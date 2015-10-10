/* Prototypes des fonctions de gestion d'entrée et de sortie */

char* SaisieMot();

char* Recuperer_ligne(char* ligne);

char* Recuperer_char(char carac);

FILE* Ouvrir_Fichier();

int Compte_Nb_Seq(FILE* fp);

void Lecture_Fichier_Sequences(FILE* fp, TTabSeq** tab_seq);

TTabSeq* AlloueTTabSeq();

void AfficheTTabSeq(TTabSeq** tab_seq, int nb_seq);

TDict* AlloueTDict();

TSequence* AlloueTSequence();

TOccurrence* AlloueTOccurrence();

void Creer_Dictionnaire_T1(TTabSeq** tab_seq, TDict* dict_t1, int nb_seq);

