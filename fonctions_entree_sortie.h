/* Prototypes des fonctions de gestion d'entrée et de sortie */

char* SaisieMot();

char* Recuperer_ligne(char* ligne);
FILE* Ouvrir_Fichier();

int Compte_Nb_Seq(FILE* fp);

void Lecture_Fichier_Sequences(FILE* fp, TTabSeq** tab_seq);

TTabSeq* AlloueTTabSeq();

void AfficheTTabSeq(TTabSeq** tab_seq, int nb_seq);

TDict* AlloueTDict();

