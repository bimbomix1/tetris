#define TESTING

#include <stdio.h>
#include <stdlib.h>
typedef enum {red, black} colore;

struct rbnode {
	int p;                             /* posizione */
	int l;							   /* livello nodo */
	colore c;                          /* Colore del nodo */
	struct rbnode *left, *right, *up;  /* Puntatori ai due figli e al padre */
}; 
typedef struct rbnode rbnode;
typedef struct {
	int size;
	int* c_count;
	int h;
	rbnode *root, *nil;
}rbtree;


// funzioni specifiche
rbtree* scatola( int x );
int inserisci(rbtree* , int x );

// prototipipi strutture 
rbtree *createrbtree();
int rbinsert(rbtree*, int p, int l);
void rbdelete(rbtree *tree, rbnode *q);
rbnode *search(rbtree *r, int p, int l);

void visualizza(rbtree *p);
void display(rbtree *p);
void statistica(int, int, int);
int* estrai_in_parallelo (rbtree*);
//prototipi tools
int is_lower_than(int pa, int la, int pb, int lb);

	typedef struct node {
	  int p,l;
	  struct node *next;
	} node;
	
	typedef node *list;










// #ifdef TESTING
// list sottocatasta(rbtree* box, int x);
// #else
// int* sottocatasta(rbtree* box, int x);
// #endif