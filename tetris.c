#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"


// FUNZIONI TETRIS

rbtree *scatola(int x){
	if (x <= 1)
		return NULL;
	rbtree* temp = createrbtree();
	temp->size = x;
	temp->columns_counter = malloc((x-1) * sizeof (int));
	return temp;
}

int inserisci(rbtree* box, int x){
	// il blocco eccede la dimensione consentita
	if (x+1 >= box->size)
		return -1;	
	
	// sistema contatore colonne
	box->columns_counter[x] = x;
	box->columns_counter[x+1] = x;
	box->columns_counter[0] = 0;
	return 0;
}






/* Creazione Albero Mosaico*/
rbtree *createrbtree()
{
	rbtree *t = (rbtree*) malloc(sizeof(rbtree));
	if(!t) {
		fprintf(stderr,"Errore di allocazione A\n");
        	exit(-1);
	}
	if(!(t->root = (rbnode*) malloc(sizeof(rbnode)))) {
		fprintf(stderr,"Errore di allocazione B\n");
        	exit(-2);
	}
	t->nil = t->root;
	t->nil->left = t->nil->right = t->nil->up = t->nil;
	t->nil->c = black;
	return t;
}

/* Rotazione sinistra, per mantenere immutate le proprietà dell'albero */
void leftrotate(rbtree *r, rbnode *x)
{
	rbnode *y = x->right;
	
	x->right = y->left;
	if(y->left != r->nil)
		y->left->up = x;
    y->up = x->up;
    if(x->up == r->nil)
             r->root = y;
    else if(x == x->up->left)   
                     x->up->left = y;
                     else
                     x->up->right = y;
    y->left = x;
    x->up = y;
}

/* Rotazione destra, per mantenere immutate le proprietà dell'albero */
void rightrotate(rbtree *r, rbnode *x)
{
	rbnode *y = x->left;

	x->left = y->right;
	if(y->right != r->nil)
 	            y->right->up = x;
    y->up = x->up;
    if(x->up == r->nil)
             r->root = y;
    else if(x == x->up->right)
                 x->up->right = y;
                 else
                 x->up->left = y;
	y->right = x;
    x->up = y;
}				

/* Inserimento del singolo nodo, con valorizzazione di tutti i campi del nodo */
rbnode *simpleinsert(rbtree *tree, int p, int l)
{
   
	rbnode *q = (rbnode*) malloc(sizeof(rbnode));
	rbnode *r = tree->root;
	rbnode *s = tree->nil;

	if(!q) { 
		fprintf(stderr,"Errore di allocazione C\n");
        	exit(-4);
	}
	
	q->p = p;
	q->l = l;

	q->left = q->right = tree->nil;
	q->c = red;
	
	while(r != tree->nil) {                /* Controllo dove va inserito il nuovo nodo */
		
		s = r;
		if (is_lower_than(p,l, r->p, r->l) < 0){
		   r = r->left;
        }
		else{
			if (is_lower_than(p,l, r->p, r->l) == 0)
				return NULL;
             r = r->right;
        }                  
      }
	   q->up = s;
  

	if(s == tree->nil)
		tree->root = q;
	else{
		
       if(is_lower_than(p,l, s->p, s->l) < 0)
           s->left = q;
		else{
			if (is_lower_than(p,l, s->p, s->l) == 0)
				return NULL;
   	       s->right = q;
		}
	}

	return q;
}

/* Inserimento di un nuovo elemento nell'albero */
int rbinsert(rbtree *tree, int p, int l)
{
	
	rbnode *x = simpleinsert(tree, p, l);
	if (x == NULL)
			return -1;
	while(x != tree->root && x->up->c == red) {     /* Finchè x non è la radice e il padre è red */
		if(x->up == x->up->up->left) {              /* Se il padre di x è uguale al figlio sinistro di suo nonno, cioè il padre di x */
			rbnode *y = x->up->up->right;           /* y è uguale allo zio di x */
            if(y->c == red) {                       /* se il colore di y è red */
				x->up->c = black;                   /* il colore del padre di x è black */
				y->c = black;                       /* il colore di y è balck */
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				x = x->up->up;                      /* x è uguale a suo nonno */
			} else {
				if(x == x->up->right){              /* se x è uguale a suo fratello */
                     x = x->up;              
					 leftrotate(tree,x);            /* leftrotate con x */
                     }            				
				x->up->c = black;                   /* il colore del padre di x è black */
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				rightrotate(tree, x->up->up);       /* rightrotate con il nonno di x */
			}
		} else {                                    
			rbnode *y = x->up->up->left;            /* y è uguale al figlio sinistro del nonno di x */
			if(y->c == red) {                       /* se il colore di y è red */
				x->up->c = black;                   /* il colore del padre di x è black */
				y->c = black;                       /* il colore di y è black */
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				x = x->up->up;                      /* x è uguale a suo nonno */
			} else {
				if(x == x->up->left){               /* se x è uguale a suo fratello */
                     x = x->up;                     /* x è uguale a suo padre */        
					 rightrotate(tree,x);           /* rightrotate con x */ 
                     }   					
				x->up->c = black;                   /* il colore del padre di x è black */      
				x->up->up->c = red;                 /* il colore del nonno di x è red */
				leftrotate(tree, x->up->up);        /* leftrotate con il nonno di x */
			}
		}
	}
	tree->root->c = black;                          /* il colore della root è black */
	
}

rbnode *search(rbtree *r, int p, int l)
{
	rbnode *n = r->root;

	while(n != r->nil && is_lower_than(p,l, n->p,n->l) !=0)
	        if(is_lower_than(p,l, n->p,n->l) < 0)
	                  n = n->left;
                      else
                      n = n->right;
	return n == r->nil ? NULL : n;
}


int is_lower_than(int pa, int la, int pb, int lb){
	if(la > lb)
		return -1;
	if(la == lb && pa < pb)
		return -1;
	if(la > lb)
		return 0;
	if((la == lb && pa > pb) || la < lb)
		return 1;
	return 0; // sono uguali
}

void inorder(rbnode *p, rbnode *nil)
{
	if(p != nil) {
        	inorder(p->left,nil);
			printf("(%d,%d) ", p->p, p->l);
            inorder(p->right,nil);
	}
}

void visualizza(rbtree *p)
{
	inorder(p->root, p->nil);
}
