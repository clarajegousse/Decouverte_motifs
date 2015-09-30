/* Définitions des structures */

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
/*typedef TOccurrence* TPointer*/

typedef struct TSequence TSequence;
struct TSequence
{
	int num_seq;
	struct TSequence* next;
	struct TOccurrence* prem_occ;
};
/*typedef TSequence* TPointer*/

typedef struct TDict TDict;
struct TDict
{
	char* motif;
	int nb_seq;
	struct TDict* next;
	struct TSequence* prem_seq;
};
/*typedef TDict* TPointer*/
