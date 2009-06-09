#include <stdio.h>
#include "tetris.h"
#include <stdlib.h>

typedef struct node {
  int p;
int l;
  struct node *next;
} node;

typedef node *list;

list NEW() {
  list l = NULL;
  return l;
}

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

int main( void ) {
  list l = NEW();
  int i;
  int j,x;
  srand( time( NULL ) );
  for ( i = 0; i < 10; i++ ) {
    j = rand() % 10;
	x = rand() % 10;
	printf("%d - ",j,x);
    ListInsert( &l, j ,x);
  }
  printf( "\n" );
  ListPrint(l);
}
