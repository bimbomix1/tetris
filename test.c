#include "tetris.h"
#include "cgreen/cgreen.h"
#include <stdio.h>

// Rbtree
void should_create_a_tree(){
	rbtree *box = createrbtree();
	assert_not_equal(NULL,box);
}

void should_insert_element(){
	rbtree *box = createrbtree();
	rbinsert(box,2,2);
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(NULL,search(box,0,0));
	rbinsert(box,0,1);
	assert_not_equal(NULL,search(box,0,1));
	rbinsert(box,0,0);
	assert_not_equal(NULL,search(box,0,0));
	rbinsert(box,2,0);
	assert_not_equal(NULL,search(box,2,0));
}

void should_remove_an_item(){
	rbtree *box = createrbtree();
	rbinsert(box,3,2);
	rbnode* node = search(box,3,2);
	assert_not_equal(NULL,node);
	// printf("prima =============== \n");
	// display(box);
	rbdelete(box,node);
	// printf("\n dopo =============== \n");
	// display(box);
	// printf("\n \n");
	node = search(box,3,2);
	// display(box);

	

}

void should_remove_many_items(){
	rbtree *box = createrbtree();
	rbinsert(box,3,1);
	rbinsert(box,4,1);
	rbinsert(box,1,1);
	rbinsert(box,8,1);
	rbinsert(box,2,1);
	rbinsert(box,5,3);
	rbinsert(box,2,2);
	rbinsert(box,2,3);
	rbinsert(box,2,4);
	
	display(box);
	printf("\n");
	rbnode* node = search(box,2,1);
	rbdelete(box,node);
	assert_equal(NULL, search(box,2,1));
	node = search(box,13,1);
	
	assert_not_equal(NULL, search(box,3,1));
	rbdelete(box,search(box,3,1));
	assert_equal(NULL, search(box,3,1));
	
	assert_not_equal(NULL, search(box,1,1));
	rbdelete(box,search(box,1,1));
	assert_equal(NULL, search(box,1,1));
	
	assert_not_equal(NULL, search(box,4,1));
	rbdelete(box,search(box,4,1));
	assert_equal(NULL, search(box,4,1));
	
	assert_not_equal(NULL, search(box,2,4));
	rbdelete(box,search(box,2,4));
	assert_equal(NULL, search(box,2,4));
	
	assert_not_equal(NULL, search(box,2,2));
	rbdelete(box,search(box,2,2));
	assert_equal(NULL, search(box,2,2));
	
	assert_not_equal(NULL, search(box,2,3));
	rbdelete(box,search(box,2,3));
	assert_equal(NULL, search(box,2,3));
	
	rbinsert(box,5,5);
	
	assert_not_equal(NULL, search(box,5,3));
	rbdelete(box,search(box,5,3));
	assert_equal(NULL, search(box,5,3));
	
	assert_not_equal(NULL, search(box,8,1));
	rbdelete(box,search(box,8,1));
	assert_equal(NULL, search(box,8,1));
	
	assert_not_equal(NULL, search(box,5,5));
	rbdelete(box,search(box,5,5));
	assert_equal(NULL, search(box,5,5));
	
	display(box);

}
void should_search_many_items(){
	rbtree *box = createrbtree();
	rbinsert(box,3,1);
	rbnode *node = search(box,2,1);
	assert_equal(NULL,node);
	node = search(box,4,1);
	assert_equal(NULL,node);
	node = search(box,5,1);
	assert_equal(NULL,node);
	node = search(box,7,1);
	assert_equal(NULL,node);
	node = search(box,9,1);
	assert_equal(NULL,node);
	node = search(box,3,1);
	assert_not_equal(NULL,node);
	rbinsert(box,5,1);
	node = search(box,8,1);
	assert_equal(NULL,node);
	node = search(box,5,1);
	assert_not_equal(NULL,node);
	// visualizza(box);
}
// tools
void test_is_lower_than(){
	assert_equal(0, is_lower_than(0,0,0,0));
	assert_equal(-1, is_lower_than(0,0,1,0));
	assert_equal(-1, is_lower_than(1,0,2,0));
	assert_equal(1, is_lower_than(3,-4,0,-3));
	assert_equal(-1, is_lower_than(0,-2,0,-3));
	assert_equal(1, is_lower_than(0,-3,0,-2));
	assert_equal(-1, is_lower_than(0,-4,1,-4));
	assert_equal(-1, is_lower_than(0,8,0,6));
	assert_equal(0, is_lower_than(0,8,0,8));
	assert_equal(-1,is_lower_than(0,-3,2,-3));
	assert_equal(1,is_lower_than(0,-4,4,-3));
	assert_equal(1,is_lower_than(2,-4,2,-3));
	assert_equal(-1,is_lower_than(-1,0,0,0));
	assert_equal(1,is_lower_than(0,-4,2,-2));
	assert_equal(-1,is_lower_than(2,-4,3,-4));
	assert_equal(1,is_lower_than(3,-4,2,-4));
	assert_equal(1,is_lower_than(0,-4,0,-2));
	assert_equal(1,is_lower_than(0,-4,4,-1));
	assert_equal(-1,is_lower_than(0,0,0,-1)); // MUST FALSE
	assert_equal(-1,is_lower_than(0,1,1,1));
	assert_equal(1,is_lower_than(1,1,0,1));
	assert_equal(-1,is_lower_than(2,1,3,1));
	assert_equal(1,is_lower_than(3,1,2,1));
	assert_equal(1,is_lower_than(0,0,-1,0));
	assert_equal(-1,is_lower_than(3,0,0,-1));
	assert_equal(1,is_lower_than(0,-1,3,0));
	assert_equal(-1,is_lower_than(2,0,2,-1));
	assert_equal(-1,is_lower_than(1,3,2,-3));
}


// scatola(x)
void should_create_a_box(){
	rbtree *box = scatola(5);
	assert_not_equal(NULL,box);
	assert_not_equal(NULL,box->c_count);
	assert_equal(5,box->size);
	free(box);
}

void should_not_create_a_box_with_size_zero(){
	rbtree *box = scatola(0);
	assert_equal(NULL,box);
}

void should_not_create_a_box_with_size_one(){
	rbtree *box = scatola(1);
	assert_equal(NULL,box);	
}

// * manca lo svuotamento dei pezzi

// inserisci(x)
void should_not_insert_in_box(){
	rbtree *box = scatola(5);
	assert_equal(0,inserisci(box,3));
	assert_equal(0,inserisci(box,1));
	
	assert_equal(0,inserisci(box,2)); // pay attention
	assert_equal(2,box->h);
}

void should_not_insert_element_in_small_box(){
	rbtree *box = scatola(2);
	assert_equal(-1,inserisci(box,1));
	assert_equal(0,box->h);
	
}

void should_insert_sequence_1(){
	rbtree *box = scatola(5);
	assert_equal(-1, inserisci(box,5));
	// inserisci pezzo posizione 2 
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,1));
	assert_equal(0,box->c_count[0]);
	assert_equal(0,box->c_count[1]);
	assert_equal(1,box->c_count[2]);
	assert_equal(1,box->c_count[3]);
	// inserisci pezzo posizione 1
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,2));
	assert_equal(0,box->c_count[0]);
	assert_equal(2,box->c_count[1]);
	assert_equal(2,box->c_count[2]);
	assert_equal(1,box->c_count[3]);
	assert_equal(0,box->c_count[0]);
	// inserisci pezzo posizione 1
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,2));
	assert_equal(0,box->c_count[0]);
	assert_equal(2,box->c_count[1]);
	assert_equal(2,box->c_count[2]);
	assert_equal(2,box->c_count[3]);
	assert_equal(2,box->c_count[4]);
	assert_equal(-1, inserisci(box,4));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,3));
	assert_equal(0,box->c_count[0]);
	assert_equal(2,box->c_count[1]);
	assert_equal(2,box->c_count[2]);
	assert_equal(3,box->c_count[3]);
	assert_equal(3,box->c_count[4]);
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,4));
	assert_equal(0,box->c_count[0]);
	assert_equal(2,box->c_count[1]);
	assert_equal(4,box->c_count[2]);
	assert_equal(4,box->c_count[3]);
	assert_equal(3,box->c_count[4]);
	assert_equal(4,box->h);
	
	//free(box);
	//visualizza(box);
}

void should_insert_sequence_2(){
	rbtree *box = scatola(9);
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(1,box->c_count[1]);
	assert_equal(1,box->c_count[2]);

	
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,1));
	assert_equal(1,box->c_count[1]);
	assert_equal(1,box->c_count[2]);
	assert_equal(1,box->c_count[4]);
	assert_equal(1,box->c_count[5]);
	
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(1,box->c_count[1]);
	assert_equal(2,box->c_count[2]);
	assert_equal(2,box->c_count[3]);
	assert_equal(1,box->c_count[4]);
	assert_equal(1,box->c_count[5]);

	assert_equal(0, inserisci(box,5));
	assert_not_equal(NULL,search(box,5,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,3));
	assert_equal(0, inserisci(box,6));
	assert_not_equal(NULL,search(box,6,3));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,4));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,4));
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,5));
	
	assert_equal(5,box->c_count[0]);
	assert_equal(5,box->c_count[1]);
	assert_equal(4,box->c_count[2]);
	assert_equal(4,box->c_count[3]);
	assert_equal(4,box->c_count[4]);
	assert_equal(2,box->c_count[5]);
	assert_equal(3,box->c_count[6]);
	assert_equal(3,box->c_count[7]);
	assert_equal(5,box->h);
	
//	visualizza(box);

}
void test_c_count(){
	rbtree *box = scatola(5);
	assert_equal(0,box->c_count[0]);
	assert_equal(0,box->c_count[1]);
	assert_equal(0,box->c_count[2]);
	assert_equal(0,box->c_count[3]);
	assert_equal(0,inserisci(box,1));
	//column counter
	assert_equal(0,box->c_count[0]);
	assert_equal(1,box->c_count[1]);
	assert_equal(1,box->c_count[2]);
	assert_equal(0,box->c_count[3]);
	assert_equal(0,inserisci(box,2));
	assert_equal(0,box->c_count[0]);
	assert_equal(1,box->c_count[1]);
	assert_equal(2,box->c_count[2]);
	assert_equal(2,box->c_count[3]);
	assert_equal(0,box->c_count[4]);
	assert_equal(0,inserisci(box,1));
	assert_equal(0,box->c_count[0]);
	assert_equal(3,box->c_count[1]);
	assert_equal(3,box->c_count[2]);
	assert_equal(2,box->c_count[3]);
	assert_equal(0,box->c_count[4]);
	assert_equal(0,inserisci(box,3));
	assert_equal(0,box->c_count[0]);
	assert_equal(3,box->c_count[1]);
	assert_equal(3,box->c_count[2]);
	assert_equal(3,box->c_count[3]);
	assert_equal(3,box->c_count[4]);
	assert_equal(0,inserisci(box,2));
	assert_equal(0,box->c_count[0]);
	assert_equal(3,box->c_count[1]);
	assert_equal(4,box->c_count[2]);
	assert_equal(4,box->c_count[3]);
	assert_equal(3,box->c_count[4]);
	assert_equal(4,box->h);
	
//	visualizza(box);
}


void should_extract_in_parallel_1(){
	rbtree *box = scatola(6);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,1));
	// display(box);
	free_elements = (int*) estrai_in_parallelo(box);
	assert_equal(1,free_elements[0]);
	assert_equal(1,free_elements[1]);
	assert_equal(4,free_elements[2]);
	assert_equal(1,free_elements[3]);
	
}

void should_extract_in_parallel_2(){
	rbtree *box = scatola(6);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,1));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,3));
	free_elements = (int*) estrai_in_parallelo(box);
	assert_equal(1,free_elements[0]);
	assert_equal(3,free_elements[1]);
	assert_equal(0,free_elements[2]);
	assert_equal(0,free_elements[3]);
	assert_equal(0,free_elements[4]);
	assert_equal(0,free_elements[5]);

	
}

void should_insert_sequence_3(){
	rbtree *box = scatola(6);
	int* free_elements;
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,1));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,1));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,3));
	free_elements = (int*) estrai_in_parallelo(box);
	assert_equal(0,free_elements[0]);
	assert_equal(1,free_elements[1]);
	assert_equal(3,free_elements[2]);
	assert_equal(3,free_elements[3]);
	assert_equal(0,free_elements[4]);
	assert_equal(0,free_elements[5]);

	
}

void should_insert_sequence_4(){
	rbtree *box = scatola(11);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,1));
	assert_equal(0, inserisci(box,8));
	assert_not_equal(NULL,search(box,8,1));
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,2));
	assert_equal(0, inserisci(box,7));
	assert_not_equal(NULL,search(box,7,2));
	assert_equal(0, inserisci(box,9));
	assert_not_equal(NULL,search(box,9,2));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,3));
	assert_equal(0, inserisci(box,6));
	assert_not_equal(NULL,search(box,6,3));
	assert_equal(0, inserisci(box,5));
	assert_not_equal(NULL,search(box,5,4));
	
	
	free_elements = (int*) estrai_in_parallelo(box);
	assert_equal(0,free_elements[0]);
	assert_equal(2,free_elements[1]);
	assert_equal(2,free_elements[2]);
	assert_equal(2,free_elements[3]);
	assert_equal(5,free_elements[4]);
	assert_equal(4,free_elements[5]);
	assert_equal(9,free_elements[6]);
	assert_equal(2,free_elements[7]);
	assert_equal(0,free_elements[8]);
	assert_equal(0,free_elements[9]);
    assert_equal(0,free_elements[10]);
	// visualizza(box);
}

void should_insert_sequence_5(){
	rbtree *box = scatola(11);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,6));
	assert_not_equal(NULL,search(box,6,1));
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,5));
	assert_not_equal(NULL,search(box,5,2));
	assert_equal(0, inserisci(box,8));
	assert_not_equal(NULL,search(box,8,1));
	free_elements = (int*) estrai_in_parallelo(box);
	assert_equal(0,free_elements[0]);
	assert_equal(2,free_elements[1]);
	assert_equal(2,free_elements[2]);
	assert_equal(3,free_elements[3]);
	assert_equal(5,free_elements[4]);
	assert_equal(2,free_elements[5]);
	assert_equal(8,free_elements[6]);
	assert_equal(1,free_elements[7]);
	assert_equal(0,free_elements[8]);
	assert_equal(0,free_elements[9]);
    assert_equal(0,free_elements[10]);
	// visualizza(box);
}

void should_insert_sequence_6(){
	rbtree *box = scatola(11);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,9));
	assert_not_equal(NULL,search(box,9,1));
	assert_equal(0, inserisci(box,8));
	assert_not_equal(NULL,search(box,8,2));
	assert_equal(0, inserisci(box,7));
	assert_not_equal(NULL,search(box,7,3));
	assert_equal(0, inserisci(box,6));
	assert_not_equal(NULL,search(box,6,4));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,3));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,4));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,5));
	free_elements = (int*) estrai_in_parallelo(box);
	
	assert_equal(4,free_elements[0]);
	assert_equal(5,free_elements[1]);
	assert_equal(6,free_elements[2]);
	assert_equal(4,free_elements[3]);
	assert_equal(0,free_elements[4]);
	assert_equal(0,free_elements[5]);
	assert_equal(0,free_elements[6]);
	assert_equal(0,free_elements[7]);
	assert_equal(0,free_elements[8]);
	assert_equal(0,free_elements[9]);
	assert_equal(0,free_elements[10]);
	// visualizza(box);
}

void should_insert_sequence_7(){
	rbtree *box = scatola(11);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,1));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,5));
	assert_not_equal(NULL,search(box,5,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,3));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,4));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,4));
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,5));
	free_elements = (int*) estrai_in_parallelo(box);
	assert_equal(0,free_elements[0]);
	assert_equal(5,free_elements[1]);
	assert_equal(3,free_elements[2]);
	assert_equal(4,free_elements[3]);
	assert_equal(5,free_elements[4]);
	assert_equal(2,free_elements[5]);
	assert_equal(0,free_elements[6]);
	assert_equal(0,free_elements[7]);
	assert_equal(0,free_elements[8]);
	assert_equal(0,free_elements[9]);
	assert_equal(0,free_elements[10]);
	// visualizza(box);
	// display(box);
}

void should_insert_sequence_8(){
	rbtree *box = scatola(11);
	int* free_elements;
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,1));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,5));
	assert_not_equal(NULL,search(box,5,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,3));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,4));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,4));
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,5));
	assert_equal(0, inserisci(box,7));
	assert_not_equal(NULL,search(box,7,1));
	assert_equal(0, inserisci(box,7));
	assert_not_equal(NULL,search(box,7,2));
	free_elements = (int*) estrai_in_parallelo(box);

	assert_equal(0,free_elements[0]);
	assert_equal(5,free_elements[1]);
	assert_equal(3,free_elements[2]);
	assert_equal(4,free_elements[3]);
	assert_equal(5,free_elements[4]);
	assert_equal(2,free_elements[5]);
	assert_equal(7,free_elements[6]);
	assert_equal(2,free_elements[7]);
	assert_equal(0,free_elements[8]);
	assert_equal(0,free_elements[9]);
	assert_equal(0,free_elements[10]);
	// visualizza(box);
	// display(box);
}


void should_get_statistica(){
	rbtree *box = scatola(11);
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	assert_equal(0, inserisci(box,4));
	assert_not_equal(NULL,search(box,4,1));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,2));
	assert_equal(0, inserisci(box,5));
	assert_not_equal(NULL,search(box,5,2));
	assert_equal(0, inserisci(box,2));
	assert_not_equal(NULL,search(box,2,3));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,4));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL,search(box,3,4));
	assert_equal(0, inserisci(box,0));
	assert_not_equal(NULL,search(box,0,5));
	// inserisci n elementi in una scatolad i dimensioni m  20 volte
	statistica(60,10,100);
	
}

void should_get_sottocatasta_1(){
	rbtree *box = scatola(11);
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,search(box,1,1));
	// assert_not_equal(NULL, sottocatasta(box,1));
	// assert_equal(-1, sottocatasta(box,0));
	// assert_equal(-1, sottocatasta(box,2));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,6));
	assert_equal(0, inserisci(box,5));
	list l = sottocatasta(box,5);
	assert_not_equal(NULL, l);
	assert_equal(6, l->p);
	assert_equal(6, l->l);
	l = l->next;
	assert_equal(5, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(5, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(NULL, l);
}


void should_get_sottocatasta_2(){
	rbtree *box = scatola(11);
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,5));
	list l = sottocatasta(box,4);
	assert_equal(NULL, l);
	l = sottocatasta(box,5);
	assert_equal(4, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(5, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(NULL, l);
	l = sottocatasta(box,0);
	assert_equal(1, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(NULL, l);
	l = sottocatasta(box,3);
	assert_equal(4, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(5, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(1, l->l);
}
void should_get_sottocatasta_3(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,7));
	assert_equal(0, inserisci(box,4));
	assert_equal(NULL,sottocatasta(box,0));
	assert_not_equal(NULL,l = sottocatasta(box,1));
	assert_equal(2, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_not_equal(NULL,l = sottocatasta(box,3));
	assert_equal(2, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(NULL,l);
}

void should_get_sottocatasta_4(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,9));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,7));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	// visualizza(box);
	
	assert_not_equal(NULL,l = sottocatasta(box,2));
	assert_equal(3, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(1, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(4, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(5, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(NULL,l);
}

void should_get_sottocatasta_5(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,l = sottocatasta(box,1));
	
	assert_equal(2, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_equal(NULL,l);
	assert_not_equal(NULL,l = sottocatasta(box,2));
	printf("lista eccola \n ");
	ListPrint(l);
	printf("\n");
	assert_equal(3, l->p);
	assert_equal(1, l->l);
	l = l->next;
	visualizza(box);
}

void should_get_sottocatasta_6(){ 
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL,l = sottocatasta(box,1));
	// visualizza(box);
}

void should_get_sottocatasta_esempio_requisiti(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	// visualizza(box);
	assert_not_equal(NULL,l = sottocatasta(box,2));	
	assert_equal(3, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(1, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(1, l->p);
	assert_equal(1, l->l);
	l = l->next;
	assert_not_equal(NULL,l);
	// assert_equal(4, l->p);
	// 	assert_equal(1, l->l);
	// 	l = l->next;
}

void should_get_anticatasta_1(){
	rbtree *box = scatola(11);
	list l = NULL;
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,9));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,7));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	assert_equal(NULL,l = anticatasta(box,2));
	assert_equal(NULL,l = anticatasta(box,0));
	l = anticatasta(box,4);
		assert_equal(NULL, l);
	
	assert_not_equal(NULL, l = anticatasta(box,1));

	assert_equal(2, l->p);
		assert_equal(5, l->l);
				l = l->next;
		
				assert_equal(NULL, l = anticatasta(box,6));

	
	//visualizza(box);
}

void should_get_anticatasta_3(){
	rbtree *box = scatola(11);
	list l = NULL;
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,9));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,7));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	assert_equal(NULL,l);
	// visualizza(box);
	
	// l = NULL;
	assert_not_equal(NULL, l = anticatasta(box,3));
	assert_equal(4, l->p);
		assert_equal(5, l->l);
		l = l->next;
		assert_equal(2, l->p);
			assert_equal(5, l->l);
			l = l->next;
			assert_equal(NULL,l);
			
	assert_not_equal(NULL,l = anticatasta(box,7));

		assert_equal(8, l->p);
			assert_equal(2, l->l);
			l = l->next;
	assert_equal(8, l->p);
		assert_equal(3, l->l);
		l = l->next;
	assert_equal(NULL,l);

	printf("\n");
}
void should_get_anticatasta_2(){
	rbtree *box = scatola(11);
	list l;
	
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,5));
	assert_equal(NULL, l = anticatasta(box,0));
	assert_not_equal(NULL, l = anticatasta(box,1));
	assert_equal(0, l->p);
	assert_equal(2, l->l);
	l = l->next;
	assert_equal(NULL,l);
	assert_equal(NULL, l = anticatasta(box,2));
	assert_equal(NULL, l = anticatasta(box,3));
	assert_not_equal(NULL, l = anticatasta(box,4));
	assert_equal(5, l->p);
	assert_equal(6, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(6, l->l);
	l = l->next;
	assert_equal(NULL,l);
	
	assert_equal(NULL, l = anticatasta(box,5));	
	assert_equal(NULL, l = anticatasta(box,6));
	// visualizza(box);

}
void should_get_anticatasta(){
	rbtree *box = scatola(11);
		list l;
		assert_equal(0, inserisci(box,2));
		assert_equal(0, inserisci(box,4));
		assert_equal(0, inserisci(box,5));
		assert_equal(0, inserisci(box,3));
		assert_equal(0, inserisci(box,2));
		assert_equal(0, inserisci(box,5));
		assert_equal(0, inserisci(box,1));
		assert_equal(0, inserisci(box,3));
		assert_equal(0, inserisci(box,7));
		assert_equal(0, inserisci(box,4));
		assert_equal(NULL, l = anticatasta(box,0));
		assert_equal(NULL, l = anticatasta(box,1));
		assert_not_equal(NULL, l = anticatasta(box,2));
		assert_equal(3, l->p);
		assert_equal(4, l->l);
		l = l->next;
		assert_equal(1, l->p);
		assert_equal(4, l->l);
		l = l->next;
		assert_equal(4, l->p);
		assert_equal(5, l->l);
		l = l->next;
		assert_equal(NULL,l);
		assert_not_equal(NULL, l = anticatasta(box,3));
		assert_equal(4, l->p);
		assert_equal(5, l->l);
		l = l->next;
		assert_equal(NULL,l);
		//visualizza(box);
		// display(box);
		// visualizza(box);
}

void should_get_anticatasta_4(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,9));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,7));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,8));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,4));
	assert_equal(NULL, l = anticatasta(box,0));
	assert_not_equal(NULL, l = anticatasta(box,1));
	assert_equal(2, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL, l = anticatasta(box,1));
	assert_equal(2, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(6, l->l);
	l = l->next;
	assert_equal(NULL, l);
	// visualizza(box);
}

void should_get_anticatasta_5(){
	rbtree *box = scatola(11);
		list l;
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,4));
	assert_equal(0, inserisci(box,5));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL, l = anticatasta(box,1));
	assert_equal(2, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(6, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(7, l->l);
	l = l->next;
	assert_equal(NULL,l);
	assert_not_equal(NULL, l = anticatasta(box,4));
	assert_equal(5, l->p);
	assert_equal(5, l->l);
		l = l->next;
	assert_equal(3, l->p);
	assert_equal(7, l->l);
	l = l->next;
	assert_equal(NULL, l);
	// visualizza(box);
	// printf("\n");
}

void should_get_anticatasta_6(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL, l = anticatasta(box,0));
	assert_equal(1, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(NULL,l);
	assert_equal(NULL, l = anticatasta(box,1));
	assert_not_equal(NULL, l = anticatasta(box,2));
	assert_equal(1, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(NULL,l);
}

void should_get_anticatasta_7(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,1));
	assert_not_equal(NULL, l = anticatasta(box,0));
	assert_equal(1, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(NULL,l);
	assert_equal(NULL, l = anticatasta(box,1));
	assert_not_equal(NULL, l = anticatasta(box,2));
	assert_equal(1, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(NULL,l);

}

void should_get_anticatasta_8(){
	
}
void should_get_anticatasta_esempio_requisiti(){
	rbtree *box = scatola(11);
	list l;
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,3));
	assert_equal(0, inserisci(box,0));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,2));
	assert_equal(0, inserisci(box,1));
	assert_equal(0, inserisci(box,3));
	assert_not_equal(NULL, l = anticatasta(box,0));
	assert_equal(1, l->p);
	assert_equal(3, l->l);
	l = l->next;
	assert_equal(2, l->p);
	assert_equal(4, l->l);
	l = l->next;
	assert_equal(3, l->p);
	assert_equal(5, l->l);
	l = l->next;	
	assert_equal(1, l->p);
	assert_equal(5, l->l);
	l = l->next;
	assert_equal(NULL, l);
	// visualizza(box);
}

void should_find_if_is_block_1(){
	
}

void should_find_if_is_block_2(){
	
}
void should_find_if_is_block_3(){
	
}
void should_find_if_is_block_4(){
	
}
void should_find_if_is_block_5(){
	
}

int main(int argc, char **argv) {
	TestSuite *suite = create_test_suite();
	TestSuite *suite1 = create_test_suite();
		
	// REDBLACK THREE	
	TestSuite *structure_tests = create_test_suite();
	add_test(structure_tests,should_create_a_tree);
	add_test(structure_tests,should_insert_element);
	add_test(structure_tests,should_remove_an_item);
	// add_test(structure_tests,should_remove_many_items);  //sistemare non cancella se ci sono solo 2 elementi
	add_test(structure_tests,should_search_many_items);
	run_test_suite(structure_tests, create_text_reporter());
	
	
	// FUNZIONI DI UTILITA'
	TestSuite *tools_tests = create_test_suite();
	add_test(tools_tests,test_is_lower_than);
	add_test(tools_tests,should_extract_in_parallel_1);
	add_test(tools_tests,should_extract_in_parallel_2);
	run_test_suite(tools_tests, create_text_reporter());
		
		
	// SCATOLA	
	TestSuite *scatola_tests = create_test_suite();
	add_test(scatola_tests,should_create_a_box);
	add_test(scatola_tests,should_not_create_a_box_with_size_zero);
	add_test(scatola_tests,should_not_create_a_box_with_size_one);
	run_test_suite(scatola_tests, create_text_reporter());

	// INSERISCI 	
	TestSuite *inserisci_tests = create_test_suite();
	add_test(inserisci_tests,should_not_insert_element_in_small_box);
	add_test(inserisci_tests,should_not_insert_in_box);
	add_test(inserisci_tests,test_c_count);
	add_test(inserisci_tests,should_insert_sequence_1);
	add_test(inserisci_tests,should_insert_sequence_2);
	add_test(inserisci_tests,should_insert_sequence_3);
	add_test(inserisci_tests,should_insert_sequence_4);
	add_test(inserisci_tests,should_insert_sequence_5);
	add_test(inserisci_tests,should_insert_sequence_6);
	add_test(inserisci_tests,should_insert_sequence_7);
	add_test(inserisci_tests,should_insert_sequence_8);
	run_test_suite(inserisci_tests, create_text_reporter());
	
	// STATISTICA
	TestSuite *statistica_tests = create_test_suite();
	add_test(suite,statistica_tests);
	run_test_suite(statistica_tests, create_text_reporter());
	
	// ANTICATASTA
	TestSuite *anticatasta_tests = create_test_suite();
	add_test(anticatasta_tests, should_get_anticatasta_1);
	add_test(anticatasta_tests, should_get_anticatasta_2);
	add_test(anticatasta_tests, should_get_anticatasta_3);
	add_test(anticatasta_tests, should_get_anticatasta_4);
	add_test(anticatasta_tests, should_get_anticatasta_5);
	add_test(anticatasta_tests, should_get_anticatasta_6);
	add_test(anticatasta_tests, should_get_anticatasta_7);
	add_test(anticatasta_tests, should_get_anticatasta_8);
	add_test(anticatasta_tests,should_get_anticatasta_esempio_requisiti);
	run_test_suite(anticatasta_tests, create_text_reporter());
	
	
	// CATASTA
	TestSuite *catasta_tests = create_test_suite();
	add_test(catasta_tests,should_get_sottocatasta_1);
	add_test(catasta_tests,should_get_sottocatasta_2);
	add_test(catasta_tests,should_get_sottocatasta_3);
	add_test(catasta_tests,should_get_sottocatasta_4);
	add_test(catasta_tests,should_get_sottocatasta_5);
	add_test(catasta_tests,should_get_sottocatasta_6);
	run_test_suite(catasta_tests, create_text_reporter());

		// 
		// run_test_suite(suite, create_text_reporter());
		// add_test(suite1, should_find_if_is_block_1);
		// add_test(suite1, should_find_if_is_block_2);
		// add_test(suite1, should_find_if_is_block_3);
		// add_test(suite1, should_find_if_is_block_4);
		// add_test(suite1, should_find_if_is_block_5);
		// run_test_suite(suite1, create_text_reporter());
		return 0;
	
}

