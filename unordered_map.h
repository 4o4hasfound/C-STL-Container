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

#define UNORDERED_MAP_INITIALIZE_SIZE 12

#define DeclareUnorderedMap(keyT, valueT, name, function_prefix, prober, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
extern inline int function_prefix##_default_cmp(keyT* a, keyT* b)  {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
extern inline int function_prefix##_default_hasher(keyT data) {\
    return (int)data;\
}\
_DeclareUnorderedMap(keyT, valueT, name, function_prefix, function_prefix##_default_hasher, prober, function_prefix##_default_cmp, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)

#define DeclareUnorderedMapHash(keyT, valueT, name, function_prefix, hasher, prober, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
extern inline int function_prefix##_default_cmp(keyT* a, keyT* b) {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
_DeclareUnorderedMap(keyT, valueT, name, function_prefix, hasher, prober, function_prefix##_default_cmp, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)

#define DeclareUnorderedMapCmp(keyT, valueT, name, function_prefix, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
extern inline int function_prefix##_default_hasher(keyT data) {\
    return (int)data;\
}\
_DeclareUnorderedMap(keyT, valueT, name, function_prefix, function_prefix##_default_hasher, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)

#define DeclareUnorderedMapCmpHash(keyT, valueT, name, function_prefix, hasher, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
_DeclareUnorderedMap(keyT, valueT, name, function_prefix, hasher, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)

#define _DeclareUnorderedMap(keyT, valueT, name, function_prefix, hasher, prober, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
extern inline void function_prefix##_default_key_constructor(keyT* data) {\
    return;\
}\
extern inline void function_prefix##_default_key_copy_constructor(keyT* dest, keyT* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_key_destructor(keyT* data) {\
    return;\
}\
extern inline void function_prefix##_default_value_constructor(valueT* data) {\
    return;\
}\
extern inline void function_prefix##_default_value_copy_constructor(valueT* dest, valueT* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_value_destructor(valueT* data) {\
    return;\
}\
extern inline int function_prefix##_default_prober(keyT key, int (*hash)(keyT), int i, int m) {\
    /*Double hashing*/\
    const int _Hash_Res = hash(key);\
    const int result = (_Hash_Res + /*First hash*/ \
        i * ((_Hash_Res | 1) % (m - 1) + 1) /*First hash*/ \
    ) % m;\
    if (result < 0) {\
        return result + m;\
    }\
    return result;\
}\
typedef struct name##_Node {\
    keyT key;\
    valueT value;\
    bool occupied;\
} name##_Node;\
typedef struct name {\
    struct name##_Node* data;\
    int size;\
    int capacity;\
    float max_load_factor;\
    int (*_hasher)(keyT);\
    int (*_prober)(keyT, int (*)(keyT), int, int);\
    void (*_key_constructor)(keyT*);\
    void (*_key_copy_constructor)(keyT*, keyT*);\
    void (*_key_destructor)(keyT*);\
    void (*_value_constructor)(valueT*);\
    void (*_value_copy_constructor)(valueT*, valueT*);\
    void (*_value_destructor)(valueT*);\
    int (*_cmp)(keyT*, keyT*);\
} name;\
extern inline name* function_prefix##_create();\
extern inline void function_prefix##_initialize(name* map);\
extern inline void function_prefix##_copy(name* dest, name* from);\
extern inline void function_prefix##_destroy(name* map);\
extern inline void function_prefix##_destroy_ptr(name* map);\
extern inline void function_prefix##_clear(name* map);\
extern inline void function_prefix##_reserve(name* map, int size);\
extern inline void function_prefix##_erase(name* map, keyT key);\
extern inline name##_Node* function_prefix##_extract(name* map, keyT key);\
extern inline void function_prefix##_merge(name* map, name* other);\
extern inline valueT function_prefix##_at(name* map, keyT key);\
extern inline valueT* function_prefix##_at_ptr(name* map, keyT key);\
extern inline keyT function_prefix##_get_index_key(name* map, int index);\
extern inline valueT function_prefix##_get_index_value(name* map, int index);\
extern inline void function_prefix##_insert(name* map, keyT key, valueT value);\
extern inline void function_prefix##_insert_key(name* map, keyT key);\
extern inline bool function_prefix##_contains(name* map, keyT key);\
extern inline valueT function_prefix##_get_default(name* map, keyT key, valueT defualt_value);\
extern inline float function_prefix##_load_factor(name* map);\
extern inline bool function_prefix##_valid_index(name* map, int index);\
extern inline void function_prefix##_reallocate(name* map, int size);\
extern inline int function_prefix##_get_index(name* map, name##_Node* nodes, int size, keyT key);\
extern inline void function_prefix##_remove_node(name* map, name##_Node* node);\
extern inline void function_prefix##_initialize_node(name* map, int from, int to);\
\
extern inline name* function_prefix##_create(){\
    name* map = (name*)malloc(sizeof(name));\
    function_prefix##_initialize(map);\
    return map;\
}\
extern inline void function_prefix##_initialize(name* map){\
    map->data = (name##_Node*)malloc(sizeof(name##_Node) * UNORDERED_MAP_INITIALIZE_SIZE);\
    map->size = 0;\
    map->capacity = UNORDERED_MAP_INITIALIZE_SIZE;\
    function_prefix##_initialize_node(map, 0, map->capacity-1);\
    map->max_load_factor = 0.5;\
    if (prober) {\
        map->_prober = prober;\
    }\
    else {\
        map->_prober = function_prefix##_default_prober;\
    }\
    if (key_constructor) {\
        map->_key_constructor = key_constructor;\
    }\
    else {\
        map->_key_constructor = function_prefix##_default_key_constructor;\
    }\
    if (key_copy_constructor) {\
        map->_key_copy_constructor = key_copy_constructor;\
    }\
    else {\
        map->_key_copy_constructor = function_prefix##_default_key_copy_constructor;\
    }\
    if (key_destructor) {\
        map->_key_destructor = key_destructor;\
    }\
    else {\
        map->_key_destructor = function_prefix##_default_key_destructor;\
    }\
    if (value_constructor) {\
        map->_value_constructor = value_constructor;\
    }\
    else {\
        map->_value_constructor = function_prefix##_default_value_constructor;\
    }\
    if (value_copy_constructor) {\
        map->_value_copy_constructor = value_copy_constructor;\
    }\
    else {\
        map->_value_copy_constructor = function_prefix##_default_value_copy_constructor;\
    }\
    if (value_destructor) {\
        map->_value_destructor = value_destructor;\
    }\
    else {\
        map->_value_destructor = function_prefix##_default_value_destructor;\
    }\
    map->_hasher = hasher;\
    map->_cmp = comparitor;\
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
        int index = function_prefix##_get_index(dest, dest->data, dest->capacity, from->data[i].key);\
        assert(index < dest->capacity);\
        function_prefix##_remove_node(dest, &dest->data[index]);\
        dest->_key_copy_constructor(&dest->data[index].key, &from->data[i].key);\
        dest->_value_copy_constructor(&dest->data[index].value, &from->data[i].value);\
        dest->data[index].occupied = true;\
    }\
}\
extern inline void function_prefix##_destroy(name* map){\
    for(int i = 0; i < map->capacity; ++i) {\
        if (!map->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(map, &map->data[i]);\
    }\
    free(map->data);\
}\
extern inline void function_prefix##_destroy_ptr(name* map){\
    for(int i = 0; i < map->capacity; ++i) {\
        if (!map->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(map, &map->data[i]);\
    }\
    free(map->data);\
    free(map);\
}\
extern inline void function_prefix##_clear(name* map){\
    for(int i = 0; i < map->capacity; ++i) {\
        if (!map->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_remove_node(map, &map->data[i]);\
    }\
}\
extern inline void function_prefix##_reserve(name* map, int size){\
    if (map->capacity * map->max_load_factor >= size) {\
        return;\
    }\
    function_prefix##_reallocate(map, (size / map->max_load_factor) * 2);\
}\
extern inline void function_prefix##_erase(name* map, keyT key){\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    if (index >= map->capacity) {\
        return;\
    }\
    function_prefix##_remove_node(map, &map->data[index]);\
    --map->size;\
}\
extern inline name##_Node* function_prefix##_extract(name* map, keyT key){\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    if (index >= map->capacity) {\
        return NULL;\
    }\
    return &map->data[index];\
}\
extern inline void function_prefix##_merge(name* map, name* other){\
    if (map->capacity * map->max_load_factor < (map->size + other->size)) {\
        function_prefix##_reallocate(map, max(map->capacity * 2, ceil((float)(map->size + other->size) / map->max_load_factor)));\
    }\
    for(int i = 0; i < other->capacity; ++i) {\
        if (!other->data[i].occupied) {\
            continue;\
        }\
        function_prefix##_insert(map, other->data[i].key, other->data[i].value);\
    }\
}\
extern inline valueT function_prefix##_at(name* map, keyT key){\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    assert(index < map->capacity);\
    valueT ret;\
    map->_value_copy_constructor(&ret, &map->data[index].value);\
    return ret;\
}\
extern inline valueT* function_prefix##_at_ptr(name* map, keyT key){\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    if (index >= map->capacity || !map->data[index].occupied) {\
        return NULL;\
    }\
    return &map->data[index].value;\
}\
extern inline keyT function_prefix##_get_index_key(name* map, int index){\
    keyT ret;\
    map->_key_copy_constructor(&ret, &map->data[index].key);\
    return ret;\
}\
extern inline valueT function_prefix##_get_index_value(name* map, int index){\
    valueT ret;\
    map->_value_copy_constructor(&ret, &map->data[index].value);\
    return ret;\
}\
extern inline void function_prefix##_insert(name* map, keyT key, valueT value){\
    if (function_prefix##_load_factor(map) >= map->max_load_factor) {\
        function_prefix##_reallocate(map, map->capacity * 2);\
    }\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    assert(index < map->capacity);\
    if (!map->data[index].occupied) {\
        map->_key_copy_constructor(&map->data[index].key, &key);\
        map->_value_copy_constructor(&map->data[index].value, &value);\
        map->data[index].occupied = true;\
        ++map->size;\
    }\
    else if (!map->_cmp(&map->data[index].key, &key)) {\
        map->_value_destructor(&map->data[index].value);\
        map->_value_copy_constructor(&map->data[index].value, &value);\
    }\
}\
extern inline void function_prefix##_insert_key(name* map, keyT key){\
    if (function_prefix##_load_factor(map) >= map->max_load_factor) {\
        function_prefix##_reallocate(map, map->capacity * 2);\
    }\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    assert(index < map->capacity);\
    if (!map->data[index].occupied) {\
        map->_key_copy_constructor(&map->data[index].key, &key);\
        map->_value_constructor(&map->data[index].value);\
        map->data[index].occupied = true;\
        ++map->size;\
    }\
    else if (!map->_cmp(&map->data[index].key, &key)) {\
        map->_value_destructor(&map->data[index].value);\
        map->_value_constructor(&map->data[index].value);\
    }\
}\
extern inline bool function_prefix##_contains(name* map, keyT key){\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    return index < map->capacity && map->data[index].occupied;\
}\
extern inline valueT function_prefix##_get_default(name* map, keyT key, valueT default_value){\
    int index = function_prefix##_get_index(map, map->data, map->capacity, key);\
    valueT ret;\
    if (index >= map->capacity || !map->data[index].occupied) {\
        map->_value_copy_constructor(&ret, &default_value);\
    }\
    map->_value_copy_constructor(&ret, &map->data[index].value);\
    return ret;\
}\
extern inline float function_prefix##_load_factor(name* map){\
    return (float)map->size / map->capacity;\
}\
extern inline bool function_prefix##_valid_index(name* map, int index){\
    assert(index >= 0 && index < map->capacity);\
    return map->data[index].occupied;\
}\
extern inline void function_prefix##_reallocate(name* map, int size){\
    if (map->capacity >= size) {\
        return;\
    }\
    name##_Node* newNode = (name##_Node*)malloc(sizeof(name##_Node) * size);\
    for(int i = 0; i < size; ++i) {\
        newNode[i].occupied = false;\
    }\
    \
    for(int i = 0; i < map->capacity; ++i) {\
        if (!map->data[i].occupied) {\
            continue;\
        }\
        int index = function_prefix##_get_index(map, newNode, size, map->data[i].key);\
        assert(index < size);\
        map->_key_copy_constructor(&newNode[index].key, &map->data[i].key);\
        map->_value_copy_constructor(&newNode[index].value, &map->data[i].value);\
        newNode[index].occupied = map->data[i].occupied;\
        function_prefix##_remove_node(map, map->data+i);\
    }\
    free(map->data);\
    map->capacity = size;\
    map->data = newNode;\
}\
extern inline int function_prefix##_get_index(name* map, name##_Node* nodes, int size, keyT key){\
    int i = 0;\
    \
    while(i < size) {\
        int index = map->_prober(key, map->_hasher, i, size);\
        if (!nodes[index].occupied || !map->_cmp(&nodes[index].key, &key)) {\
            return index;\
        }\
        ++i;\
    }\
    \
    return i;\
}\
extern inline void function_prefix##_remove_node(name* map, name##_Node* node){\
    if (!node->occupied) {\
        return;\
    }\
    map->_key_destructor(&node->key);\
    map->_value_destructor(&node->value);\
    node->occupied = false;\
}\
extern inline void function_prefix##_initialize_node(name* map, int from, int to){\
    for(int i = from; i <= to; ++i) {\
        map->data[i].occupied = false;\
    }\
}
