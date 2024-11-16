#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#define SET_RBTREE_COLOR_RED   0
#define SET_RBTREE_COLOR_BLACK 1

#define DeclareSet(type, name, function_prefix, constructor, copy_constructor, destructor) \
extern inline int function_prefix##_default_cmp(type* a, type* b) {\
    return *a < *b ? -1: *a > *b? 1: 0;\
}\
_DeclareSet(type, name, function_prefix, constructor, copy_constructor, destructor, function_prefix##_default_cmp)
#define DeclareSetCmp(type, name, function_prefix, constructor, copy_constructor, destructor, cmp) \
_DeclareSet(type, name, function_prefix, constructor, copy_constructor, destructor, cmp)

#define _DeclareSet(type, name, function_prefix, constructor, copy_constructor, destructor, comparitor)\
extern inline void function_prefix##_default_constructor(type* data) {\
    return;\
}\
extern inline void function_prefix##_default_copy_constructor(type* dest, type* from) {\
    *dest = *from;\
}\
extern inline void function_prefix##_default_destructor(type* data) {\
    return;\
}\
typedef struct name##_Node {\
    type value;\
    bool color;\
    struct name##_Node *left, *right, *parent;\
} name##_Node;\
typedef struct name {\
    name##_Node* root;\
    name##_Node* nil;\
    int size;\
    void (*_constructor)(type*);\
    void (*_copy_constructor)(type*, type*);\
    void (*_destructor)(type*);\
    int (*_cmp)(type*, type*);\
} name;\
extern inline name* function_prefix##_create();\
extern inline void function_prefix##_initialize(name* set);\
extern inline void function_prefix##_copy(name* dest, name* from);\
extern inline void function_prefix##_merge(name* dest, name* from);\
extern inline void function_prefix##_clear(name* set);\
extern inline void function_prefix##_destroy(name* set);\
extern inline void function_prefix##_destroy_ptr(name* set);\
extern inline void function_prefix##_insert(name* set, type value);\
extern inline void function_prefix##_erase(name* set, type value);\
extern inline name##_Node* function_prefix##_at(name* set, type value);\
extern inline bool function_prefix##_contain(name* set, type value);\
extern inline type function_prefix##_front(name* set);\
extern inline type function_prefix##_back(name* set);\
extern inline name##_Node* function_prefix##_front_node(name* set);\
extern inline name##_Node* function_prefix##_back_node(name* set);\
extern inline name##_Node* function_prefix##_next_forward_node(name* set, name##_Node* node);\
extern inline name##_Node* function_prefix##_next_backward_node(name* set, name##_Node* node);\
extern inline type function_prefix##_at_node(name* set, name##_Node* node);\
extern inline type* function_prefix##_at_node_ptr(name* set, name##_Node* node);\
\
extern inline void function_prefix##_rbtree_left_rotation(name* set, name##_Node* node);\
extern inline void function_prefix##_rbtree_right_rotation(name* set, name##_Node* node);\
extern inline name##_Node* function_prefix##_rbtree_insert(name* set, type data);\
extern inline void function_prefix##_rbtree_insert_fixup(name* set, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_erase(name* set, type data);\
extern inline void function_prefix##_rbtree_erase_fixup(name* set, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_successor(name* set, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_search(name* set, type value);\
extern inline name##_Node* function_prefix##_rbtree_leftmost(name* set, name##_Node* current);\
extern inline name##_Node* function_prefix##_rbtree_rightmost(name* set, name##_Node* current);\
extern inline void function_prefix##_rbtree_free(name* set, name##_Node* current);\
\
extern inline name* function_prefix##_create(){\
    name* set = (name*)malloc(sizeof(name));\
    function_prefix##_initialize(set);\
    return set;\
}\
extern inline void function_prefix##_initialize(name* set){\
    set->nil = (name##_Node*)malloc(sizeof(name##_Node));\
    set->nil->color = SET_RBTREE_COLOR_BLACK;\
    set->root = set->nil;\
    set->root->parent = set->nil;\
    set->size = 0;\
    if (constructor) {\
        set->_constructor = constructor;\
    }\
    else {\
        set->_constructor = function_prefix##_default_constructor;\
    }\
    if (copy_constructor) {\
        set->_copy_constructor = copy_constructor;\
    }\
    else {\
        set->_copy_constructor = function_prefix##_default_copy_constructor;\
    }\
    if (destructor) {\
        set->_destructor = destructor;\
    }\
    else {\
        set->_destructor = function_prefix##_default_destructor;\
    }\
    set->_cmp = comparitor;\
}\
extern inline void function_prefix##_copy(name* dest, name* from){\
    function_prefix##_initialize(dest);\
    function_prefix##_merge(dest, from);\
}\
extern inline void function_prefix##_merge(name* dest, name* from){\
    for (name##_Node* itr = function_prefix##_front_node(from); itr != NULL; itr = function_prefix##_next_forward_node(from, itr)) {\
        function_prefix##_insert(dest, itr->value);\
    }\
}\
extern inline void function_prefix##_clear(name* set){\
    for (name##_Node* itr = function_prefix##_front_node(set); itr != NULL; itr = function_prefix##_next_forward_node(set, itr)) {\
        set->_destructor(&itr->value);\
    }\
    function_prefix##_rbtree_free(set, set->root);\
    set->root = set->nil;\
    set->root->parent = set->nil;\
    set->size = 0;\
}\
extern inline void function_prefix##_destroy(name* set){\
    for (name##_Node* itr = function_prefix##_front_node(set); itr != NULL; itr = function_prefix##_next_forward_node(set, itr)) {\
        set->_destructor(&itr->value);\
    }\
    function_prefix##_rbtree_free(set, set->root);\
    free(set->nil);\
}\
extern inline void function_prefix##_destroy_ptr(name* set){\
    function_prefix##_destroy(set);\
    free(set);\
}\
extern inline void function_prefix##_insert(name* set, type value){\
    name##_Node* node = function_prefix##_rbtree_insert(set, value);\
    if (!node) {\
        return;\
    }\
    ++set->size;\
}\
extern inline void function_prefix##_erase(name* set, type value){\
    name##_Node* node = function_prefix##_rbtree_erase(set, value);\
    if (!node) {\
        return;\
    }\
    --set->size;\
    set->_destructor(&node->value);\
    free(node);\
}\
extern inline name##_Node* function_prefix##_at(name* set, type value){\
    return function_prefix##_rbtree_search(set, value);\
}\
extern inline bool function_prefix##_contain(name* set, type value){\
    return function_prefix##_rbtree_search(set, value) != NULL;\
}\
extern inline type function_prefix##_front(name* set){\
    type ret;\
    set->_copy_constructor(&ret, &function_prefix##_front_node(set)->value);\
    return ret;\
}\
extern inline type function_prefix##_back(name* set){\
    type ret;\
    set->_copy_constructor(&ret, &function_prefix##_back_node(set)->value);\
    return ret;\
}\
extern inline name##_Node* function_prefix##_front_node(name* set){\
    if (set->root == set->nil) {\
        return NULL;\
    }\
    name##_Node* node = set->root;\
    while(node->left != set->nil) {\
        node = node->left;\
    }\
    return node;\
}\
extern inline name##_Node* function_prefix##_back_node(name* set){\
    if (set->root == set->nil) {\
        return NULL;\
    }\
    name##_Node* node = set->root;\
    while(node->right != set->nil) {\
        node = node->right;\
    }\
    return node;\
}\
extern inline name##_Node* function_prefix##_next_forward_node(name* set, name##_Node* node){\
    if (node->right != set->nil) {\
        return function_prefix##_rbtree_leftmost(set, node->right);\
    }\
    while(node->parent != set->nil) {\
        if (node->parent->left == node){\
            return node->parent;\
        }\
        node = node->parent;\
    }\
    return NULL;\
}\
extern inline name##_Node* function_prefix##_next_backward_node(name* set, name##_Node* node){\
    if (node->left != set->nil) {\
        return function_prefix##_rbtree_rightmost(set, node->left);\
    }\
    while(node->parent != set->nil) {\
        if (node->parent->right == node){\
            return node->parent;\
        }\
        node = node->parent;\
    }\
    return NULL;\
}\
extern inline type function_prefix##_at_node(name* set, name##_Node* node){\
    type ret;\
    set->_copy_constructor(&ret, &node->value);\
    return ret;\
}\
extern inline type* function_prefix##_at_node_ptr(name* set, name##_Node* node){\
    return &node->value;\
}\
\
extern inline void function_prefix##_rbtree_left_rotation(name* set, name##_Node* x){\
    name##_Node* y = x->right;\
    x->right = y->left;\
    if (y->left != set->nil) {\
        y->left->parent = x;\
    }\
    y->parent = x->parent;\
    if (x->parent == set->nil) {\
        set->root = y;\
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
extern inline void function_prefix##_rbtree_right_rotation(name* set, name##_Node* y){\
    name##_Node* x = y->left;\
    y->left = x->right;\
    if (x->right != set->nil) {\
        x->right->parent = y;\
    }\
    x->parent = y->parent;\
    if (y->parent == set->nil) {\
        set->root = x;\
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
extern inline name##_Node* function_prefix##_rbtree_insert(name* set, type data){\
    name##_Node* y = set->nil;\
    name##_Node* x = set->root;\
    \
    while(x != set->nil) {\
        y = x;\
        if (set->_cmp(&data, &x->value) < 0) {\
            x = x->left;\
        }\
        else if (set->_cmp(&data, &x->value) > 0) {\
            x = x->right;\
        }\
        else {\
            return NULL;\
        }\
    }\
    name##_Node* insert_node = (name##_Node*)malloc(sizeof(name##_Node));\
    set->_copy_constructor(&insert_node->value, &data);\
    insert_node->parent = y;\
    if (y == set->nil) {\
        set->root = insert_node;\
    }\
    else if (set->_cmp(&insert_node->value, &y->value) < 0) {\
        y->left = insert_node;\
    }\
    else {\
        y->right = insert_node;\
    }\
    insert_node->left = set->nil;\
    insert_node->right = set->nil;\
    insert_node->color = SET_RBTREE_COLOR_RED;\
    function_prefix##_rbtree_insert_fixup(set, insert_node);\
    return insert_node;\
}\
extern inline void function_prefix##_rbtree_insert_fixup(name* set, name##_Node* current){\
    while (current->parent->color == SET_RBTREE_COLOR_RED) {\
        if (current->parent == current->parent->parent->left) {\
            name##_Node *uncle = current->parent->parent->right;\
            if (uncle->color == SET_RBTREE_COLOR_RED) {\
                current->parent->color = SET_RBTREE_COLOR_BLACK;\
                uncle->color = SET_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = SET_RBTREE_COLOR_RED;\
                current = current->parent->parent;\
            }\
            else {\
                if (current == current->parent->right) {\
                    current = current->parent;\
                    function_prefix##_rbtree_left_rotation(set, current);\
                }\
                current->parent->color = SET_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = SET_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_right_rotation(set, current->parent->parent);\
            }\
        }\
        else {\
            name##_Node *uncle = current->parent->parent->left;\
            if (uncle->color == SET_RBTREE_COLOR_RED) {\
                current->parent->color = SET_RBTREE_COLOR_BLACK;\
                uncle->color = SET_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = SET_RBTREE_COLOR_RED;\
                current = current->parent->parent;\
            }\
            else {\
                if (current == current->parent->left) {\
                    current = current->parent;\
                    function_prefix##_rbtree_right_rotation(set, current);\
                }\
                current->parent->color = SET_RBTREE_COLOR_BLACK;\
                current->parent->parent->color = SET_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_left_rotation(set, current->parent->parent);\
            }\
        }\
    }\
    set->root->color = SET_RBTREE_COLOR_BLACK;\
}\
extern inline name##_Node* function_prefix##_rbtree_erase(name* set, type data){\
    name##_Node* delete_node = function_prefix##_rbtree_search(set, data);\
    if (delete_node == NULL) {\
        return NULL;\
    }\
    name##_Node* y = NULL;\
    name##_Node* x = NULL;\
  \
    if (delete_node->left == set->nil || delete_node->right == set->nil) {\
        y = delete_node;\
    }\
    else {\
        y = function_prefix##_rbtree_successor(set, delete_node);\
    }\
    if (y->left != set->nil){\
        x = y->left;\
    }\
    else{\
        x = y->right;\
    }\
    x->parent = y->parent;\
    if (y->parent == set->nil){\
        set->root = x; \
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
    if (y->color == SET_RBTREE_COLOR_BLACK) { \
        function_prefix##_rbtree_erase_fixup(set, x);\
    }\
    return y;\
}\
extern inline void function_prefix##_rbtree_erase_fixup(name* set, name##_Node* current){\
    while (current != set->root && current->color == SET_RBTREE_COLOR_RED) {\
        if (current == current->parent->left) {\
            name##_Node *sibling = current->parent->right;\
            if (sibling->color == SET_RBTREE_COLOR_RED) {\
                sibling->color = SET_RBTREE_COLOR_BLACK;\
                current->parent->color = SET_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_left_rotation(set, current->parent);\
                sibling = current->parent->right;\
            }\
            if (sibling->left->color == SET_RBTREE_COLOR_BLACK && sibling->right->color == SET_RBTREE_COLOR_BLACK) {\
                sibling->color = SET_RBTREE_COLOR_RED;\
                current = current->parent;\
            }\
            else {\
                if (sibling->right->color == SET_RBTREE_COLOR_BLACK) {\
                    sibling->left->color = SET_RBTREE_COLOR_BLACK;\
                    sibling->color = SET_RBTREE_COLOR_RED;\
                    function_prefix##_rbtree_right_rotation(set, sibling);\
                    sibling = current->parent->right;\
                }\
                sibling->color = current->parent->color;\
                current->parent->color = SET_RBTREE_COLOR_BLACK;\
                sibling->right->color = SET_RBTREE_COLOR_BLACK;\
                function_prefix##_rbtree_left_rotation(set, current->parent);\
                current = set->root;\
            }\
        }\
        else {\
            name##_Node *sibling = current->parent->left;\
            if (sibling->color == SET_RBTREE_COLOR_RED) {\
                sibling->color = SET_RBTREE_COLOR_BLACK;\
                current->parent->color = SET_RBTREE_COLOR_RED;\
                function_prefix##_rbtree_right_rotation(set, current->parent);\
                sibling = current->parent->left;\
            }\
            if (sibling->left->color == SET_RBTREE_COLOR_BLACK && sibling->right->color == SET_RBTREE_COLOR_BLACK) {\
                sibling->color = SET_RBTREE_COLOR_RED;\
                current = current->parent;\
            }\
            else {\
                if (sibling->left->color == SET_RBTREE_COLOR_BLACK) {\
                    sibling->right->color = SET_RBTREE_COLOR_BLACK;\
                    sibling->color = 0;\
                    function_prefix##_rbtree_left_rotation(set, sibling);\
                    sibling = current->parent->left;\
                }\
                sibling->color = current->parent->color;\
                current->parent->color = SET_RBTREE_COLOR_BLACK;\
                sibling->left->color = SET_RBTREE_COLOR_BLACK;\
                function_prefix##_rbtree_right_rotation(set, current->parent);\
                current = set->root;\
            }\
        }\
    }\
    current->color = SET_RBTREE_COLOR_BLACK;\
}\
extern inline name##_Node* function_prefix##_rbtree_successor(name* set, name##_Node* current){\
    if (current->right != set->nil){\
        return function_prefix##_rbtree_leftmost(set, current->right);\
    }\
    \
    name##_Node *new_node = current->parent;\
    \
    while (new_node != set->nil && current == new_node->right) {\
        current = new_node;\
        new_node = new_node->parent;\
    }\
    \
    return new_node;\
}\
extern inline name##_Node* function_prefix##_rbtree_search(name* set, type value){\
    name##_Node *current = set->root;\
    \
    while (current != set->nil && set->_cmp(&value, &current->value) != 0) {\
    	\
        if (set->_cmp(&value, &current->value) < 0){\
            current = current->left;\
        }\
        else {\
            current = current->right;\
        }\
    }\
    return current;\
}\
extern inline name##_Node* function_prefix##_rbtree_leftmost(name* set, name##_Node* current){\
    while (current->left != set->nil){\
        current = current->left;\
    }\
    return current;\
}\
extern inline name##_Node* function_prefix##_rbtree_rightmost(name* set, name##_Node* current){\
    while (current->right != set->nil){\
        current = current->right;\
    }\
    return current;\
}\
extern inline void function_prefix##_rbtree_free(name* set, name##_Node* current){\
    if (current == set->nil) {\
        return;\
    }\
    function_prefix##_rbtree_free(set, current->left);\
    function_prefix##_rbtree_free(set, current->right);\
    free(current);\
}