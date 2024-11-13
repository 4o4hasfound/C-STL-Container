#include "set.h"
#include "map.h"
#include "pair.h"
#include "vector.h"
#include "string.h"
#include "unordered_map.h"
#include "unordered_set.h"
#include <stdio.h>

int stringCMP(String* a, String* b) {
	return strcmp(a->data, b->data);
}
int stringHash(String string) {
	unsigned long hash = 5381;
	int c;
	char* str = string.data;

	while (c = *str++)
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

	return hash;
}


DeclareVector(int, IVector, ivector, NULL, NULL, NULL);
int vectorCMP(IVector* a, IVector* b) {
	if (a->size != b->size) {
		return a->size < b->size ? -1 : a->size > b->size ? 1 : 0;
	}
	for (int i = 0; i < a->size; ++i) {
		if (ivector_at(a, i) != ivector_at(b, i)) {
			return ivector_at(a, i) < ivector_at(b, i) ? -1 : ivector_at(a, i) > ivector_at(b, i) ? 1 : 0;
		}
	}
	return 0;
}
DeclarePairCmpFirst(IVector, float, IFPair, if_pair, ivector_initialize, ivector_copy, ivector_destroy, vectorCMP, NULL, NULL, NULL);
int pairHash(IFPair p) {
	return (int)p.second;
}

DeclareSetCmp(IFPair, PairSet, pair_set, if_pair_initialize, if_pair_copy, if_pair_destroy, if_pair_cmp);
DeclareUnorderedSetCmpHash(IFPair, PairUnorderedSet, pair_uset, pairHash, NULL, if_pair_cmp, if_pair_initialize, if_pair_copy, if_pair_cmp);
DeclareVectorCmp(IFPair, PairVector, pair_vector, if_pair_initialize, if_pair_copy, if_pair_destroy, if_pair_cmp);
DeclareUnorderedMapCmpHash(String, PairSet, String2PairUMap, pairl_umap, stringHash, NULL, stringCMP, string_initialize, string_copy, string_destroy, pair_set_initialize, pair_set_copy, pair_set_destroy);
DeclareMapCmp(String, PairSet, String2PairMap, pairl_map, stringCMP, string_initialize, string_copy, string_destroy, pair_set_initialize, pair_set_copy, pair_set_destroy);


int main1() {
	String2PairMap* map = pairl_map_create();
	for (int i = 0; i < 10; ++i) {
		String* string = string_from_char('0' + i);
		pairl_map_insert_key(map, *string);
		string_destroy_ptr(string);
	}
	for (int i = 0; i < 10; ++i) {
		String* string = string_from_char('0' + i);
		PairSet* vector = pairl_map_at_ptr(map, *string);
		for (int j = 0; j < i + 5; ++j) {
			IVector* ivec = ivector_create();
			for (int k = 0; k < j + 2; ++k) {
				ivector_push_back(ivec, k);
			}
			IFPair* pair = if_pair_make(*ivec, j);
			pair_set_insert(vector, *pair);
			if_pair_destroy_ptr(pair);
			ivector_destroy_ptr(ivec);
		}
		string_destroy_ptr(string);
	}
	for (int i = 0; i < 10; ++i) {
		String* string = string_from_char('0' + i);
		PairSet* vector = pairl_map_at_ptr(map, *string);
		printf("%d:\n", i);
		for (PairSet_Node* itr = pair_set_front_node(vector); itr != NULL; itr = pair_set_next_forward_node(vector, itr)) {
			printf("	");
			for (int j = 0; j < itr->value.first.size; ++j) {
				printf("%d ", ivector_at(&itr->value.first, j));
			}
			printf("%f\n", itr->value.second);
		} 
		//for (int j = 0; j < vector->capacity; ++j) {
		//	if (!pair_uset_valid_index(vector, j)) {
		//		continue;
		//	}
		//	printf("	%d %f\n", pair_uset_get_index_value(vector, j).x, pair_uset_get_index_value(vector, j).y);
		//}
		printf("\n");
		string_destroy_ptr(string);
	}
	pairl_map_destroy_ptr(map);
}