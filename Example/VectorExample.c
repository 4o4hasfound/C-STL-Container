#include <stdio.h>
#include "vector.h"

// Create a vector called "IVector"
// All its member function will be prefixed with "ivector"
// The constructor/copy constructor/destructor for its element is NULL,
// meaning the constructor/destructor will be empty,
// and the copy constructor will be assignment
DeclareVector(int, IVector, ivector, NULL, NULL, NULL);


// Create a vector called "EStructVector"
// All its member function will be prefixed with "es_vector"
// The constructor is the function "es_constructor"
// The copy_constructor is the function "es_copy_constructor"
// The destructor is the function "es_destructor"
typedef struct ExampleStruct {
	int* arr;
	int size;
	int dummy_variable[2];
	float key;
} ExampleStruct;
void es_constructor(ExampleStruct* object);
void es_copy_constructor(ExampleStruct* dest, ExampleStruct* from);
void es_destructor(ExampleStruct* object);
// if a < b, returns -1, if a > b, returns 1, if a == b, returns 0
int es_cmp(ExampleStruct* a, ExampleStruct* b);

DeclareVectorCmp(ExampleStruct, EStructVector, es_vector, es_constructor, es_copy_constructor, es_destructor, es_cmp);

// ========== Available functions for the vector ==========
// 
//	vector* function_prefix_create();
//		Allocate an empty vector object, then initialize it before returning it
// 
//	void function_prefix_initialize(vector* vec);
//		Initialize an allocated vector
//		Allocate VECTOR_INITIALIZE_SIZE amount of space for its data
//		
//	void function_prefix_copy(vector* dest, vector* from);
//		Copy a vector from "from" to "dest"
//		"dest" will be initialized, so any data in it will be lost
//		Destroy "dest" or make sure its not initialized to prevent memory leaks
// 
//	void function_prefix_destroy(vector* vec);
//		Free the data the vector allocates
//		This function will NOT free the pointer "vec" itself
//		This could act as a destructor if vector is used in any other containers
// 
//	void function_prefix_destroy_ptr(vector* vec);
//		Free the data the vector allocates
//		This function WILL free the pointer "vec" itself
// 
//	void function_prefix_clear(vector* vec);
//		Call destructor on every element and set the size of "vec" to 0
//
//	void function_prefix_reserve(vector* vec, int size);
//		Reserve atleast "size" amount of space for "vec"
//		If "vec" has space equal or more than "size",
//		then nothing will be done
// 
//	void function_prefix_shrink_to_fit(vector* vec);
//		Shrink the capacity of "vec" to its size
// 
//	void function_prefix_erase(vector* vec, int index);
//		Erase the object located in "index" and call destructor
// 
//	void function_prefix_reverse(vector* vec, int from, int to);
//		Reverse the element of "vec" from index "from" to index "to"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	int function_prefix_find(vector* vec, type object);
//		Returns the index of "object" in "vec"
//		If "object" doesn't exist, then the size of "vec" will be returned
// 
//	int function_prefix_find_cmp(vector* vec, type object, int(*cmp)(type*, type*));
//		Returns the index of "object" in "vec"
//		A custom "cmp" function is used to compare elements
//		If "object" doesn't exist, then the size of "vec" will be returned
//		
//	int function_prefix_find_range(vector* vec, int from, int to, type object);
//		Returns the index of "object" in "vec" from the index "from" to "to"
//		If the index is negative, then it will start counting from the end of the vector
//		If "object" doesn't exist, then the size of "vec" will be returned
// 
//	int function_prefix_find_range_cmp(vector* vec, int from, int to, type object, int(*cmp)(type*, type*));
//		Returns the index of "object" in "vec" from the index "from" to "to"
//		A custom "cmp" function is used to compare elements
//		If the index is negative, then it will start counting from the end of the vector
//		If "object" doesn't exist, then the size of "vec" will be returned
// 
//	void function_prefix_push_back(vector* vec, type object);
//		Push "object" on the back of "vec"
// 
//	void function_prefix_insert(vector* vec, int index, type object);
//		Insert "object" at the position "index" of "vec"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	void function_prefix_resize(vector* vec, int size);
//		Resize "vec" to "size"
//		If any element is not in range of "size", then destructor will be called
//		If any new element is created, the constructor will be called
// 
//	void function_prefix_pop_back(vector* vec);
//		Pop the last element of "vec"
//		Destructor will be called
// 
//	type function_prefix_at(vector* vec, int index);
//		Returns the COPIED element at position "index" of "vec"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	type* function_prefix_at_ptr(vector* vec, int index);
//		Returns the pointer of the element at position "index" of "vec"
// 
//	type* function_prefix_front(vector* vec);
//		Returns the pointer of the first element in "vec"
// 
//	type* function_prefix_back(vector* vec);
//		Returns the pointer of the last element in "vec"
//		
//	bool function_prefix_empty(vector* vec);
//		Returs if "vec" is empty
// 
//	bool function_prefix_equal(vector* a, vector* b);
//		Returs if vector "a" is equal to vector "b"
// 
//	void function_prefix_insert_array(vector* vec, type* other, int index, int size);
//		Insert an array "other" of size "size" into "vec" at position "index"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	void function_prefix_insert_array_range(vector* vec, type* other, int index, int from, int to, int size);
//		Insert an array "other" of size "size" from index "from" to index "to" into "vec" at position "index"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	void function_prefix_insert_vec(vector* vec, vector* other, int index);
//		Insert a vector "other" into "vec" at position "index"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	void function_prefix_insert_vec_range(vector* vec, vector* other, int index, int from, int to);
//		Insert a vector "other" from index "from" to index "to" into "vec" at position "index"
//		If the index is negative, then it will start counting from the end of the vector
// 
//	void function_prefix_reallocate(vector* vec, int size);
//		Reallocate "vec" so that it could hold "size" element
//		If "size" is less than "vec"'s capacity, then nothing will be done
//		
//	void function_prefix_init_element(vector* vec, int from, int to);
//		Call the constructor from index "from" to index "to" in vector "vec"

int main() {
	// Create with pointer
	IVector* ivec = ivector_create();

	// Or create with initialization
	EStructVector es_vec;
	es_vector_initialize(&es_vec);

	ivector_push_back(ivec, 10);
	es_vector_resize(&es_vec, 10);

	// Now es_vec2 and es_vec is equal, although they points to different part of memory
	EStructVector* es_vec2 = (EStructVector*)malloc(sizeof(EStructVector));
	es_vector_copy(es_vec2, &es_vec);

	ExampleStruct tmp;
	es_constructor(&tmp);
	// Tmp will be the 11th element of es_vec2
	es_vector_push_back(es_vec2, tmp);

	// This should be all 1s
	for (int i = 0; i < es_vec2->size; ++i) {
		printf("%d ", es_vector_at_ptr(es_vec2, i)->dummy_variable[0]);
	}
}

void es_constructor(ExampleStruct* object) {
	object->size = 10;
	object->arr = (int*)malloc(sizeof(int) * 10);
	object->key = 0;
	object->dummy_variable[0] = object->dummy_variable[1] = 1;
}
void es_copy_constructor(ExampleStruct* dest, ExampleStruct* from) {
	dest->size = from->size;
	dest->dummy_variable[0] = from->dummy_variable[0];
	dest->dummy_variable[1] = from->dummy_variable[1];
	dest->key = from->key;
	dest->arr = (int*)malloc(sizeof(int) * from->size);
	memcpy(dest->arr, from->arr, sizeof(int) * from->size);
}
void es_destructor(ExampleStruct* object) {
	free(object->arr);
}
int es_cmp(ExampleStruct* a, ExampleStruct* b) {
	if (a->key < b->key) {
		return -1;
	}
	else if (a->key > b->key) {
		return 1;
	}
	return 0;
}