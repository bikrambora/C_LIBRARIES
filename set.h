/***********************************************************
 *          SUBMITTED BY: BIKRAM KAUSHIK BORA              *
 *                                                         *
 *          STUDENT ID: 663854                             *
 *                                                         *
 ***********************************************************/

/*
** This file contains the function prototypes and struct definitions used by the file heap.c
**
*/

typedef struct node SetItem;

struct node 
{
	unsigned int Label;
	SetItem *next;
	SetItem *prev;
};

typedef struct 
{
	unsigned int name;
	unsigned int n;
	SetItem *head;
	SetItem *foot;
}Set;

Set* createSet(unsigned int name); //allocates memory for a set and initializes its variables

int isEmptySet(Set *S); //checks if set is empty returns 1 if true 0 if false

void freeSet(Set *S); //frees the memory allocated to a set


int insertInSet(Set *S, unsigned int Label);  //inserts an element into a set and returns 1 if successful 0 if failed
int removeFromSet(Set *S, unsigned int Label);

void printSet(Set *S); //prints the elements of a set
Set* unionSet(Set* S1, Set* S2);  //Unites two sets and returns a pointer to the united set
void minusSet(Set* S1, Set* S2);  // Removes elements of set s2 from s1
int presentInSet(Set *S, unsigned int Label);   //Returns 1 if input element is present in set otherwise returns 0