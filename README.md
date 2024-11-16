# C STL Container  
  
## About the Proejct  
This is an attempt of me writing some C++ STL container using C, this includes:  
- vector  
- map  
- unordered_map  
- set  
- unordered_set  
- pair  
  
Every container above will include constructor, copy_contsructor and destructor to manage its data. This make it possible to put a container inside another container inside another...  
  
In order to mimic templates in C++, every container allowed generic type and custom cmp/hash/prpobe function in their declaration.   
  
## Usage  
Every container includes a declaration macro. Generally you need to pass:  
- type use in the container  
- name for the struct of the container  
- prefix name for all the "member" functions  
- constructor for the type  
- copy_constructor for the type  
- destructor for the type  
  
Other possible parameter is custom cmp/hash/probe function.  
  
To use a container, use the declaration macro to declare a struct and functions for the container. Then you can use it however you want!  
  
An example of using a vector containing int  
```c  
DeclareVector(int, IVector, ivector, NULL, NULL, NULL)  
IVector ivector;  
```  
  
## Some Common functions  
Every container has a function of:  
- create  
	returns a pointer of a allocated and initialized container  
- initialize  
	initialize the passed in pointer  
- copy  
	copy a container from a to b  
- destroy  
	free the data stored in the container  
- destroy_ptr  
	free the data stored in the container and the pointer itself  
  
## Container or type  
- [Vector](#vector)  
- [Map](#map)  
- [Unordered Map](#unordered_map)  
- [Set](#set)   
- [Unordered Set](#unordered_set)  
- [Pair](#pair)  
  
# vector  
- [top](#c-stl-container)  
## Table of content  
- [How to Declare a Vector](#how-to-declare-a-vector)  
- [Available Vector Functions](#availble-vector-functions)  
- [Vector Iterate Method](#vector-iterate-method)  
  
## How to Declare a Vector  
- [vector](#vector)  
  
1. `DeclareVector(type, name, void function_prefix, constructor, copy_constructor, destructor)`  
  
2. `DeclareVectorCmp(type, name, void function_prefix, constructor, copy_constructor, destructor, cmp)`  
  
    - type  
        - type of the element in the vector  
    - name  
        - the name of the vector struct  
    - function_prefix  
        - every function will be prefixed with void function_prefix  
    - constructor  
        - the constructor for "type", pass NULL to use the default constructor(which is empty)  
    - copy_constructor  
        - the copy_constructor for "type", pass NULL to use the default copy_constructor(which is empty)  
    - destructor  
        - the destructor for "type", pass NULL to use the default destructor(which is empty)  
    - cmp  
        - the comparitor for "type"  
  
## Availble Vector Functions   
- [vector](#vector)  
#### 1. Creation and Initialization  
- `vector* function_prefix_create()`  
    Allocate an empty vector object, then initialize it before returning it  
  
- `void function_prefix_initialize(vector* vec)`  
	Initialize an allocated vector  
	Allocate 'VECTOR_INITIALIZE_SIZE' amount of space for its data  
	  
#### 2. Copying and Destruction  
- `void function_prefix_copy(vector* dest, vector* from)`  
	Copy a vector from "from" to "dest"  
	"dest" will be initialized, so any data in it will be lost  
	Destroy "dest" or make sure its not initialized to prevent memory leaks  
  
- `void function_prefix_destroy(vector* vec)`  
	Free the data the vector allocates  
	This function will NOT free the pointer "vec" itself  
	This could act as a destructor if vector is used in any other containers  
  
- `void function_prefix_destroy_ptr(vector* vec)`  
	Free the data the vector allocates  
	This function WILL free the pointer "vec" itself  
  
#### 3. Capacity and Size Management  
- `void function_prefix_reserve(vector* vec, int size)`  
	Reserve atleast "size" amount of space for "vec"  
	If "vec" has space equal or more than "size",  
	then nothing will be done  
  
- `void function_prefix_shrink_to_fit(vector* vec)`  
	Shrink the capacity of "vec" to its size  
  
- `void function_prefix_resize(vector* vec, int size)`  
	Resize "vec" to "size"  
	If any element is not in range of "size", then destructor will be called  
	If any new element is created, the constructor will be called  
  
#### 4. Element Access  
- `type function_prefix_at(vector* vec, int index)`  
	Returns of the copy of the element at position "index" of "vec"  
	If the index is negative, then it will start counting from the end of the vector  
  
- `type* function_prefix_at_ptr(vector* vec, int index)`  
	Returns the pointer of the element at position "index" of "vec"  
  
- `type* function_prefix_front(vector* vec)`  
	Returns the pointer of the first element in "vec"  
  
- `type* function_prefix_back(vector* vec)`  
	Returns the pointer of the last element in "vec"  
	  
#### 5. Modifying Functions  
- `void function_prefix_push_back(vector* vec, type object)`  
	Push "object" on the back of "vec"  
  
- `void function_prefix_insert(vector* vec, int index, type object)`  
	Insert "object" at the position "index" of "vec"  
	If the index is negative, then it will start counting from the end of the vector  
  
- `void function_prefix_pop_back(vector* vec)`  
	Pop the last element of "vec"  
	Destructor will be called  
  
- `void function_prefix_erase(vector* vec, int index)`  
	Erase the object located in "index" and call destructor  
  
- `void function_prefix_clear(vector* vec)`  
	Call destructor on every element and set the size of "vec" to 0  
  
- `void function_prefix_reverse(vector* vec, int from, int to)`  
	Reverse the element of "vec" from index "from" to index "to"  
	If the index is negative, then it will start counting from the end of the vector  
  
- `void function_prefix_insert_array(vector* vec, type* other, int index, int size)`  
	Insert an array "other" of size "size" into "vec" at position "index"  
	If the index is negative, then it will start counting from the end of the vector  
  
- `void function_prefix_insert_array_range(vector* vec, type* other, int index, int from, int to, int size)`  
	Insert an array "other" of size "size" from index "from" to index "to" into "vec" at position "index"  
	If the index is negative, then it will start counting from the end of the vector  
  
- `void function_prefix_insert_vec(vector* vec, vector* other, int index)`  
	Insert a vector "other" into "vec" at position "index"  
	If the index is negative, then it will start counting from the end of the vector  
  
- `void function_prefix_insert_vec_range(vector* vec, vector* other, int index, int from, int to)`  
	Insert a vector "other" from index "from" to index "to" into "vec" at position "index"  
	If the index is negative, then it will start counting from the end of the vector  
  
  
#### 6. Searching  
- `int function_prefix_find(vector* vec, type object)`  
	Returns the index of "object" in "vec"  
	If "object" doesn't exist, then the size of "vec" will be returned  
  
- `int function_prefix_find_cmp(vector* vec, type object, int(*cmp)(type*, type*))`  
	Returns the index of "object" in "vec"  
	A custom "cmp" function is used to compare elements  
	If "object" doesn't exist, then the size of "vec" will be returned  
	  
- `int function_prefix_find_range(vector* vec, int from, int to, type object)`  
	Returns the index of "object" in "vec" from the index "from" to "to"  
	If the index is negative, then it will start counting from the end of the vector  
	If "object" doesn't exist, then the size of "vec" will be returned  
  
- `int function_prefix_find_range_cmp(vector* vec, int from, int to, type object, int(*cmp)(type*, type*))`  
	Returns the index of "object" in "vec" from the index "from" to "to"  
	A custom "cmp" function is used to compare elements  
	If the index is negative, then it will start counting from the end of the vector  
	If "object" doesn't exist, then the size of "vec" will be returned  
  
#### 7. Utility Functions  
- `bool function_prefix_empty(vector* vec)`  
	Returs if "vec" is empty  
  
- `bool function_prefix_equal(vector* a, vector* b)`  
	Returs if vector "a" is equal to vector "b"  
  
#### 8. Private Functions  
##### You should NOT call these functions  
- `void function_prefix_reallocate(vector* vec, int size)`  
	Reallocate "vec" so that it could hold "size" element  
	If "size" is less than the capacity of "vec", then nothing will be done  
	  
- `void function_prefix_init_element(vector* vec, int from, int to)`  
	Call the constructor from index "from" to index "to" in vector "vec"  
  
## Vector Iterate Method  
- [vector](#vector)  
##### Declaration  
```c  
DeclareVector(int, IVector, ivector, NULL, NULL, NULL)  
Ivector vector;  
```  
##### How to Iterate  
```c  
for (int i = 0; i < vector.size; ++i) {  
    int element = ivector_at(&vector, i);  
    int* element_ptr = ivector_at_ptr(&vector, i);  
}  
```  
  
# map  
- [top](#c-stl-container)  
## Table of content  
- [How to Declare a Map](#how-to-declare-a-map)  
- [Available Map Functions](#availble-map-functions)  
- [Map Iterate Method](#map-iterate-method)  
  
## How to Declare a Map  
- [map](#map)  
1. `DeclareMap(keyT, valueT, name, function_prefix, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)`  
  
2. `DeclareMapCmp(keyT, valueT, name, function_prefix, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)`  
  
    - keyT  
        - the type of the key in the map  
    - valueT  
        - the type of the value in the map  
    - name   
        - the name of the map struct  
    - function_prefix  
        - every function will be prefixed with function_prefix  
    - comparitor  
        - the comparison function for type "keyT"  
    - key_constructor  
        - the constructor for "keyT", pass NULL to use the default constructor(which is empty)  
    - key_copy_constructor  
        - the copy_constructor for "keyT", pass NULL to use the default copy_constructor(which is empty)  
    - key_destructor  
        - the destructor for "keyT", pass NULL to use the default destructor(which is empty)  
    - value_constructor  
        - the constructor for "keyT", pass NULL to use the default constructor(which is empty)  
    - value_copy_constructor  
        - the copy_constructor for "keyT", pass NULL to use the default copy_constructor(which is empty)  
    - value_destructor  
        - the destructor for "keyT", pass NULL to use the default destructor(which is empty)  
  
## Availble Map Functions  
- [map](#map)  
#### 1. Creation and Initialization  
- `name* function_prefix_create()`  
    Allocate an empty map object, then initialize it before returning it  
  
- `void function_prefix_initialize(name* map)`  
	Allocate memory for the nil node of the map  
#### 2. Copying, Merging and Destruction  
- `void function_prefix_copy(name* dest, name* from)`o  
	Copy a map from "from" to "dest"  
	"dest" will be initialized, so any data in it will be lost  
	Destroy "dest" or make sure its not initialized to prevent memry leaks  
  
- `void function_prefix_merge(name* dest, name* from)`  
	Merge "from" to "dest"  
    Every element of "from" will be inserted into "dest"  
  
- `void function_prefix_destroy(name* map)`  
	Free the data the map allocates  
	This function will NOT free the pointer "map" itself  
	This could act as a destructor if map is used in any other containers  
  
- `void function_prefix_destroy_ptr(name* map)`  
	Free the data the map allocates  
	This function WILL free the pointer "map" itself  
#### 3. Element Access  
- `valueT function_prefix_at(name* map, keyT key)`  
    Returns a copy of the element that has the key "key"  
  
- `valueT* function_prefix_at_ptr(name* map, keyT key)`  
    Returns the pointer of the element that has the key "key"  
  
- `keyT function_prefix_front_key(name* map)`  
    Returns a copy of the key of the left most element in the red black tree  
    This key will be the smallest in respect to the compare function  
  
- `keyT function_prefix_back_key(name* map)`  
    Returns a copy of the key of the right most element in the red black tree  
    This key will be the largest in respect to the compare function  
  
- `valueT function_prefix_front_value(name* map)`  
    Returns a copy of the value of the left most element in the red black tree  
  
- `valueT function_prefix_back_value(name* map)`  
    Returns a copy of the value of the right most element in the red black tree  
	  
- `valueT function_prefix_back_value(name* map)`  
    Returns a copy of the value of the right most element in the red black tree  
#### 4. Node Access  
- `name_Node* function_prefix_front_node(name* map)`  
    Returns a pointer to the left most node in the red black tree  
  
- `name_Node* function_prefix_back_node(name* map)`  
    Returns a pointer to the right most node in the red black tree  
  
- `name_Node* function_prefix_next_forward_node(name* map, name_Node* node)`  
    Returns a pointer next node in the in order traversal  
    Returns NULL if nothing is left to traverse  
  
- `name_Node* function_prefix_next_backward_node(name* map, name_Node* node)`  
    Returns a pointer next node in the reverse in order traversal  
    Returns NULL if nothing is left to traverse  
  
- `keyT function_prefix_at_node_key(name* map, name_Node* node);`  
	Returns a copy of the key in "node"  
  
- `valueT function_prefix_at_node_value(name* map, name_Node* node);`  
	Returns a copy of the value in "node"  
  
- `keyT* function_prefix_at_node_key_ptr(name* map, name_Node* node);`  
	Returns the pointer of the key in "node"  
  
- `valueT* function_prefix_at_node_value_ptr(name* map, name_Node* node);`  
	Returns the pointer of the value in "node"  
#### 5. Modifying Functions  
- `void function_prefix_clear(name* map)`  
	Call destructor on every element and set the size of "map" to 0  
  
- `void function_prefix_insert(name* map, keyT key, valueT value)`  
	Insert "value" with "key" into the map  
  
- `void function_prefix_insert_key(name* map, keyT key)`  
	Insert "key" into the map  
	This will call constructor for valueT on the value of "key"  
  
- `void function_prefix_erase(name* map, keyT key)`  
	Erase the element with the key "key"  
	If the key doesn't exist in the red black tree,  
	then nothing will be done  
#### 6. Utility Functions  
- `bool function_prefix_contain(name* set, type value);`  
	Returns if the value is in the set  
#### 7. Red Black Tree functions  
##### You should NOT call these functions  
- `void function_prefix_rbtree_left_rotation(name* map, name_Node* node)`  
- `void function_prefix_rbtree_right_rotation(name* map, name_Node* node)`  
- `name_Node* function_prefix_rbtree_insert(name* map, keyT key, valueT value)`  
- `void function_prefix_rbtree_insert_fixup(name* map, name_Node* current)`  
- `name_Node* function_prefix_rbtree_erase(name* map, keyT key)`  
- `void function_prefix_rbtree_erase_fixup(name* map, name_Node* current)`  
- `name_Node* function_prefix_rbtree_successor(name* map, name_Node* current)`  
- `name_Node* function_prefix_rbtree_search(name* map, keyT key)`  
- `name_Node* function_prefix_rbtree_leftmost(name* map, name_Node* current)`  
- `name_Node* function_prefix_rbtree_rightmost(name* map, name_Node* current)`  
- `void function_prefix_rbtree_free(name* map, name_Node* current)`  
  
## Map Iterate Method  
- [map](#map)  
##### Declaration  
```c  
DeclareMap(int, float, IFMap, if_map, NULL, NULL, NULL, NULL, NULL, NULL, NULL)  
IIMap map;  
```  
##### How to Iterate Forward (From smallest to largest / Inorder traversal)  
```c  
for(IFMap_Node* itr = if_map_front_node(&map); itr != NULL; itr = if_map_next_forward_node(&map, itr)) {  
    int key = if_map_at_node_key(&map, itr);  
    float value = if_map_at_node_value(&map, itr);  
    int* key_ptr = if_map_at_node_key_ptr(&map, itr);  
    float* value_ptr = if_map_at_node_value_ptr(&map, itr);  
}  
```  
##### How to Iterate Backward (From largest to smallest / Reverse inorder traversal)  
```c  
for(IFMap_Node* itr = if_map_back_node(&map); itr != NULL; itr = if_map_next_backward_node(&map, itr)) {  
    int key = if_map_at_node_key(&map, itr);  
    float value = if_map_at_node_value(&map, itr);  
    int* key_ptr = if_map_at_node_key_ptr(&map, itr);  
    float* value_ptr = if_map_at_node_value_ptr(&map, itr);  
}  
```  
  
# unordered_map  
- [top](#c-stl-container)  
## Table of content  
- [How to Declare an Unordered Map](#how-to-declare-an-unordered-map)  
- [Available Unordered Map Functions](#availble-unordered-map-functions)  
- [Unordered Map Iterate Method](#unordered-map-iterate-method)  
  
## How to Declare an Unordered Map  
- [unordered_map](#unordered_map)  
1. `DeclareUnorderedMap(keyT, valueT, name, function_prefix, prober, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)`  
  
2. `DeclareUnorderedMapHash(keyT, valueT, name, function_prefix, hasher, prober, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)`  
  
3. `DeclareUnorderedMapCmp(keyT, valueT, name, function_prefix, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)`  
  
4. `DeclareUnorderedMapCmpHash(keyT, valueT, name, function_prefix, hasher, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)`  
  
    - keyT  
        - the type of the key in the set  
    - valueT  
        - the type of the value in the set  
    - name   
        - the name of the unordered_map struct  
    - function_prefix  
        - every function will be prefixed with void function_prefix  
	- hasher  
		- the hash function for type "keyT"  
	- prober  
		- the probe function for type "keyT"  
    - comparitor  
        - the comparison function for type "keyT"  
    - key_constructor  
        - the constructor for "keyT", pass NULL to use the default constructor(which is empty)  
    - key_copy_constructor  
        - the copy_constructor for "keyT", pass NULL to use the default copy_constructor(which is empty)  
    - key_destructor  
        - the destructor for "keyT", pass NULL to use the default destructor(which is empty)  
    - value_constructor  
        - the constructor for "keyT", pass NULL to use the default constructor(which is empty)  
    - value_copy_constructor  
        - the copy_constructor for "keyT", pass NULL to use the default copy_constructor(which is empty)  
    - value_destructor  
        - the destructor for "keyT", pass NULL to use the default destructor(which is empty)  
  
  
## Availble Unordered Map Functions  
- [unordered_map](#unordered_map)  
#### 1. Creation and Initialization  
- `name* function_prefix_create();`  
    Allocate an empty unordered_map object, then initialize it before returning it  
  
- `void function_prefix_initialize(name* map);`  
	Initialize an allocated unordered_map  
	Allocate 'UNORDERED_MAP_INITIALIZE_SIZE' amount of space for its data  
#### 2. Copying, Merging and Destruction  
- `void function_prefix_copy(name* dest, name* from);`  
	Copy a map from "from" to "dest"  
	"dest" will be initialized, so any data in it will be lost  
	Destroy "dest" or make sure its not initialized to prevent memry leaks  
  
- `void function_prefix_merge(name* map, name* other);`  
	Merge "from" to "dest"  
    Every element of "from" will be inserted into "dest"  
  
- `void function_prefix_destroy(name* map);`  
	Free the data the unordered_map allocates  
	This function will NOT free the pointer "map" itself  
	This could act as a destructor if "map" is used in any other containers  
  
- `void function_prefix_destroy_ptr(name* map);`  
	Free the data the unordered_map allocates  
	This function WILL free the pointer "map" itself  
#### 3. Capacity and Size Management  
- `void function_prefix_reserve(name* map, int size);`  
	Reserve atleast "size" amount of space for "map"  
	If "map" has space equal or more than "size",  
	then nothing will be done  
  
- `float function_prefix_load_factor(name* map);`  
	Returns the load factor of the map  
#### 4. Element Access  
- `valueT function_prefix_at(name* map, keyT key);`  
	Returns a copy of the value with the key "key"  
  
- `valueT* function_prefix_at_ptr(name* map, keyT key);`  
	Returns the pointer of the value with the key "key"  
	Returns NULL if key was not found  
  
- `keyT function_prefix_get_index_key(name* map, int index);`  
	Returns a copy of the key of the element at index "index" in "map"  
  
- `valueT function_prefix_get_index_value(name* map, int index);`  
	Returns a copy of the value of the element at index "index" in "map"  
  
- `keyT* function_prefix_get_index_key_ptr(name* map, int index);`  
	Returns the pointer of the key of the element at index "index" in "map"  
  
- `valueT* function_prefix_get_index_value_ptr(name* map, int index);`  
	Returns the pointer of the value of the element at index "index" in "map"  
  
- `valueT function_prefix_get_default(name* map, keyT key, valueT defualt_value);`  
	Returns the copy of the value with the key "key"  
	Returns the copy of "default_value" if "key" was not found  
  
- `name_Node* function_prefix_extract(name* map, keyT key);`  
	Returns the pointer of the node with the key "key"  
	Returns NULL if "key" was not found  
#### 5. Modifying Functions  
- `void function_prefix_clear(name* map);`  
	Call destructor on every element and set the size of "map" to 0  
  
- `void function_prefix_insert(name* map, keyT key, valueT value);`  
	Insert "value" with "key" into the unordered_map  
  
- `void function_prefix_insert_key(name* map, keyT key);`  
	Insert "key" into the unordered_map  
	This will call constructor for valueT on the value of "key"  
  
- `void function_prefix_erase(name* map, keyT key);`  
	Erase the element with the key "key"  
	If the key doesn't exist in the red black tree,  
	then nothing will be done  
#### 6. Utility functions  
- `bool function_prefix_contain(name* map, keyT key);`  
	Returns if the value is in the set  
	  
- `bool function_prefix_valid_index(name* map, int index);`  
	Returns it the "index" is a valid index in "map"   
#### 7. Private functions  
##### You should NOT call these functions  
- `void function_prefix_reallocate(name* map, int size);`  
	Reallocate "vec" so that it could hold "size" element  
	If "size" is less than the capacity of "vec", then nothing will be done  
  
- `void function_prefix_remove_node(name* map, name_Node* node);`  
	Call the destructor on the key and value of "node"  
  
- `void function_prefix_initialize_node(name* map, int from, int to);`  
	Call the constructor from index "from" to index "to" in map  
  
- `int function_prefix_get_index(name* map, name_Node* nodes, int size, keyT key);`  
	Return an index for the key  
  
  
## Unorderd Map Iterate Method  
- [unordered_map](#unordered_map)  
##### Declaration  
```c  
DeclareUnorderedMap(int, float, IFUMap, if_umap, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)  
IFUMap map;  
```  
##### How to Iterate  
```c  
for(int i = 0; i < map.capacity; ++i) {  
	if (!if_umap_valid_index(&map, i)) {  
		continue;  
	}  
	int key = if_umap_get_index_key(&map, i);  
	float value = if_umap_get_index_value(&map, i);  
	int* key_ptr = if_umap_get_index_key_ptr(&map, i);  
	float* value_ptr = if_umap_get_index_value_ptr(&map, i);  
}  
```  
  
# set  
- [top](#c-stl-container)  
## Table of content  
- [How to Declare a Set](#how-to-declare-a-set)  
- [Available Set Functions](#availble-set-functions)  
- [Set Iterate Method](#set-iterate-method)  
  
## How to Declare a Set  
- [set](#set)  
1. `DeclareSet(type, name, void function_prefix, constructor, copy_constructor, destructor)`  
  
2. `DeclareSetCmp(type, name, void function_prefix, constructor, copy_constructor, destructor, cmp)`  
  
    - type  
        - the type of the element in the set  
    - name   
        - the name of the set struct  
    - function_prefix  
        - every function will be prefixed with void function_prefix  
    - constructor  
        - the constructor for "type", pass NULL to use the default constructor(which is empty)  
    - copy_constructor  
        - the copy_constructor for "type", pass NULL to use the default copy_constructor(which is empty)  
    - destructor  
        - the destructor for "type", pass NULL to use the default destructor(which is empty)  
    - cmp  
        - the comparitor for "type"  
  
## Availble Set Functions  
- [set](#set)  
#### 1. Creation and Initialization  
- `name* function_prefix_create();`  
    Allocate an empty set object, then initialize it before returning it  
- `void function_prefix_initialize(Set* set);`  
	Initialize an allocated set  
	Allocate memory for the nil node of the set  
  
#### 2. Copying, Merging and Destruction  
- `void function_prefix_copy(Set* dest, Set* from);`  
	Copy a set from "from" to "dest"  
	"dest" will be initialized, so any data in it will be lost  
	Destroy "dest" or make sure its not initialized to prevent memory leaks  
  
- `void function_prefix_merge(Set* dest, Set* from);`  
	Merge "from" to "dest"  
    Every element of "from" will be inserted into "dest"  
  
- `void function_prefix_destroy(Set* set);`  
	Free the data the set allocates  
	This function will NOT free the pointer "set" itself  
	This could act as a destructor if set is used in any other containers  
  
- `void function_prefix_destroy_ptr(Set* set);`  
	Free the data the set allocates  
	This function WILL free the pointer "set" itself  
  
#### 3. Element Access  
- `type function_prefix_front(Set* set);`  
    Returns a copy of the left most element in the red black tree  
    This element will be the smallest in respect to the compare function  
  
- `type function_prefix_back(Set* set);`  
    Returns a copy of the right most element in the red black tree  
    This element will be the largest in respect to the compare function  
- `type function_prefix_at_node(Set* set, name_Node* node);`  
    Returns a copy of the value in the node  
  
#### 4. Node Access  
- `name_Node* function_prefix_at(Set* set, type value);`  
    Returns a pointer to the node value is stored in  
    Returns NULL if value is not in the set  
  
- `name_Node* function_prefix_front_node(Set* set);`  
    Returns a pointer to the left most node in the red black tree  
  
- `name_Node* function_prefix_back_node(Set* set);`  
    Returns a pointer to the right most node in the red black tree  
    
- `name_Node* function_prefix_next_forward_node(Set* set, name_Node* node);`  
    Returns a pointer next node in the in order traversal  
    Returns NULL if nothing is left to traverse  
    
- `name_Node* function_prefix_next_backward_node(Set* set, name_Node* node);`  
    Returns a pointer next node in the reverse in order traversal  
    Returns NULL if nothing is left to traverse  
  
#### 5. Modifying Functions  
- `void function_prefix_clear(Set* set);`  
	Call destructor on every element and set the size of "set" to 0  
  
#### 6. Utility Functions  
- `bool function_prefix_contain(name* set, type value);`  
	Returns if the value is in the set  
  
#### 6. Red Black Tree functions  
##### You should NOT call these functions  
- `void function_prefix_rbtree_left_rotation(Set* set, name_Node* node);`  
- `void function_prefix_rbtree_right_rotation(Set* set, name_Node* node);`  
- `name_Node* function_prefix_rbtree_insert(Set* set, type data);`  
- `void function_prefix_rbtree_insert_fixup(Set* set, name_Node* current);`  
- `name_Node* function_prefix_rbtree_erase(Set* set, type data);`  
- `void function_prefix_rbtree_erase_fixup(Set* set, name_Node* current);`  
- `name_Node* function_prefix_rbtree_successor(Set* set, name_Node* current);`  
- `name_Node* function_prefix_rbtree_search(Set* set, type value);`  
- `name_Node* function_prefix_rbtree_leftmost(Set* set, name_Node* current);`  
- `name_Node* function_prefix_rbtree_rightmost(Set* set, name_Node* current);`  
- `void function_prefix_rbtree_free(Set* set, name_Node* current);`  
  
## Set Iterate Method  
- [set](#set)  
##### Declaration  
```c  
DeclareSet(int, ISet, iset, NULL, NULL, NULL)  
ISet set;  
```  
##### How to Iterate Forward (From smallest to largest / Inorder traversal)  
```c  
for(ISet_Node* itr = iset_front_node(&set); itr != NULL; itr = iset_next_forward_node(&set, itr)) {  
    int element = iset_at_node(&set, itr);  
}  
```  
##### How to Iterate Backward (From largest to smallest / Reverse inorder traversal)  
```c  
for(ISet_Node* itr = iset_back_node(&set); itr != NULL; itr = iset_next_backward_node(&set, itr)) {  
    int element = iset_at_node(&set, itr);  
}  
```  
  
# unordered_set  
- [top](#c-stl-container)  
## Table of content  
- [How to Declare an Unordered Set](#how-to-declare-an-unordered-set)  
- [Available Unordered Set Functions](#availble-unordered-set-functions)  
- [Unordered Set Iterate Method](#unordered-set-iterate-method)  
  
## How to Declare an Unordered Set  
- [unordered_set](#unordered_set)  
1. `DeclareUnorderedSet(type, name, function_prefix, prober, constructor, copy_constructor, destructor)`  
  
2. `DeclareUnorderedSetHash(type, name, function_prefix, hasher, prober, constructor, copy_constructor, destructor)`  
  
3. `DeclareUnorderedSetCmp(type, name, function_prefix, prober, comparitor, constructor, copy_constructor, destructor)`  
  
4. `DeclareUnorderedSetCmpHash(type, name, function_prefix, hasher, prober, comparitor, constructor, copy_constructor, destructor)`  
  
    - type  
        - the type of the element in the unordered_set  
    - name   
        - the name of the unordered_set struct  
    - function_prefix  
        - every function will be prefixed with void function_prefix  
	- hasher  
		- the hash function for type "keyT"  
	- prober  
		- the probe function for type "keyT"  
    - comparitor  
        - the comparison function for type "keyT"  
    - constructor  
        - the constructor for "type", pass NULL to use the default constructor(which is empty)  
    - copy_constructor  
        - the copy_constructor for "type", pass NULL to use the default copy_constructor(which is empty)  
    - destructor  
        - the destructor for "type", pass NULL to use the default destructor(which is empty)  
  
  
## Availble Unordered Set Functions  
- [unordered_set](#unordered_set)  
#### 1. Creation and Initialization  
- `name* function_prefix_create();`  
    Allocate an empty unordered_set object, then initialize it before returning it  
  
- `void function_prefix_initialize(name* set);`  
	Initialize an allocated unordered_set  
	Allocate 'UNORDERED_SET_INITIALIZE_SIZE' amount of space for its data  
#### 2. Copying, Merging and Destruction  
- `void function_prefix_copy(name* dest, name* from);`  
	Copy a unordered_set from "from" to "dest"  
	"dest" will be initialized, so any data in it will be lost  
	Destroy "dest" or make sure its not initialized to prevent memry leaks  
  
- `void function_prefix_merge(name* set, name* other);`  
	Merge "from" to "dest"  
    Every element of "from" will be inserted into "dest"  
  
- `void function_prefix_destroy(name* set);`  
	Free the data the unordered_set allocates  
	This function will NOT free the pointer "set" itself  
	This could act as a destructor if unordered_set is used in any other containers  
  
- `void function_prefix_destroy_ptr(name* set);`  
	Free the data the unordered_set allocates  
	This function WILL free the pointer "set" itself  
#### 3. Capacity and Size Management  
- `void function_prefix_reserve(name* set, int size);`  
	Reserve atleast "size" amount of space for "set"  
	If "set" has space equal or more than "size",  
	then nothing will be done  
  
- `float function_prefix_load_factor(name* map);`  
	Returns the load factor of the map  
#### 4. Element Access  
- `type function_prefix_get_index_value(name* set, int index);`  
	Returns a copy of the value at index "index" in "set"  
  
- `type* function_prefix_get_index_value_ptr(name* set, int index);`  
	Returns the pointer of the value at index "index" in "set"  
  
- `name_Node* function_prefix_extract(name* set, type value);`  
	Returns the pointer of the node with "value"  
	Returns NULL if "key" was not found  
#### 5. Modifying Functions  
- `void function_prefix_clear(name* set);`  
	Call destructor on every element and set the size of "set" to 0  
  
- `void function_prefix_insert(name* set, type value);`  
	Insert "value" into the unordered_set  
  
- `void function_prefix_erase(name* set, type value);`  
	Erase "value"  
	If the key doesn't exist, then nothing will be done  
#### 6. Utility functions  
- `bool function_prefix_contain(name* set, type value);`  
	Returns if the value is in the unordered_set  
	  
- `bool function_prefix_valid_index(name* set, int index);`  
	Returns it the "index" is a valid index in "set"   
#### 7. Private functions  
##### You should NOT call these functions  
- `void function_prefix_reallocate(name* set, int size);`  
	Reallocate "vec" so that it could hold "size" element  
	If "size" is less than the capacity of "vec", then nothing will be done  
  
- `void function_prefix_remove_node(name* set, name_Node* node);`  
	Call the destructor on the key and value of "node"  
  
- `void function_prefix_initialize_node(name* set, int from, int to);`  
	Call the constructor from index "from" to index "to" in set  
  
- `int function_prefix_get_index(name* map, name_Node* nodes, int size, type value);`  
	Return an index for the value  
  
## Unordered Set Iterate Method  
- [unordered_set](#unordered_set)  
##### Declaration  
```c  
DeclareUnorderedSet(int, IUSet, iu_set, NULL, NULL, NULL, NULL)  
IUSet set;  
```  
##### How to Iterate  
```c  
for (int i = 0; i < set.capacity; ++i) {  
	if (!iu_set_valid_index(&set, i)) {  
		continue;  
	}  
	int value = iu_set_get_index_value(&set, i);  
	int* value_ptr = iu_set_get_index_value_ptr(&set, i);  
}  
```  
  
# pair  
- [top](#c-stl-container)  
## Table of content  
- [How to Declare a Pair](#how-to-declare-a-pair)  
- [Available Pair Functions](#availble-pair-functions)  
  
## How to Declare a Pair  
- [pair](#pair)  
1. `DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, second_constructor, second_copy_constructor, second_destructor)`  
  
2. `DeclarePairCmpFirst(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor)`  
  
3. `DeclarePairCmpSecond(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, second_constructor, second_copy_constructor, second_destructor, second_comparitor)`  
  
4. `DeclarePairCmp(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor, second_comparitor)`  
  
    - firstT  
        - the type of the first element in the pair  
	- secondT  
		- the type of the second element in the pair  
    - name   
        - the name of the pair struct  
    - function_prefix  
        - every function will be prefixed with void function_prefix  
    - first_constructor  
        - the constructor for "firstT", pass NULL to use the default constructor(which is empty)  
    - first_copy_constructor  
        - the copy_constructor for "firstT", pass NULL to use the default copy_constructor(which is empty)  
    - first_destructor  
        - the destructor for "firstT", pass NULL to use the default destructor(which is empty)  
    - first_comparitor  
        - the comparison function for type "firstT"  
    - second_constructor  
        - the constructor for "secondT", pass NULL to use the default constructor(which is empty)  
    - second_copy_constructor  
        - the copy_constructor for "secondT", pass NULL to use the default copy_constructor(which is empty)  
    - second_destructor  
        - the destructor for "secondT", pass NULL to use the default destructor(which is empty)  
    - second_comparitor  
        - the comparison function for type "secondT"  
  
## Availble Pair Functions  
- [pair](#pair)  
#### 1. Creation and Initialization  
- `name* function_prefix_create();`  
    Allocate a pair object, then initialize it before returning it  
  
- `name* function_prefix_make(firstT first, secondT second);`  
    Allocate a pair object, then initialize it with "first" and "second" before returning it  
  
- `void function_prefix_initialize(name* pair);`  
	Initialize an allocated pair  
	  
- `void function_prefix_initialize_with_value(name* pair, firstT first, secondT second);`  
	Initialize an allocated pair with "first" and "second"  
#### 2. Copying, Merging and Destruction  
- `void function_prefix_copy(name* dest, name* from);`  
	Copy a pair from "from" to "dest"  
	"dest" will be initialized, so any data in it will be lost  
	Destroy "dest" or make sure its not initialized to prevent memry leaks  
  
- `void function_prefix_destroy(name* pair);`  
	Free the data in the pair  
	This function will NOT free the pointer "pair" itself  
	This could act as a destructor if pair is used in any other containers  
  
- `void function_prefix_destroy_ptr(name* pair);`  
	Free the data in the pair  
	This function WILL free the pointer "pair" itself  
#### 3. Element Access  
- `firstT fucntion_prefix##_get_first(name* pair);`  
	Returns a copy of the first element of "pair"  
  
- `secondT fucntion_prefix##_get_second(name* pair);`  
	Returns a copy of the second element of "pair"  
#### 4. Modifying Functions  
- `void fucntion_prefix##_set_first(name* pair, firstT first);`  
	Set the first element "pair" to a copy of "first" after calling destructor on it  
  
- `void fucntion_prefix##_set_second(name* pair, secondT first);`  
	Set the second element "pair" to a copy of "second" after calling destructor on it  
  
- `void function_prefix_clear(name* pair);`  
	Call destructor and then the constructorS on the first and second element of "pair"  
#### 5. Utility functions  
- `int function_prefix_cmp(name* a, name* b);`  
	Returns the comparison of pair "a" and "b"