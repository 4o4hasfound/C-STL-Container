
#define DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, second_constructor, second_copy_constructor, second_destructor)\
extern inline int function_prefix##_defulat_first_cmp(firstT* a, firstT* b) {\
	return *a < *b? -1: *a > *b? 1: 0;\
}\
extern inline int function_prefix##_defulat_second_cmp(secondT* a, secondT* b) {\
	return *a < *b? -1: *a > *b? 1: 0;\
}\
_DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, function_prefix##_defulat_first_cmp, second_constructor, second_copy_constructor, second_destructor, function_prefix##_defulat_second_cmp)

#define DeclarePairCmpFirst(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor)\
extern inline int function_prefix##_defulat_second_cmp(secondT* a, secondT* b) {\
	return *a < *b? -1: *a > *b? 1: 0;\
}\
_DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor, function_prefix##_defulat_second_cmp)

#define DeclarePairCmpSecond(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, second_constructor, second_copy_constructor, second_destructor, second_comparitor)\
extern inline int function_prefix##_defulat_first_cmp(firstT* a, firstT* b) {\
	return *a < *b? -1: *a > *b? 1: 0;\
}\
_DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, function_prefix##_defulat_first_cmp, second_constructor, second_copy_constructor, second_destructor, second_comparitor)

#define DeclarePairCmp(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor, second_comparitor)\
_DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor, second_comparitor)

#define _DeclarePair(firstT, secondT, name, function_prefix, first_constructor, first_copy_constructor, first_destructor, first_comparitor, second_constructor, second_copy_constructor, second_destructor, second_comparitor)\
extern inline void function_prefix##_default_first_constructor(firstT* data) {\
    return;\
}\
extern inline void function_prefix##_default_first_copy_constructor(firstT* dest, firstT* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_first_destructor(firstT* data) {\
    return;\
}\
extern inline void function_prefix##_default_second_constructor(secondT* data) {\
    return;\
}\
extern inline void function_prefix##_default_second_copy_constructor(secondT* dest, secondT* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_second_destructor(secondT* data) {\
    return;\
}\
typedef struct name {\
	firstT first;\
	secondT second;\
	void (*_first_constructor)(firstT*);\
	void (*_first_copy_constructor)(firstT*, firstT*);\
	void (*_first_destructor)(firstT*);\
	int (*_first_cmp)(firstT*, firstT*);\
	void (*_second_constructor)(secondT*);\
	void (*_second_copy_constructor)(secondT*, secondT*);\
	void (*_second_destructor)(secondT*);\
	int (*_second_cmp)(secondT*, secondT*);\
} name;\
extern inline name* function_prefix##_create();\
extern inline name* function_prefix##_make(firstT first, secondT second);\
extern inline void function_prefix##_initialize(name* pair);\
extern inline void function_prefix##_initialize_with_value(name* pair, firstT first, secondT second);\
extern inline void function_prefix##_copy(name* dest, name* from);\
extern inline void function_prefix##_destroy(name* pair);\
extern inline void function_prefix##_destroy_ptr(name* pair);\
extern inline void fucntion_prefix##_clear(name* pair);\
extern inline void fucntion_prefix##_set_first(name* pair, firstT first);\
extern inline void fucntion_prefix##_set_second(name* pair, secondT first);\
extern inline int function_prefix##_cmp(name* a, name* b);\
\
extern inline name* function_prefix##_create(){\
	name* pair = (name*)malloc(sizeof(name));\
	function_prefix##_initialize(pair);\
	return pair;\
}\
extern inline name* function_prefix##_make(firstT first, secondT second){\
	name* pair = (name*)malloc(sizeof(name));\
	function_prefix##_initialize_with_value(pair, first, second);\
	return pair;\
}\
extern inline void function_prefix##_initialize(name* pair){\
    if (first_constructor) {\
        pair->_first_constructor = first_constructor;\
    }\
    else {\
        pair->_first_constructor = function_prefix##_default_first_constructor;\
    }\
    if (first_copy_constructor) {\
        pair->_first_copy_constructor = first_copy_constructor;\
    }\
    else {\
        pair->_first_copy_constructor = function_prefix##_default_first_copy_constructor;\
    }\
    if (first_destructor) {\
        pair->_first_destructor = first_destructor;\
    }\
    else {\
        pair->_first_destructor = function_prefix##_default_first_destructor;\
    }\
    if (second_constructor) {\
        pair->_second_constructor = second_constructor;\
    }\
    else {\
        pair->_second_constructor = function_prefix##_default_second_constructor;\
    }\
    if (second_copy_constructor) {\
        pair->_second_copy_constructor = second_copy_constructor;\
    }\
    else {\
        pair->_second_copy_constructor = function_prefix##_default_second_copy_constructor;\
    }\
    if (second_destructor) {\
        pair->_second_destructor = second_destructor;\
    }\
    else {\
        pair->_second_destructor = function_prefix##_default_second_destructor;\
    }\
    pair->_first_cmp = first_comparitor;\
    pair->_second_cmp = second_comparitor;\
	pair->_first_constructor(&pair->first);\
	pair->_second_constructor(&pair->second);\
}\
extern inline void function_prefix##_initialize_with_value(name* pair, firstT first, secondT second){\
    if (first_constructor) {\
        pair->_first_constructor = first_constructor;\
    }\
    else {\
        pair->_first_constructor = function_prefix##_default_first_constructor;\
    }\
    if (first_copy_constructor) {\
        pair->_first_copy_constructor = first_copy_constructor;\
    }\
    else {\
        pair->_first_copy_constructor = function_prefix##_default_first_copy_constructor;\
    }\
    if (first_destructor) {\
        pair->_first_destructor = first_destructor;\
    }\
    else {\
        pair->_first_destructor = function_prefix##_default_first_destructor;\
    }\
    if (second_constructor) {\
        pair->_second_constructor = second_constructor;\
    }\
    else {\
        pair->_second_constructor = function_prefix##_default_second_constructor;\
    }\
    if (second_copy_constructor) {\
        pair->_second_copy_constructor = second_copy_constructor;\
    }\
    else {\
        pair->_second_copy_constructor = function_prefix##_default_second_copy_constructor;\
    }\
    if (second_destructor) {\
        pair->_second_destructor = second_destructor;\
    }\
    else {\
        pair->_second_destructor = function_prefix##_default_second_destructor;\
    }\
    pair->_first_cmp = first_comparitor;\
    pair->_second_cmp = second_comparitor;\
	pair->_first_copy_constructor(&pair->first, &first);\
	pair->_second_copy_constructor(&pair->second, &second);\
}\
extern inline void function_prefix##_copy(name* dest, name* from){\
	function_prefix##_initialize_with_value(dest, from->first, from->second);\
}\
extern inline void function_prefix##_destroy(name* pair){\
	pair->_first_destructor(&pair->first);\
	pair->_second_destructor(&pair->second);\
}\
extern inline void function_prefix##_destroy_ptr(name* pair){\
	pair->_first_destructor(&pair->first);\
	pair->_second_destructor(&pair->second);\
	free(pair);\
}\
extern inline void fucntion_prefix##_clear(name* pair){\
	pair->_first_destructor(&pair->first);\
	pair->_second_destructor(&pair->second);\
	pair->_first_constructor(&pair->first);\
	pair->_second_constructor(&pair->second);\
}\
extern inline void fucntion_prefix##_set_first(name* pair, firstT first){\
	pair->_first_copy_constructor(&pair->first, &first);\
}\
extern inline void fucntion_prefix##_set_second(name* pair, secondT second){\
	pair->_second_copy_constructor(&pair->second, &second);\
}\
extern inline int function_prefix##_cmp(name* a, name* b){\
	int cmp1 = a->_first_cmp(&a->first, &b->first);\
	int cmp2 = a->_second_cmp(&a->second, &b->second);\
	if (cmp1 > 0) {\
		return 1;\
	}\
	else if (cmp1 < 0) {\
		return -1;\
	}\
	else if (cmp2 > 0) {\
		return 1;\
	}\
	else if (cmp2 < 0) {\
		return -1;\
	}\
	return 0;\
}
