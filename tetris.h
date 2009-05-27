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
int* estrai_in_parallelo (rbtree*);
//prototipi tools
int is_lower_than(int pa, int la, int pb, int lb);

