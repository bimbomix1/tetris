#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#define MAX(a, b) ((a) < (b) ? (b) : (a))
// for visualizza
int *grid;
int size;
int currentLine = NULL;
// FUNZIONI TETRIS

rbtree *scatola(int x){
	if (x <= 1)
		return NULL;
	rbtree* temp = createrbtree();
	temp->size = x;
	temp->columns_counter = malloc((x) * sizeof (int));
	for(size_t i = 0; i <= temp->size; ++i)
	{
		temp->columns_counter[i] = 0;
	}
	return temp;
}

int inserisci(rbtree* box, int x){
	int base;
	// il blocco eccede la dimensione consentita
	if (x+1 >= box->size)
		return -1;	
		
	base = MAX(box->columns_counter[x],box->columns_counter[x+1]);
	// inserisci elemento
	rbinsert(box,x,base+1);
	// sistema contatore colonne

	box->columns_counter[x] = base + 1;
	box->columns_counter[x+1] = base + 1;
	
	
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
/* Controllo se le proprietà dopo la cancellazione vanno bene */
void fixup(rbtree *tree, rbnode *x)
{
	while(x != tree->root && x->c == black) {                   /* Finchè x non è la radice e il padre è black */
		if(x == x->up->left) {                                  
             rbnode *w = x->up->right;                             
			 if(w->c == red) {
                     w->c = black;                                 
				     x->up->c = red;                               
     				 leftrotate(tree, x->up);                       
                     w = x->up->right;                             
			}
			if(w->left->c == black && w->right->c == black) {
				w->c = red;                                   
				x = x->up;                                    
			} else {
				if(w->right->c == black) {
					w->left->c = black;                       
					w->c = red;                               
					rightrotate(tree, w);                      
					w = x->up->right;                         
				}
				w->c = x->up->c;                              
				x->up->c = black;                             
				w->right->c = black;                          
				leftrotate(tree, x->up);                       
				x = tree->root;                               
			}
		} else {          
               rbnode *w = x->up->left;                                    
			   if(w->c == red) {  
                       w->c = black;                                 
  				       x->up->c = red;                              
  				       rightrotate(tree, x->up);                     
  				       w = x->up->left;                              
                }
			if(w->right->c == black && w->left->c == black) {
				w->c = red;                                   
				x = x->up;                                    
			} else {
				if(w->left->c == black) {
					w->right->c = black;                      
					w->c = red;                               
					leftrotate(tree, w);                     
					w = x->up->left;                          
				}
				w->c = x->up->c;                              
				x->up->c = black;                             
				w->left->c = black;                          
				rightrotate(tree, x->up);                     
				x = tree->root;                              
			}
		}
	}
	x->c = black;
}
/* Cancellazione di un elemento dell'albero */
void rbdelete(rbtree *tree, rbnode *q)
{
	rbnode *r, *s;
    
	if(q->left == tree->nil || q->right == tree->nil)
		r = q;
	else {
         r = q->right;
         while (r->left != tree->nil)
                        r = r->left;
         }


	if(r->left != tree->nil)
	           s = r->left;
    else
        s = r->right;
        s->up = r->up;
	if(r->up)
             if(r == r->up->left)
                r->up->left = s;
             else
			      r->up->right = s;
	else
        tree->root = s;		      
	if(r != q)
        q->p = r->p;
	if(r->c == black)
		fixup(tree, s);
	free(r);
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

void display(rbtree *p)
{
	inorder(p->root, p->nil);
}

void inorderadv(rbnode *p, rbnode *nil)
{
	if(p != nil) {
        	inorderadv(p->left,nil);
			if (currentLine == NULL)
				currentLine = p->l;
			
			
			if(p->l != currentLine){
				currentLine = p->l;
				print_row(grid, size);
				printf("\n");
			}
			grid[p->p] = 1;
            inorderadv(p->right,nil);
	}
}

void visualizza(rbtree *p)
{
	grid = malloc(p->size * sizeof(int));
	size = p->size;
	inorderadv(p->root, p->nil);
	print_row(grid, p->size);
	
}


void print_row(int *grid, int size){
	int n = 0;
	while (n < size) 
	{
	

		if (grid[n] == 1){ 
			grid[n] = 0;
			n++;
			printf("XX");
		
		}
			 else{
					grid[n] = 0;
				printf(" ");
				}
				
		
			n++;
		
		}
		
}