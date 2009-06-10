#include <stdio.h>
#include <stdlib.h>
#include "tetris.h"
#define MAX(a, b) ((a) < (b) ? (b) : (a))
#define TESTING


// for visualizza
int *grid;
int size;
int currentLine = NULL;
int current_level;
int* current_row;
int* next_row;
int trovato = 0, last_row_is_empty_row = 1;


// catasta
list catasta_list;
rbnode* catasta_node;



	int IsEmpty( list s ) { return ( s == NULL ); }

	void ListInsert( list *s, int p, int l ) {
	  list t;
	  if ( IsEmpty( *s )  ) {
	    t = malloc( sizeof( struct node ) );
	    t->p = p;
		t->l = l;
	    t->next = *s;
	    *s = t;
	    return ;
	  }
	  t = *s;
	  while ( ( t->next ) ) t = t->next;
	    list q = malloc( sizeof( struct node ) );
	    q->p = p;
		q->l = l;
	    q->next = t->next;
	    t->next = q;
	}
	void ListPrint(list *l){
	   for (list t = l; t != NULL; t = t->next )
	   printf( " (%d,%d)", t->p, t->l );
	}

// FUNZIONI TETRIS

rbtree *scatola(int x){
	if (x <= 1)
		return NULL;
	rbtree* temp = createrbtree();
	temp->h = 0;
	temp->size = x;
	temp->c_count = malloc((x) * sizeof (int));
	temp->c_max = malloc((x) * sizeof (int));
	for(size_t i = 0; i <= temp->size; ++i)
	{
		temp->c_count[i] = 0;
	}
	return temp;
}

int inserisci(rbtree* box, int x){
	int base;
	if (x < 0 )
		return -1;
	// il blocco eccede la dimensione consentita
	if (x+1 >= box->size)
		return -1;	
		
	base = MAX(box->c_count[x],box->c_count[x+1]);
	// inserisci elemento
	rbinsert(box,x,base+1);
	// sistema contatore colonne
	box->c_max[x] = base+1;
	box->c_count[x] = base + 1;
	box->c_count[x+1] = base + 1;
	box->h = (base+1) > box->h ? base+1: box->h ; 
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
		else {
             r = r->right;                  
             }
        }
	q->up = s;
	if(s == tree->nil)
		tree->root = q;
	else{
       if(is_lower_than(p,l, s->p, s->l) < 0)
           s->left = q;
	   else
   	       s->right = q;
	}return q;
}
/* Inserimento del singolo nodo, con valorizzazione di tutti i campi del nodo */
// rbnode *simpleinsert(rbtree *tree, int p, int l)
// {
//    
// 	rbnode *q = (rbnode*) malloc(sizeof(rbnode));
// 	rbnode *r = tree->root;
// 	rbnode *s = tree->nil;
// 
// 	if(!q) { 
// 		fprintf(stderr,"Errore di allocazione C\n");
//         	exit(-4);
// 	}
// 	
// 	q->p = p;
// 	q->l = l;
// 
// 	q->left = q->right = tree->nil;
// 	q->c = red;
// 	
// 	while(r != tree->nil) {                /* Controllo dove va inserito il nuovo nodo */
// 		
// 		s = r;
// 		if (is_lower_than(p,l, r->p, r->l) < 0){
// 		   r = r->left;
//         }
// 		else{
// 			if (is_lower_than(p,l, r->p, r->l) == 0)
//              r = r->right;
//         }                  
//       }
// 	   q->up = s;
//   
// 
// 	if(s == tree->nil)
// 		tree->root = q;
// 	else{
// 		
//        if(is_lower_than(p,l, s->p, s->l) < 0)
//            s->left = q;
// 		else{
// 			if (is_lower_than(p,l, s->p, s->l) == 0)
// 				return NULL;
//    	       s->right = q;
// 		}
// 	}
// 
// 	return q;
// }

/* Inserimento di un nuovo elemento nell'albero */
int rbinsert(rbtree *tree, int p, int l)
{
	
	rbnode *x = simpleinsert(tree, p, l);

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
	        if(is_lower_than(p,l, n->p,n->l) < 0){
					// printf("vado a sinistra \n");
	                  n = n->left;
                     } else{
	// printf("vado a destra \n");
                      n = n->right;}
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
		q->l = r->l;
	if(r->c == black)
		fixup(tree, s);
		// printf("canclelo elemento (%d,%d) \n", r->p, r->l);
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

void inorder(rbnode *n, rbnode *nil)
{
	if(n != nil) {
        	inorder(n->left,nil);
			printf("(%d,%d) ", n->p, n->l);
            inorder(n->right,nil);
	}
}

void display(rbtree *p)
{
	inorder(p->root, p->nil);
	printf("\n");
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

void init_random_number() { 
  srand( time( NULL ) ); /* inizializza un seme casuale per il generatore pseudo-casuale
			    tramite il clock di sistema */
}

int random_number( int l, int r ){
  return ( rand() % ( r - l ) + l ); /* genera un numero casuale tra l e r-1 */
}

void acatasta(rbnode *n, rbnode *nil){
	if(n != nil) {
		
	acatasta(n->right,nil);	
	if (current_level == NULL)
		 current_level = n->l;
		 			// printf("i valori riscontrati sono : n->l = %d  current_level => %d, catasta_node->l =%d \n",n->l, current_level ,catasta_node->l);
		 	   	    if ( n->l != current_level && n->l != catasta_node->l && next_row != NULL){
		 			// printf( "cambio livello \n");
		 				current_level = n->l;
						// printf("impostato livello a %d \n", n->l);
						// 												printf("============PRIMA =============== \n");
						// 												printf("riga corrente \n "); for(size_t i = 0; i < size; ++i) { printf("%d - ",current_row[i]);}
						// 												printf("\n riga seguente \n "); for(size_t j = 0; j < size; ++j) {printf("%d - ",next_row[j]);}
						if (!last_row_is_empty_row){																								
								int* temp = current_row;
								current_row = next_row;
								next_row = temp;
								
						}									
						// printf("\n============DOPO =============== \n");
						// 											 				printf("riga corrente \n "); for(size_t i = 0; i < size; ++i){printf("%d - ",current_row[i]);}
						// 											 				printf("\n riga seguente \n "); for(size_t j = 0; j < size; ++j) { printf("%d - ",next_row[j]);}
						// 											                printf("\n \n \n \n \n");
		 		}
		 
		 		if (catasta_node->p == n->p && catasta_node->l == n->l){
		 			// printf("area sfigata \n \n trovata per elemento (%d, %d)  ", n->p, n->l);
		 			trovato = 1;
					// last_row_is_empty_row = 1;
		 			/* LIVELLO E ELEMENTO TROVATO */
		 			// abbiamo trovato il nodo e generiamo i successivi elementi
		 			// printf("(%d,%d) =sotto> ",n->p, n->l );
		 			// 	 			 			printf(" (%d,%d) ",n->p-1,n->l+1);
		 			// 	 			 			printf(" (%d,%d) ",n->p,n->l+1);
		 			// 	 			 			printf(" (%d,%d) \n",n->p+1,n->l+1);
		 			current_row = malloc((size) * sizeof (int));
		 			next_row = malloc((size) * sizeof (int));
		 			// for(size_t i = 0; i < size; ++i)
		 			// {
		 			// 	current_row[i] = 0;
		 			// 	next_row[i] = 0;
		 			// }
		 			// attento che non produca valori limite che escano dalla scatola fare!!!
		 			next_row[n->p-1] = n->l+1;
		 			next_row[n->p] = n->l+1;
		 			next_row[n->p+1] = n->l+1;
		 			last_row_is_empty_row = 1;
		
		 
		 		}else{
		 			if (trovato == 1 ){
		 				// printf("n ->p = %d   current_row[n->p] = %d current level = %d \n",n->p,current_level);
		 				// if(next_row[n->p] != 0)
		 				// 			printf("beccato \n");
		 			 	// for(size_t i = 0; i < size; ++i){
		 			 	// 															printf("%d - ",next_row[i]);
		 			 	// 					}
		 			 	// 					printf("\n");
		 				// printf("passato \n ");
		 				if (current_level != NULL){
							// printf("last row = %d \n", last_row_is_empty_row);
							if (last_row_is_empty_row){																								
																			int* temp = current_row;
																				current_row = next_row;
																				next_row = temp;
																				
																			}
		 					if (current_row[n->p] == current_level || ( current_row[n->p] >=1 && current_row[n->p] < 8) || ( next_row[n->p] >=1 && next_row[n->p] < 8)){
		 							
	
									printf(" (%d,%d) ", n->p, n->l);
									last_row_is_empty_row = 0;
									ListInsert( &catasta_list, n->p ,n->l);
										            current_row[n->p] = 0;
													next_row[n->p-1] = n->l+1;
													next_row[n->p] = n->l+1;
													next_row[n->p+1] = n->l+1;																										next_row[n->p+1] = n->l-1;
					}
				}
			}
		}
			
	acatasta(n->left,nil);
	
	
	} 
}
void scatasta(rbnode *n, rbnode *nil){
	if(n != nil) {
		scatasta(n->left,nil);
		// se abbiamo iniziato 
	    if (current_level == NULL)
		   	  current_level = n->l;
		// se c'è un cambio di livello
   	    if ( n->l != current_level && n->l != catasta_node->l && next_row != NULL){
			current_level = n->l;
			int* temp = current_row;
			current_row = next_row;
			next_row = temp;
		}
	
	   if (catasta_node->p == n->p && catasta_node->l == n->l){
	    	trovato = 1;
		    current_row = malloc((size) * sizeof (int));
		    next_row = malloc((size) * sizeof (int));
		    next_row[n->p-1] = n->l-1;
		    next_row[n->p] = n->l-1;
	    	next_row[n->p+1] = n->l-1;
	    }else{
		if (trovato == 1 ){
			if (current_level != NULL){
				if (current_row[n->p] == current_level || ( current_row[n->p] >=1 && current_row[n->p] < 6)){
					printf(" (%d,%d) ", n->p, n->l);
					ListInsert( &catasta_list, n->p ,n->l);
					current_row[n->p] = 0;
					next_row[n->p-1] = n->l-1;
					next_row[n->p] = n->l-1;
					next_row[n->p+1] = n->l-1;																										next_row[n->p+1] = n->l-1;
				}
			}
		}
	}
	scatasta(n->right,nil);	
	} 
}


list sottocatasta(rbtree* box, int x)

{
	catasta_node = search(box, x, box->c_count[x]);
	
	
	if (catasta_node){
		printf("elemento trovato (%d, %d)", catasta_node->p, catasta_node->l);
		// preparazione variabili globali
		catasta_list = NULL, current_level = NULL;;
		size = box->size;
		trovato = 0;
		// printf("trovato");
		scatasta(box->root, box->nil);
		printf("\n");
		
		// ListPrint(catasta_list);
		return catasta_list;
	}
	
	return catasta_list;
}

list anticatasta(rbtree* box, int x)

{
	catasta_node = search(box, x, box->c_max[x]);
	
	// controllare che non ci siano valori strani nei contatori
	// printf("il column count = %d, il max nella colonna è %d \n ", box->c_count[x], box->c_max[x]);
	if (catasta_node){
		// preparazione variabili globali
		printf("elemento trovato (%d, %d)", catasta_node->p, catasta_node->l);
		catasta_list = NULL, current_level = NULL;
		size = box->size;
		trovato = 0;
		
		// printf("trovato");
		acatasta(box->root, box->nil);
		printf("\n");
		
		// ListPrint(catasta_list);
		return catasta_list;
	}
	
	return NULL;
}

void statistica(int n, int m, int k){
	float media = 0;
	int i = 0;
	init_random_number();
	while(i < k){
		rbtree *box = scatola(m);
		for(size_t j = 0; j < n; ++j)
		{
			while(-1 == inserisci(box,random_number(0,m)));
		}
		media+= (float)( (float) box->h / (float) n);
		free(box);
		i++;
	}
	
		printf("valore medio = %f\n", media/k);
}

int* estrai_in_parallelo(rbtree* box){
	int* free_elements = malloc((box->size) * sizeof (int));
	int j = 0, i = 0, count;
	while (i < box->size){
		    count = 0;
			// metto a 0 il contenuto nella posizione i e i+1 dell'array elementi liberi  O(2)
			free_elements[i] = 0;
			free_elements[i+1] = 0;
	    	
			if(box->c_count[i] == box->c_count[i+1]  // sono uguali 
		      && box->c_count[i+1] != 0 && box->c_count[i] != 0 // c'è qualcosa nella colonna){
				// trovato possibile elemento rettangolo completo
			){
			
			// Caso particolare gradino discende
			if(box->c_count[i-1]>box->c_count[i]){
				int current = box->c_count[i];
				for(int k = i; k < box->size; ++k){
					// printf ("elemento => %d \n",k);			
					if (box->c_count[k] == current)
						count ++;
					else
						break;
				}
			}
			
			free_elements[j] = (count % 2) != 0 ? i+1 : i;
            free_elements[j+1] = box->c_count[i];
			j = j+2;
			i++;
		}
	i++;
	}

	return free_elements;
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




