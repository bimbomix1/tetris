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
	// statistica(800,40,2000);
	
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
		assert_equal(0, inserisci(box,3));
				assert_equal(0, inserisci(box,2));
				assert_equal(0, inserisci(box,5));
				assert_equal(0, inserisci(box,5));
				assert_equal(0, inserisci(box,5));
				assert_equal(0, inserisci(box,5));
	// assert_not_equal(NULL, sottocatasta(box,1));
	// assert_equal(-1, sottocatasta(box,0));
	// assert_equal(-1, sottocatasta(box,2));  // decommenta
	visualizza(box);

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
	//rbtree
	add_test(suite,should_create_a_tree);
	add_test(suite,should_insert_element);
	add_test(suite,should_remove_an_item);
	// add_test(suite,should_remove_many_items);  sistemare non cancella se ci sono solo 2 elementi
	add_test(suite,should_search_many_items);
	//tools
	add_test(suite,test_is_lower_than);
	// scatola(x)
	add_test(suite,should_create_a_box);
	add_test(suite,should_not_create_a_box_with_size_zero);
	add_test(suite,should_not_create_a_box_with_size_one);
	// inserisci(x)
	add_test(suite,should_not_insert_element_in_small_box);
	add_test(suite,should_not_insert_in_box);
	add_test(suite,test_c_count);
	add_test(suite,should_insert_sequence_1);
	add_test(suite,should_insert_sequence_2);
	add_test(suite,should_insert_sequence_3);
	add_test(suite,should_insert_sequence_4);
	add_test(suite,should_insert_sequence_5);
	add_test(suite,should_insert_sequence_6);
	add_test(suite,should_insert_sequence_7);
	add_test(suite,should_insert_sequence_8);	
	// elimina (x)
	
	// estrazione in parallelo
	add_test(suite,should_extract_in_parallel_1);
	add_test(suite,should_extract_in_parallel_2);
	
	//statistica
	add_test(suite,should_get_statistica);
	
	//sottocastasta(x)
	add_test(suite,should_get_sottocatasta_1);
	
	// is_block ?
	add_test(suite, should_find_if_is_block_1);
	add_test(suite, should_find_if_is_block_2);
	add_test(suite, should_find_if_is_block_3);
	add_test(suite, should_find_if_is_block_4);
	add_test(suite, should_find_if_is_block_5);
	return run_test_suite(suite, create_text_reporter());
	
}