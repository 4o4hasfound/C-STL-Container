#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef max
#define max(a, b) (a>b?a:b)
#endif

#ifndef min
#define min(a, b) (a<b?a:b)
#endif

#define VECTOR_INITIALIZE_SIZE 5

#define DeclareVector(type, name, function_prefix, constructor, copy_constructor, destructor) \
extern inline int function_prefix##_default_cmp(type* a, type* b) {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
_DeclareVector(type, name, function_prefix, constructor, copy_constructor, destructor, function_prefix##_default_cmp)
#define DeclareVectorCmp(type, name, function_prefix, constructor, copy_constructor, destructor, cmp) \
_DeclareVector(type, name, function_prefix, constructor, copy_constructor, destructor, cmp)

#define _DeclareVector(type, name, function_prefix, constructor, copy_constructor, destructor, comparison) \
extern inline void function_prefix##_default_constructor(type* data) {\
    return;\
}\
extern inline void function_prefix##_default_copy_constructor(type* dest, type* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_destructor(type* data) {\
    return;\
}\
typedef struct name {\
    type* data;\
    int size;\
    int capacity;\
    void(*_constructor)(type*);\
    void(*_copy_constructor)(type*, type*);\
    void(*_destructor)(type*);\
    int(*_cmp)(type*, type*);\
} name;\
extern inline name* function_prefix##_create();\
extern inline void function_prefix##_initialize(name* vector);\
extern inline void function_prefix##_copy(name* dest, name* from);\
extern inline void function_prefix##_destroy(name* vector);\
extern inline void function_prefix##_destroy_ptr(name* vector);\
extern inline void function_prefix##_clear(name* vector);\
extern inline void function_prefix##_reserve(name* vector, int size);\
extern inline void function_prefix##_shrink_to_fit(name* vector);\
extern inline void function_prefix##_erase(name* vector, int index);\
extern inline void function_prefix##_reverse(name* vector, int from, int to);\
extern inline int function_prefix##_find(name* vector, type object);\
extern inline int function_prefix##_find_cmp(name* vector, type object, int(*cmp)(type*, type*));\
extern inline int function_prefix##_find_range(name* vector, int from, int to, type object);\
extern inline int function_prefix##_find_range_cmp(name* vector, int from, int to, type object, int(*cmp)(type*, type*));\
extern inline void function_prefix##_push_back(name* vector, type object);\
extern inline void function_prefix##_insert(name* vector, int index, type object);\
extern inline void function_prefix##_resize(name* vector, int size);\
extern inline void function_prefix##_pop_back(name* vector);\
extern inline type function_prefix##_at(name* vector, int index);\
extern inline type* function_prefix##_at_ptr(name* vector, int index);\
extern inline type* function_prefix##_front(name* vector);\
extern inline type* function_prefix##_back(name* vector);\
extern inline bool function_prefix##_empty(name* vector);\
extern inline bool function_prefix##_equal(name* a, name* b);\
extern inline void function_prefix##_insert_array(name* vector, type* other, int index, int size);\
extern inline void function_prefix##_insert_array_range(name* vector, type* other, int index, int from, int to, int size);\
extern inline void function_prefix##_insert_vector(name* vector, name* other, int index);\
extern inline void function_prefix##_insert_vector_range(name* vector, name* other, int index, int from, int to);\
extern inline void function_prefix##_reallocate(name* vector, int size);\
extern inline void function_prefix##_init_element(name* vector, int from, int to);\
\
extern inline name* function_prefix##_create(){\
    name* vector = (name*)malloc(sizeof(name));\
    function_prefix##_initialize(vector);\
    return vector;\
}\
extern inline void function_prefix##_initialize(name* vector){\
    vector->data = (type*)malloc(sizeof(type) * VECTOR_INITIALIZE_SIZE);\
    vector->size = 0;\
    vector->capacity = VECTOR_INITIALIZE_SIZE;\
    if (constructor) {\
        vector->_constructor = constructor;\
    }\
    else {\
        vector->_constructor = function_prefix##_default_constructor;\
    }\
    if (copy_constructor) {\
        vector->_copy_constructor = copy_constructor;\
    }\
    else {\
        vector->_copy_constructor = function_prefix##_default_copy_constructor;\
    }\
    if (destructor) {\
        vector->_destructor = destructor;\
    }\
    else {\
        vector->_destructor = function_prefix##_default_destructor;\
    }\
    vector->_cmp = comparison;\
}\
extern inline void function_prefix##_copy(name* dest, name* from){\
    function_prefix##_initialize(dest);\
    function_prefix##_reallocate(dest, from->capacity);\
    for(int i = 0; i < from->size; ++i) {\
        dest->_copy_constructor(&dest->data[i], &from->data[i]);\
    }\
    dest->size = from->size;\
}\
extern inline void function_prefix##_destroy(name* vector){\
    for(int i = 0; i < vector->size; ++i) {\
        vector->_destructor(function_prefix##_at_ptr(vector, i));\
    }\
    free(vector->data);\
}\
extern inline void function_prefix##_destroy_ptr(name* vector){\
    for(int i = 0; i < vector->size; ++i) {\
        vector->_destructor(function_prefix##_at_ptr(vector, i));\
    }\
    free(vector->data);\
    free(vector);\
}\
extern inline void function_prefix##_clear(name* vector){\
    for(int i = 0; i < vector->size; ++i) {\
        vector->_destructor(function_prefix##_at_ptr(vector, i));\
    }\
    vector->size = 0;\
}\
extern inline void function_prefix##_reserve(name* vector, int size){\
    if (size <= vector->capacity) {\
        return;\
    }\
    function_prefix##_reallocate(vector, size);\
}\
extern inline void function_prefix##_shrink_to_fit(name* vector){\
    if (vector->size >= vector->capacity) {\
        return;\
    }\
    function_prefix##_reallocate(vector, vector->size);\
}\
extern inline void function_prefix##_erase(name* vector, int index){\
    if(index < 0) {\
        index = vector->size+index;\
    }\
    vector->_destructor(function_prefix##_at_ptr(vector, index));\
    for(int i = index; i + 1 < vector->size; ++i) {\
        vector->_destructor(&vector->data[i]);\
        vector->_copy_constructor(&vector->data[i], &vector->data[i+1]);\
    }\
    --vector->size;\
}\
extern inline void function_prefix##_reverse(name* vector, int from, int to){\
    if (from < 0) {\
        from = vector->size + from;\
    }\
    if (to < 0) {\
        to = vector->size + to;\
    }\
    if (from > to) {\
        int tmp = from;\
        from = to;\
        to = tmp;\
    }\
    int halfSize = (to - from + 1) / 2;\
    for(int i = 0; i < halfSize; ++i){\
        type tmp = vector->data[from + i];\
        vector->data[from + i] = vector->data[to - i];\
        vector->data[to - i] = tmp;\
    }\
}\
extern inline int function_prefix##_find(name* vector, type object){\
    for(int i = 0; i < vector->size; ++i) {\
        if (!vector->_cmp(function_prefix##_at_ptr(vector, i), &object)){\
            return i;\
        }\
    }\
    return vector->size;\
}\
extern inline int function_prefix##_find_cmp(name* vector, type object, int(*cmp)(type*, type*)){\
    for(int i = 0; i < vector->size; ++i) {\
        if (!cmp(function_prefix##_at_ptr(vector, i), &object)){\
            return i;\
        }\
    }\
    return vector->size;\
}\
extern inline int function_prefix##_find_range(name* vector, int from, int to, type object){\
    if (from < 0) {\
        from = vector->size + from;\
    }\
    if (to < 0) {\
        to = vector->size + to;\
    }\
    if (from >= to) {\
        for(int i = from; i <= to; ++i) {\
            if (!vector->_cmp(function_prefix##_at_ptr(vector, i), &object)){\
                return i;\
            }\
        }\
    }\
    else {\
        for(int i = to; i >= from; --i) {\
            if (!vector->_cmp(function_prefix##_at_ptr(vector, i), &object)){\
                return i;\
            }\
        }\
    }\
    return vector->size;\
}\
extern inline int function_prefix##_find_range_cmp(name* vector, int from, int to, type object, int(*cmp)(type*, type*)){\
    if (from < 0) {\
        from = vector->size + from;\
    }\
    if (to < 0) {\
        to = vector->size + to;\
    }\
    if (from >= to) {\
        for(int i = from; i <= to; ++i) {\
            if (!cmp(function_prefix##_at_ptr(vector, i), &object)){\
                return i;\
            }\
        }\
    }\
    else {\
        for(int i = to; i >= from; --i) {\
            if (!cmp(function_prefix##_at_ptr(vector, i), &object)){\
                return i;\
            }\
        }\
    }\
    return vector->size;\
}\
extern inline void function_prefix##_push_back(name* vector, type object){\
    if (vector->size >= vector->capacity) {\
        function_prefix##_reallocate(vector, vector->capacity * 2);\
    }\
    vector->_copy_constructor(&vector->data[vector->size++], &object);\
}\
extern inline void function_prefix##_insert(name* vector, int index, type object){\
    if(index < 0) {\
        index = vector->size+index;\
    }\
    if (vector->size >= vector->capacity) {\
        function_prefix##_reallocate(vector, vector->capacity * 2);\
    }\
    for(int i = vector->size; i > index; --i) {\
        vector->_destructor(&vector->data[i]);\
        vector->_copy_constructor(&vector->data[i], &vector->data[i-1]);\
    }\
    vector->_copy_constructor(&vector->data[index], &object);\
    ++vector->size;\
}\
extern inline void function_prefix##_resize(name* vector, int size) {\
    if (size == vector->size) {\
        return;\
    }\
    if (vector->size + size > vector->capacity) {\
        function_prefix##_reallocate(vector, max(vector->capacity * 2, size * 2));\
    }\
    for(int i = size; i < vector->size; ++i) {\
        vector->_destructor(function_prefix##_at_ptr(vector, i));\
    }\
    for(int i = vector->size; i < size; ++i) {\
        vector->_constructor(function_prefix##_at_ptr(vector, i));\
    }\
    vector->size = size;\
}\
extern inline void function_prefix##_pop_back(name* vector){\
    vector->_destructor(function_prefix##_at_ptr(vector, vector->size-1));\
    --vector->size;\
}\
extern inline type function_prefix##_at(name* vector, int index){\
    if (index < 0) {\
        index = vector->size + index;\
    }\
    type tmp;\
    vector->_copy_constructor(&tmp, &vector->data[index]);\
    return tmp;\
}\
extern inline type* function_prefix##_at_ptr(name* vector, int index){\
    if (index < 0) {\
        index = vector->size + index;\
    }\
    return &vector->data[index];\
}\
extern inline type* function_prefix##_front(name* vector) {\
    return function_prefix##_at_ptr(vector, 0);\
}\
extern inline type* function_prefix##_back(name* vector) {\
    return function_prefix##_at_ptr(vector, vector->size-1);\
}\
extern inline bool function_prefix##_empty(name* vector){\
    return vector->size == 0;\
}\
extern inline bool function_prefix##_equal(name* a, name* b){\
    if (!a || !b || a->size != b->size || a->_cmp != b->_cmp) {\
        return false;\
    }\
    for(int i = 0; i < a->size; ++i) {\
        if (a->_cmp(&a->data[i], &b->data[i])) {\
            return false;\
        }\
    }\
    return true;\
}\
extern inline void function_prefix##_insert_vector(name* vector, name* other, int index){\
    if (vector->size + other->size > vector->capacity) {\
        function_prefix##_reallocate(vector, max(vector->capacity * 2, other->size * 2));\
    }\
    for(int i = vector->size - 1 + other->size; i > index + other->size - 1; --i) {\
        vector->_destructor(&vector->data[i]);\
        vector->_copy_constructor(&vector->data[i], &vector->data[i-other->size]);\
    }\
    for(int i = 0; i < other->size; ++i) {\
        vector->_destructor(&vector->data[index + i]);\
        vector->_copy_constructor(&vector->data[index + i], &other->data[i]);\
    }\
    vector->size += other->size;\
}\
extern inline void function_prefix##_insert_vector_range(name* vector, name* other, int index, int from, int to){\
    if (from < 0) {\
        from = other->size + from;\
    }\
    if (to < 0) {\
        to = other->size + to;\
    }\
    if (index < 0) {\
        index = vector->size + index;\
    }\
    if (from <= to) {\
        int size = to - from + 1;\
        if (vector->size + size > vector->capacity) {\
            function_prefix##_reallocate(vector, max(vector->capacity * 2, other->size * 2));\
        }\
        for(int i = vector->size - 1 + size; i > index + size - 1; --i) {\
            vector->_destructor(&vector->data[i]);\
            vector->_copy_constructor(&vector->data[i], &vector->data[i-size]);\
        }\
        for(int i = 0; i < size; ++i) {\
            vector->_destructor(&vector->data[index + i]);\
            vector->_copy_constructor(&vector->data[index + i], &other->data[from + i]);\
        }\
        vector->size += size;\
    }\
    else {\
        int size = from - to + 1;\
        if (vector->size + size > vector->capacity) {\
            function_prefix##_reallocate(vector, max(vector->capacity * 2, other->size * 2));\
        }\
        for(int i = vector->size - 1 + size; i > index + size - 1; --i) {\
            vector->_destructor(&vector->data[i]);\
            vector->_copy_constructor(&vector->data[i], &vector->data[i-size]);\
        }\
        for(int i = 0; i < size; ++i) {\
            vector->_destructor(&vector->data[index + i]);\
            vector->_copy_constructor(&vector->data[index + i], &other->data[from - i]);\
        }\
        vector->size += size;\
    }\
}\
extern inline void function_prefix##_insert_array(name* vector, type* other, int index, int size){\
    if (vector->size + size > vector->capacity) {\
        function_prefix##_reallocate(vector, max(vector->capacity * 2, size * 2));\
    }\
    for(int i = vector->size - 1 + size; i > index + size - 1; --i) {\
        vector->data[i] = vector->data[i-size];\
    }\
    for(int i = 0; i < size; ++i) {\
        vector->_destructor(&vector->data[index + i]);\
        vector->_copy_constructor(&vector->data[index + i], &other[i]);\
    }\
    vector->size += size;\
}\
extern inline void function_prefix##_insert_array_range(name* vector, type* other, int index, int from, int to, int size){\
    if (from < 0) {\
        from = size + from;\
    }\
    if (to < 0) {\
        to = size + to;\
    }\
    if (index < 0) {\
        index = vector->size + index;\
    }\
    if (from <= to) {\
        int size = to - from + 1;\
        if (vector->size + size > vector->capacity) {\
            function_prefix##_reallocate(vector, max(vector->capacity * 2, size * 2));\
        }\
        for(int i = vector->size - 1 + size; i > index + size - 1; --i) {\
            vector->_destructor(&vector->data[i]);\
            vector->_copy_constructor(&vector->data[i], &vector->data[i-1]);\
        }\
        for(int i = size-1; i >= 0; --i) {\
            vector->_destructor(&vector->data[index + size-1-i]);\
            vector->_copy_constructor(&vector->data[index + size-1-i], &other[from + i]);\
        }\
        vector->size += size;\
    }\
    else {\
        int size = from - to + 1;\
        if (vector->size + size > vector->capacity) {\
            function_prefix##_reallocate(vector, max(vector->capacity * 2, size * 2));\
        }\
        for(int i = vector->size - 1 + size; i > index + size - 1; --i) {\
            vector->_destructor(&vector->data[i]);\
            vector->_copy_constructor(&vector->data[i], &vector->data[i-size]);\
        }\
        for(int i = 0; i < size; ++i) {\
            vector->_destructor(&vector->data[index + i]);\
            vector->_copy_constructor(&vector->data[index + i], &other[from - i]);\
        }\
        vector->size += size;\
    }\
}\
extern inline void function_prefix##_reallocate(name* vector, int size){\
    void* tmp = realloc(vector->data, size * sizeof(type));\
    vector->data = (type*)tmp;\
    vector->capacity = size;\
}\
extern inline void function_prefix##_init_element(name* vector, int from, int to){\
    for(int i = from; i <= to; ++i) {\
        vector->_constructor(function_prefix##_at_ptr(vector, i));\
    }\
}