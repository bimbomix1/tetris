#include "tetris.h"
#include "cgreen/cgreen.h"


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
	assert_not_equal(NULL,box->columns_counter);
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
}

void should_not_insert_element_in_small_box(){
	rbtree *box = scatola(2);
	assert_equal(-1,inserisci(box,1));
}

void test_columns_counter(){
	rbtree *box = scatola(5);
	assert_equal(0,inserisci(box,1));
	//column counter
	assert_equal(0,box->columns_counter[0]);
	assert_equal(1,box->columns_counter[1]);
	assert_equal(1,box->columns_counter[2]);
	assert_equal(0,inserisci(box,2));
	assert_equal(0,box->columns_counter[0]);
	assert_equal(1,box->columns_counter[1]);
	assert_equal(2,box->columns_counter[2]);
	assert_equal(2,box->columns_counter[3]);
}




int main(int argc, char **argv) {
	TestSuite *suite = create_test_suite();
	// rbtree
	add_test(suite,should_create_a_tree);
	add_test(suite,should_insert_element);
	//tools
	add_test(suite,test_is_lower_than);
	// scatola(x)
	add_test(suite,should_create_a_box);
	add_test(suite,should_not_create_a_box_with_size_zero);
	add_test(suite,should_not_create_a_box_with_size_one);
	// inserisci(x)
	add_test(suite,should_not_insert_element_in_small_box);
	add_test(suite,should_not_insert_in_box);
	add_test(suite,test_columns_counter);
	
	return run_test_suite(suite, create_text_reporter());
}