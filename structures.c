/* Définitions des structures */

/* Dictionnaire des séquences qui étaient dans le fichier */
typedef struct TTabSeq TTabSeq;
struct TTabSeq
{
	char* identifiant_seq;
	char* sequence;
};

/* dictionnaire des occurences d'un motif */
typedef struct TOccurrence TOccurrence;
struct TOccurrence
{
	int pos;
	int nb_ins;
	int nb_del;
	int nb_sub;
	int last;
	struct TOccurrence* next;
};
typedef TOccurrence* TPOccurrence;


typedef struct TSequence TSequence;
struct TSequence
{
	int num_seq;
	struct TSequence* next;
	struct TOccurrence* tete_occ;
};
typedef TSequence* TPSequence;

/* dictionaire des motifs */
typedef struct TMotif TMotif;
struct TMotif
{
	char* motif; /* le motif lui même "ATGC" */
	float nb_seq_quorum; /* le nombre de séquence possèdant le motif, permettant de calculer le quorum */
	struct TSequence* tete_seq; /* pointeur vers la première séquence trouvée possédant le motif */
	struct TMotif* next; /* pointeur vers le motif suivant */
};
typedef TMotif* TPMotif;

typedef struct TDict TDict;
struct TDict 
{
	struct TMotif* tete_motif;
};
typedef TDict* TPDict;

typedef int* TPInt ;

typedef bool* TPbool ;
