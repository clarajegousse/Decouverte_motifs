/* Prototypes des fonctions de gestion d'entrée et de sortie */

char* SaisieMot();

int Compte_Nb_Seq(FILE* fp);

void Lecture_Fichier_Sequences(FILE* fp);

TTabSeq* AlloueTTabSeq();

void SaisieTTabSeq(TTabSeq* tab_seq);

void AfficheTTabSeq(TTabSeq** tab_seq, int nb_seq);

FILE* Ouvrir_Fichier();