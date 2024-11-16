#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define MAP_RBTREE_COLOR_RED   0
#define MAP_RBTREE_COLOR_BLACK 1

#define DeclareMap(keyT, valueT, name, function_prefix, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
extern inline int function_prefix##_default_cmp(keyT* a, keyT* b)  {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
_DeclareMap(keyT, valueT, name, function_prefix, function_prefix##_default_cmp, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)

#define DeclareMapCmp(keyT, valueT, name, function_prefix, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
_DeclareMap(keyT, valueT, name, function_prefix, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)

#define _DeclareMap(keyT, valueT, name, function_prefix, comparitor, key_constructor, key_copy_constructor, key_destructor, value_constructor, value_copy_constructor, value_destructor)\
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
typedef struct name##_Node {\
    keyT key;\
    valueT value;\
    bool color;\
    struct name##_Node *left, *right, *parent;\
} name##_Node;\
typedef struct name {\
    name##_Node* root;\
    name##_Node* nil;\
    int size;\
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
extern inline void function_prefix##_merge(name* dest, name* from);\
extern inline void function_prefix##_clear(name* map);\
extern inline void function_prefix##_destroy(name* map);\
extern inline void function_prefix##_destroy_ptr(name* map);\
extern inline void function_prefix##_insert(name* map, keyT key, valueT value);\
extern inline void function_prefix##_insert_key(name* map, keyT key);\
extern inline void function_prefix##_erase(name* map, keyT key);\
extern inline valueT function_prefix##_at(name* map, keyT key);\
extern inline valueT* function_prefix##_at_ptr(name* map, keyT key);\
extern inline keyT function_prefix##_front_key(name* map);\
extern inline keyT function_prefix##_back_key(name* map);\
extern inline valueT function_prefix##_front_value(name* map);\
extern inline valueT function_prefix##_back_value(name* map);\
extern inline name##_Node* function_prefix##_front_node(name* map);\
extern inline name##_Node* function_prefix##_back_node(name* map);\
extern inline name##_Node* function_prefix##_next_forward_node(name* map, name##_Node* node);\
extern inline name##_Node* function_prefix##_next_backward_node(name* map, name##_Node* node);\
extern inline keyT function_prefix##_at_node_key(name* map, name##_Node* node);\
extern inline valueT function_prefix##_at_node_value(name* map, name##_Node* node);\
extern inline keyT* function_prefix##_at_node_key_ptr(name* map, name##_Node* node);\
extern inline valueT* function_prefix##_at_node_value_ptr(name* map, name##_Node* node);\
extern inline bool function_prefix##_contain(name* map, keyT key);\
\
extern inline void function_prefix##_rbtree_left_rotation(name* map, name##_Node* node);\
extern inline void function_prefix##_rbtree_right_rotation(name* map, name##_Node* node);\
extern inline name##_Node* function_prefix##_rbtree_insert(name* map, keyT key, valueT value);\
extern inline void function_prefix##_rbtree_insert_fixup(name* map, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_erase(name* map, keyT key);\
extern inline void function_prefix##_rbtree_erase_fixup(name* map, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_successor(name* map, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_search(name* map, keyT key);\
extern inline name##_Node* function_prefix##_rbtree_leftmost(name* map, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_rightmost(name* map, name##_Node* current);\
extern inline void function_prefix##_rbtree_free(name* map, name##_Node* current);\
extern inline void function_prefix##_print(name* map, name##_Node* node, int depth);\
\
extern inline name* function_prefix##_create(){\
    name* map = (name*)malloc(sizeof(name));\
    function_prefix##_initialize(map);\
    return map;\
}\
extern inline void function_prefix##_initialize(name* map){\
    map->nil = (name##_Node*)malloc(sizeof(name##_Node));\
    map->nil->color = MAP_RBTREE_COLOR_BLACK;\
    map->root = map->nil;\
    map->root->parent = map->nil;\
    map->size = 0;\
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
    map->_cmp = comparitor;\
}\
extern inline void function_prefix##_copy(name* dest, name* from){\
    function_prefix##_clear(dest);\
    function_prefix##_merge(dest, from);\
}\
extern inline void function_prefix##_merge(name* dest, name* from){\
    for (name##_Node* itr = function_prefix##_front_node(from); itr != NULL; itr = function_prefix##_next_forward_node(from, itr)) {\
        function_prefix##_insert(dest, itr->key, itr->value);\
    }\
}\
extern inline void function_prefix##_clear(name* map){\
    for (name##_Node* itr = function_prefix##_front_node(map); itr != NULL; itr = function_prefix##_next_forward_node(map, itr)) {\
        map->_key_destructor(&itr->key);\
        map->_value_destructor(&itr->value);\
    }\
    function_prefix##_rbtree_free(map, map->root);\
    map->root = map->nil;\
    map->root->parent = map->nil;\
    map->size = 0;\
}\
extern inline void function_prefix##_destroy(name* map){\
    for (name##_Node* itr = function_prefix##_front_node(map); itr != NULL; itr = function_prefix##_next_forward_node(map, itr)) {\
        map->_key_destructor(&itr->key);\
        map->_value_destructor(&itr->value);\
    }\
    function_prefix##_rbtree_free(map, map->root);\
    free(map->nil);\
}\
extern inline void function_prefix##_destroy_ptr(name* map){\
    function_prefix##_destroy(map);\
    free(map);\
}\
extern inline void function_prefix##_insert(name* map, keyT key, valueT value){\
    name##_Node* node = function_prefix##_rbtree_insert(map, key, value);\
    if (!node) {\
        return;\
    }\
    ++map->size;\
}\
extern inline void function_prefix##_insert_key(name* map, keyT key){\
    valueT value;\
    map->_value_constructor(&value);\
    name##_Node* node = function_prefix##_rbtree_insert(map, key, value);\
    map->_value_destructor(&value);\
    if (!node) {\
        return;\
    }\
    ++map->size;\
}\
extern inline void function_prefix##_erase(name* map, keyT key){\
    name##_Node* node = function_prefix##_rbtree_erase(map, key);\
    if (!node) {\
        return;\
    }\
    --map->size;\
    map->_key_destructor(&node->key);\
    map->_value_destructor(&node->value);\
    free(node);\
}\
extern inline valueT function_prefix##_at(name* map, keyT key){\
    valueT ret;\
    map->_value_copy_constructor(&ret, &function_prefix##_rbtree_search(map, key)->value);\
    return ret;\
}\
extern inline valueT* function_prefix##_at_ptr(name* map, keyT key){\
    return &function_prefix##_rbtree_search(map, key)->value;\
}\
extern inline keyT function_prefix##_front_key(name* map){\
    keyT ret;\
    map->_key_copy_constructor(&ret, &function_prefix##_front_node(map)->key);\
    return ret;\
}\
extern inline keyT function_prefix##_back_key(name* map){\
    keyT ret;\
    map->_key_copy_constructor(&ret, &function_prefix##_back_node(map)->key);\
    return ret;\
}\
extern inline valueT function_prefix##_front_value(name* map){\
    valueT ret;\
    map->_value_copy_constructor(&ret, &function_prefix##_front_node(map)->value);\
    return ret;\
}\
extern inline valueT function_prefix##_back_value(name* map){\
    valueT ret;\
    map->_value_copy_constructor(&ret, &function_prefix##_back_node(map)->value);\
    return ret;\
}\
extern inline name##_Node* function_prefix##_front_node(name* map){\
    if (map->root == map->nil) {\
        return NULL;\
    }\
    name##_Node* node = map->root;\
    while(node->left != map->nil) {\
        node = node->left;\
    }\
    return node;\
}\
extern inline name##_Node* function_prefix##_back_node(name* map){\
    if (map->root == map->nil) {\
        return NULL;\
    }\
    name##_Node* node = map->root;\
    while(node->right != map->nil) {\
        node = node->right;\
    }\
    return node;\
}\
extern inline name##_Node* function_prefix##_next_forward_node(name* map, name##_Node* node){\
    if (node->right != map->nil) {\
        return function_prefix##_rbtree_leftmost(map, node->right);\
    }\
    while(node->parent != map->nil) {\
        if (node->parent->left == node){\
            return node->parent;\
        }\
        node = node->parent;\
    }\
    return NULL;\
}\
extern inline name##_Node* function_prefix##_next_backward_node(name* map, name##_Node* node){\
    if (node->left != map->nil) {\
        return function_prefix##_rbtree_rightmost(map, node->left);\
    }\
    while(node->parent != map->nil) {\
        if (node->parent->right == node){\
            return node->parent;\
        }\
        node = node->parent;\
    }\
    return NULL;\
}\
extern inline keyT function_prefix##_at_node_key(name* map, name##_Node* node){\
    keyT ret;\
    map->_key_copy_constructor(&ret, &node->key);\
    return ret;\
}\
extern inline valueT function_prefix##_at_node_value(name* map, name##_Node* node){\
    valueT ret;\
    map->_value_copy_constructor(&ret, &node->value);\
    return ret;\
}\
extern inline keyT* function_prefix##_at_node_key_ptr(name* map, name##_Node* node){\
    return &node->key;\
}\
extern inline valueT* function_prefix##_at_node_value_ptr(name* map, name##_Node* node){\
    return &node->value;\
}\
extern inline bool function_prefix##_contain(name* map, keyT key){\
    return function_prefix##_rbtree_search(map, key) != NULL;\
}\
\
extern inline void function_prefix##_rbtree_left_rotation(name* map, name##_Node* x){\
    name##_Node* y = x->right;\
    x->right = y->left;\
    if (y->left != map->nil) {\
        y->left->parent = x;\
    }\
    y->parent = x->parent;\
    if (x->parent == map->nil) {\
        map->root = y;\
    }\
    else if (x == x->parent->left) {\
        x->parent->left = y;\
    }\
    else {\
        x->parent->right = y;\
    }\
    y->left = x;\
    x->parent = y;\
}\
extern inline void function_prefix##_rbtree_right_rotation(name* map, name##_Node* y){\
    name##_Node* x = y->left;\
    y->left = x->right;\
    if (x->right != map->nil) {\
        x->right->parent = y;\
    }\
    x->parent = y->parent;\
    if (y->parent == map->nil) {\
        map->root = x;\
    }\
    else if (y == y->parent->left) {\
        y->parent->left = x;\
    }\
    else {\
        y->parent->right = x;\
    }\
    x->right = y;\
    y->parent = x;\
}\
extern inline name##_Node* function_prefix##_rbtree_insert(name* map, keyT key, valueT value){\
    name##_Node* y = map->nil;\
    name##_Node* x = map->root;\
    \
    while(x != map->nil) {\
        y = x;\
        if (map->_cmp(&key, &x->key) < 0) {\
            x = x->left;\
        }\
        else if (map->_cmp(&key, &x->key) > 0) {\
            x = x->right;\
        }\
        else {\
            return NULL;\
        }\
    }\
    name##_Node* insert_node = (name##_Node*)malloc(sizeof(name##_Node));\
    map->_key_copy_constructor(&insert_node->key, &key);\
    map->_value_copy_constructor(&insert_node->value, &value);\
    insert_node->parent = y;\
    if (y == map->nil) {\
        map->root = insert_node;\
    }\
    else if (map->_cmp(&insert_node->key, &y->key) < 0) {\
        y->left = insert_node;\
    }\
    else {\
        y->right = insert_node;\
    }\
    insert_node->left = map->nil;\
    insert_node->right = map->nil;\
    insert_node->color = MAP_RBTREE_COLOR_RED;\
    function_prefix##_rbtree_insert_fixup(map, insert_node);\
    return insert_node;\
}\
extern inline void function_prefix##_rbtree_insert_fixup(name* map, name##_Node* current){\
    while (current->parent->color == MAP_RBTREE_COLOR_RED) {\
        if (current->parent == current->parent->parent->left) {\
            name##_Node *uncle = current->parent->parent->right;\
            if (uncle->color == MAP_RBTREE_COLOR_RED) {\
                current->parent->color = MAP_RBTREE_COLOR_BLACK;\
                uncle->color = MAP_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = MAP_RBTREE_COLOR_RED;\
                current = current->parent->parent;\
            }\
            else {\
                if (current == current->parent->right) {\
                    current = current->parent;\
                    function_prefix##_rbtree_left_rotation(map, current);\
                }\
                current->parent->color = MAP_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = MAP_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_right_rotation(map, current->parent->parent);\
            }\
        }\
        else {\
            name##_Node *uncle = current->parent->parent->left;\
            if (uncle->color == MAP_RBTREE_COLOR_RED) {\
                current->parent->color = MAP_RBTREE_COLOR_BLACK;\
                uncle->color = MAP_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = MAP_RBTREE_COLOR_RED;\
                current = current->parent->parent;\
            }\
            else {\
                if (current == current->parent->left) {\
                    current = current->parent;\
                    function_prefix##_rbtree_right_rotation(map, current);\
                }\
                current->parent->color = MAP_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = MAP_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_left_rotation(map, current->parent->parent);\
            }\
        }\
    }\
    map->root->color = MAP_RBTREE_COLOR_BLACK;\
}\
extern inline name##_Node* function_prefix##_rbtree_erase(name* map, keyT key){\
    name##_Node* delete_node = function_prefix##_rbtree_search(map, key);\
    if (delete_node == NULL) {\
        return NULL;\
    }\
    name##_Node* y = NULL;\
    name##_Node* x = NULL;\
  \
    if (delete_node->left == map->nil || delete_node->right == map->nil) {\
        y = delete_node;\
    }\
    else {\
        y = function_prefix##_rbtree_successor(map, delete_node);\
    }\
    if (y->left != map->nil){\
        x = y->left;\
    }\
    else{\
        x = y->right;\
    }\
    x->parent = y->parent;\
    if (y->parent == map->nil){\
        map->root = x; \
    }\
    else if (y == y->parent->left){\
        y->parent->left = x;\
    }\
    else{\
        y->parent->right = x;\
    }\
\
    if (y != delete_node) {\
        delete_node->value = y->value;\
    }\
\
    if (y->color == MAP_RBTREE_COLOR_BLACK) { \
        function_prefix##_rbtree_erase_fixup(map, x);\
    }\
    return y;\
}\
extern inline void function_prefix##_rbtree_erase_fixup(name* map, name##_Node* current){\
    while (current != map->root && current->color == MAP_RBTREE_COLOR_RED) {\
        if (current == current->parent->left) {\
            name##_Node *sibling = current->parent->right;\
            if (sibling->color == MAP_RBTREE_COLOR_RED) {\
                sibling->color = MAP_RBTREE_COLOR_BLACK;\
                current->parent->color = MAP_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_left_rotation(map, current->parent);\
                sibling = current->parent->right;\
            }\
            if (sibling->left->color == MAP_RBTREE_COLOR_BLACK && sibling->right->color == MAP_RBTREE_COLOR_BLACK) {\
                sibling->color = MAP_RBTREE_COLOR_RED;\
                current = current->parent;\
            }\
            else {\
                if (sibling->right->color == MAP_RBTREE_COLOR_BLACK) {\
                    sibling->left->color = MAP_RBTREE_COLOR_BLACK;\
                    sibling->color = MAP_RBTREE_COLOR_RED;\
                    function_prefix##_rbtree_right_rotation(map, sibling);\
                    sibling = current->parent->right;\
                }\
                sibling->color = current->parent->color;\
                current->parent->color = MAP_RBTREE_COLOR_BLACK;\
                sibling->right->color = MAP_RBTREE_COLOR_BLACK;\
                function_prefix##_rbtree_left_rotation(map, current->parent);\
                current = map->root;\
            }\
        }\
        else {\
            name##_Node *sibling = current->parent->left;\
            if (sibling->color == MAP_RBTREE_COLOR_RED) {\
                sibling->color = MAP_RBTREE_COLOR_BLACK;\
                current->parent->color = MAP_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_right_rotation(map, current->parent);\
                sibling = current->parent->left;\
            }\
            if (sibling->left->color == MAP_RBTREE_COLOR_BLACK && sibling->right->color == MAP_RBTREE_COLOR_BLACK) {\
                sibling->color = MAP_RBTREE_COLOR_RED;\
                current = current->parent;\
            }\
            else {\
                if (sibling->left->color == MAP_RBTREE_COLOR_BLACK) {\
                    sibling->right->color = MAP_RBTREE_COLOR_BLACK;\
                    sibling->color = 0;\
                    function_prefix##_rbtree_left_rotation(map, sibling);\
                    sibling = current->parent->left;\
                }\
                sibling->color = current->parent->color;\
                current->parent->color = MAP_RBTREE_COLOR_BLACK;\
                sibling->left->color = MAP_RBTREE_COLOR_BLACK;\
                function_prefix##_rbtree_right_rotation(map, current->parent);\
                current = map->root;\
            }\
        }\
    }\
    current->color = MAP_RBTREE_COLOR_BLACK;\
}\
extern inline name##_Node* function_prefix##_rbtree_successor(name* map, name##_Node* current){\
    if (current->right != map->nil){\
        return function_prefix##_rbtree_leftmost(map, current->right);\
    }\
    \
    name##_Node *new_node = current->parent;\
    \
    while (new_node != map->nil && current == new_node->right) {\
        current = new_node;\
        new_node = new_node->parent;\
    }\
    \
    return new_node;\
}\
extern inline name##_Node* function_prefix##_rbtree_search(name* map, keyT key){\
    name##_Node *current = map->root;\
    \
    while (current != map->nil && map->_cmp(&key, &current->key) != 0) {\
    	\
        if (map->_cmp(&key, &current->key) < 0){\
            current = current->left;\
        }\
        else {\
            current = current->right;\
        }\
    }\
    return current;\
}\
extern inline name##_Node* function_prefix##_rbtree_leftmost(name* map, name##_Node* current){\
    while (current->left != map->nil){\
        current = current->left;\
    }\
    return current;\
}\
extern inline name##_Node* function_prefix##_rbtree_rightmost(name* map, name##_Node* current){\
    while (current->right != map->nil){\
        current = current->right;\
    }\
    return current;\
}\
extern inline void function_prefix##_rbtree_free(name* map, name##_Node* current){\
    if (current == map->nil) {\
        return;\
    }\
    function_prefix##_rbtree_free(map, current->left);\
    function_prefix##_rbtree_free(map, current->right);\
    free(current);\
}\
extern inline void function_prefix##_print(name* map, name##_Node* node, int depth) {\
    for(int i = 0; i < depth; ++i) {\
        printf("    ");\
    }\
    printf("- ");\
    if (node == map->nil) {\
        printf("NIL\n");\
        return;\
    }\
    printf("%d\n", node->value);\
    if (node->left)\
    function_prefix##_print(map, node->left, depth+1);\
    if (node->right)\
    function_prefix##_print(map, node->right, depth+1);\
}

