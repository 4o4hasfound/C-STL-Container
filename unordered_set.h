#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#ifndef max
#define max(a, b) (a>b?a:b)
#endif

#ifndef min
#define min(a, b) (a<b?a:b)
#endif

#define UNORDERED_SET_INITIALIZE_SIZE 12

#define DeclareUnorderedSet(type, name, function_prefix, prober, constructor, copy_constructor, destructor)\
extern inline int function_prefix##_default_cmp(type* a, type* b) {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
extern inline int function_prefix##_default_hasher(type data) {\
    return (int)data;\
}\
_DeclareUnorderedSet(type, name, function_prefix, function_prefix##_default_hasher, prober, function_prefix##_default_cmp, constructor, copy_constructor, destructor)

#define DeclareUnorderedSetHash(type, name, function_prefix, hasher, prober, constructor, copy_constructor, destructor)\
extern inline int function_prefix##_default_cmp(type* a, type* b) {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
_DeclareUnorderedSet(type, name, function_prefix, hasher, prober, function_prefix##_default_cmp, constructor, copy_constructor, destructor)

#define DeclareUnorderedSetCmp(type, name, function_prefix, prober, comparitor, constructor, copy_constructor, destructor)\
extern inline int function_prefix##_default_hasher(type data) {\
    return (int)data;\
}\
_DeclareUnorderedSet(type, name, function_prefix, function_prefix##_default_hasher, prober, comparitor, constructor, copy_constructor, destructor)

#define DeclareUnorderedSetCmpHash(type, name, function_prefix, hasher, prober, comparitor, constructor, copy_constructor, destructor)\
_DeclareUnorderedSet(type, name, function_prefix, hasher, prober, comparitor, constructor, copy_constructor, destructor)

#define _DeclareUnorderedSet(type, name, function_prefix, hasher, prober, comparitor, constructor, copy_constructor, destructor)\
extern inline void function_prefix##_default_constructor(type* data) {\
    return;\
}\
extern inline void function_prefix##_default_copy_constructor(type* dest, type* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_destructor(type* data) {\
    return;\
}\
extern inline int function_prefix##_default_prober(type value, int (*hash)(type), int i, int m) {\
    /*Double hashing*/\
    const int _Hash_Res = hash(value);\
    const int result = (_Hash_Res + /*First hash*/ \
        i * ((_Hash_Res) % (m - 1) + 1) /*First hash*/ \
    ) % m;\
    if (result < 0) {\
        return result + m;\
    }\
    return result;\
}\
typedef struct name##_Node {\
    type value;\
    bool occupied;\
} name##_Node;\
typedef struct name {\
    struct name##_Node* data;\
    int size;\
    int capacity;\
    float max_load_factor;\
    int (*_hasher)(type);\
    int (*_prober)(type, int (*)(type), int, int);\
    void (*_constructor)(type*);\
    void (*_copy_constructor)(type*, type*);\
    void (*_destructor)(type*);\
    int (*_cmp)(type*, type*);\
} name;\
extern inline name* function_prefix##_create();\
extern inline void function_prefix##_initialize(name* uset);\
extern inline void function_prefix##_copy(name* dest, name* from);\
extern inline void function_prefix##_destroy(name* uset);\
extern inline void function_prefix##_destroy_ptr(name* uset);\
extern inline void function_prefix##_clear(name* uset);\
extern inline void function_prefix##_reserve(name* uset, int size);\
extern inline void function_prefix##_erase(name* uset, type value);\
extern inline name##_Node* function_prefix##_extract(name* uset, type value);\
extern inline void function_prefix##_merge(name* uset, name* other);\
extern inline void function_prefix##_insert(name* uset, type value);\
extern inline type function_prefix##_get_index_value(name* uset, int index);\
extern inline type* function_prefix##_get_index_value_ptr(name* uset, int index);\
extern inline bool function_prefix##_contain(name* uset, type value);\
extern inline float function_prefix##_load_factor(name* uset);\
extern inline bool function_prefix##_valid_index(name* uset, int index);\
extern inline void function_prefix##_reallocate(name* uset, int size);\
extern inline int function_prefix##_get_index(name* uset, name##_Node* nodes, int size, type value);\
extern inline void function_prefix##_remove_node(name* uset, name##_Node* node);\
extern inline void function_prefix##_initialize_node(name* uset, int from, int to);\
\
extern inline name* function_prefix##_create(){\
    name* uset = (name*)malloc(sizeof(name));\
    function_prefix##_initialize(uset);\
    return uset;\
}\
extern inline void function_prefix##_initialize(name* uset){\
    uset->data = (name##_Node*)malloc(sizeof(name##_Node) * UNORDERED_SET_INITIALIZE_SIZE);\
    uset->size = 0;\
    uset->capacity = UNORDERED_SET_INITIALIZE_SIZE;\
    function_prefix##_initialize_node(uset, 0, uset->capacity-1);\
    uset->max_load_factor = 0.5;\
    if (prober) {\
        uset->_prober = prober;\
    }\
    else {\
        uset->_prober = function_prefix##_default_prober;\
    }\
    if (constructor) {\
        uset->_constructor = constructor;\
    }\
    else {\
        uset->_constructor = function_prefix##_default_constructor;\
    }\
    if (copy_constructor) {\
        uset->_copy_constructor = copy_constructor;\
    }\
    else {\
        uset->_copy_constructor = function_prefix##_default_copy_constructor;\
    }\
    if (destructor) {\
        uset->_destructor = destructor;\
    }\
    else {\
        uset->_destructor = function_prefix##_default_destructor;\
    }\
    uset->_hasher = hasher;\
    uset->_cmp = comparitor;\
}\
extern inline void function_prefix##_copy(name* dest, name* from){\
    function_prefix##_initialize(dest);\
    if (dest->capacity * dest->max_load_factor < from->size) {\
        function_prefix##_reallocate(dest, ceil((float)from->size / dest->max_load_factor));\
    }\
    dest->size = from->size;\
    for(int i = 0; i < dest->capacity; ++i) {\
        if (!dest->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(dest, &dest->data[i]);\
    }\
    for(int i = 0; i < from->capacity; ++i) {\
        if (!from->data[i].occupied) {\
            continue;\
        }\
        int index = function_prefix##_get_index(dest, dest->data, dest->capacity, from->data[i].value);\
        assert(index < dest->capacity);\
        function_prefix##_remove_node(dest, &dest->data[index]);\
        dest->_copy_constructor(&dest->data[index].value, &from->data[i].value);\
        dest->data[index].occupied = true;\
    }\
}\
extern inline void function_prefix##_destroy(name* uset){\
    for(int i = 0; i < uset->capacity; ++i) {\
        if (!uset->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(uset, &uset->data[i]);\
    }\
    free(uset->data);\
}\
extern inline void function_prefix##_destroy_ptr(name* uset){\
    for(int i = 0; i < uset->capacity; ++i) {\
        if (!uset->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(uset, &uset->data[i]);\
    }\
    free(uset->data);\
    free(uset);\
}\
extern inline void function_prefix##_clear(name* uset){\
    for(int i = 0; i < uset->capacity; ++i) {\
        if (!uset->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(uset, &uset->data[i]);\
    }\
}\
extern inline void function_prefix##_reserve(name* uset, int size){\
    if (uset->capacity * uset->max_load_factor >= size) {\
        return;\
    }\
    function_prefix##_reallocate(uset, (size / uset->max_load_factor) * 2);\
}\
extern inline void function_prefix##_erase(name* uset, type value){\
    int index = function_prefix##_get_index(uset, uset->data, uset->capacity, value);\
    if (index >= uset->capacity) {\
        return;\
    }\
    function_prefix##_remove_node(uset, &uset->data[index]);\
    --uset->size;\
}\
extern inline name##_Node* function_prefix##_extract(name* uset, type value){\
    int index = function_prefix##_get_index(uset, uset->data, uset->capacity, value);\
    if (index >= uset->capacity) {\
        return NULL;\
    }\
    return &uset->data[index];\
}\
extern inline void function_prefix##_merge(name* uset, name* other){\
    if (uset->capacity * uset->max_load_factor < (uset->size + other->size)) {\
        function_prefix##_reallocate(uset, max(uset->capacity * 2, ceil((float)(uset->size + other->size) / uset->max_load_factor)));\
    }\
    for(int i = 0; i < other->capacity; ++i) {\
        if (!other->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_insert(uset, other->data[i].value);\
    }\
}\
extern inline type function_prefix##_get_index_value(name* uset, int index){\
    type ret;\
    uset->_copy_constructor(&ret, &uset->data[index].value);\
    return ret;\
}\
extern inline type* function_prefix##_get_index_value_ptr(name* uset, int index){\
    return &uset->data[index].value;\
}\
extern inline void function_prefix##_insert(name* uset, type value){\
    if (function_prefix##_load_factor(uset) >= uset->max_load_factor) {\
        function_prefix##_reallocate(uset, uset->capacity * 2);\
    }\
    int index = function_prefix##_get_index(uset, uset->data, uset->capacity, value);\
    assert(index < uset->capacity);\
    if (!uset->data[index].occupied) {\
        uset->_copy_constructor(&uset->data[index].value, &value);\
        uset->data[index].occupied = true;\
        ++uset->size;\
    }\
    else if (!uset->_cmp(&uset->data[index].value, &value)) {\
        uset->_destructor(&uset->data[index].value);\
        uset->_copy_constructor(&uset->data[index].value, &value);\
    }\
}\
extern inline bool function_prefix##_contain(name* uset, type value){\
    int index = function_prefix##_get_index(uset, uset->data, uset->capacity, value);\
    return index < uset->capacity && uset->data[index].occupied;\
}\
extern inline float function_prefix##_load_factor(name* uset){\
    return (float)uset->size / uset->capacity;\
}\
extern inline bool function_prefix##_valid_index(name* uset, int index){\
    assert(index >= 0 && index < uset->capacity);\
    return uset->data[index].occupied;\
}\
extern inline void function_prefix##_reallocate(name* uset, int size){\
    if (uset->capacity >= size) {\
        return;\
    }\
    name##_Node* newNode = (name##_Node*)malloc(sizeof(name##_Node) * size);\
    for(int i = 0; i < size; ++i) {\
        newNode[i].occupied = false;\
    }\
    \
    for(int i = 0; i < uset->capacity; ++i) {\
        if (!uset->data[i].occupied) {\
            continue;\
        }\
        int index = function_prefix##_get_index(uset, newNode, size, uset->data[i].value);\
        assert(index < size);\
        uset->_copy_constructor(&newNode[index].value, &uset->data[i].value);\
        newNode[index].occupied = uset->data[i].occupied;\
        function_prefix##_remove_node(uset, uset->data+i);\
    }\
    free(uset->data);\
    uset->capacity = size;\
    uset->data = newNode;\
}\
extern inline int function_prefix##_get_index(name* uset, name##_Node* nodes, int size, type value){\
    int i = 0;\
    \
    while(i < size) {\
        int index = uset->_prober(value, uset->_hasher, i, size);\
        if (!nodes[index].occupied || !uset->_cmp(&nodes[index].value, &value)) {\
            return index;\
        }\
        ++i;\
    }\
    \
    return i;\
}\
extern inline void function_prefix##_remove_node(name* uset, name##_Node* node){\
    if (!node->occupied) {\
        return;\
    }\
    uset->_destructor(&node->value);\
    node->occupied = false;\
}\
extern inline void function_prefix##_initialize_node(name* uset, int from, int to){\
    for(int i = from; i <= to; ++i) {\
        uset->data[i].occupied = false;\
    }\
}
