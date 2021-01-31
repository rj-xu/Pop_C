#pragma once

#include "../../include/stdc.h"

#ifndef VEC

// Maximum bytes of vector in stack
#define VEC_STACK_MAX (10000)
// Initial capacity of vector
#define VEC_INIT_CAP (cap > 0 ? cap : 1)
// Grown capacity of vector
#define VEC_GROW_CAP (vec->_cap > 0 ? vec->_cap * 2 : 1)

// Constructor for vector in stack
#define VEC(VecType_t, cap)                                                                      \
    ({                                                                                           \
        VecType_t _vec = NULL;                                                                   \
        size_t _cap = (size_t)cap;                                                               \
        size_t _byte_size = sizeof(*_vec) + _cap * sizeof(_vec->data[0]);                        \
        _vec = (_cap == 0 || _byte_size > VEC_STACK_MAX) ? NULL : (VecType_t)alloca(_byte_size); \
        if (_vec != NULL)                                                                        \
        {                                                                                        \
            _vec->size = 0;                                                                      \
            _vec->_cap = cap;                                                                    \
            _vec->_in_stack = true;                                                              \
            _vec->data = (typeof(_vec->data))((char *)_vec + sizeof(*_vec));                     \
            memset(_vec->data, 0, _cap * sizeof(_vec->data[0]));                                 \
        }                                                                                        \
        _vec;                                                                                    \
    })

// Typedef a vector
#define VEC_TYPEDEF(Name, type) _VEC_TYPEDEF(Name, type, type)
#define _VEC_TYPEDEF(Name, type, up_type)                                                                  \
    /* Vector */                                                                                           \
    typedef struct                                                                                         \
    {                                                                                                      \
        size_t size;                                                                                       \
        size_t _cap;                                                                                       \
        bool _in_stack;                                                                                    \
        type *data;                                                                                        \
    } * Vec##Name##_t;                                                                                     \
                                                                                                           \
    /* Constructor for vector in heap*/                                                                    \
    static inline Vec##Name##_t Vec##Name##Alloc(size_t cap)                                               \
    {                                                                                                      \
        Vec##Name##_t vec = (Vec##Name##_t)malloc(sizeof(*vec));                                           \
        if (vec == NULL)                                                                                   \
            return NULL;                                                                                   \
                                                                                                           \
        vec->data = (type *)calloc(cap, sizeof(type));                                                     \
        if (vec->data == NULL)                                                                             \
            return NULL;                                                                                   \
                                                                                                           \
        vec->size = 0;                                                                                     \
        vec->_cap = cap;                                                                                   \
        vec->_in_stack = false;                                                                            \
                                                                                                           \
        return vec;                                                                                        \
    }                                                                                                      \
                                                                                                           \
    /* Destructor for vector in heap */                                                                    \
    static inline int Vec##Name##Free(Vec##Name##_t *vecPtr)                                               \
    {                                                                                                      \
        Vec##Name##_t vec = *vecPtr;                                                                       \
        if (vec->_in_stack)                                                                                \
            return -1;                                                                                     \
                                                                                                           \
        free(vec->data);                                                                                   \
        vec->data = NULL;                                                                                  \
        vec->size = 0;                                                                                     \
        vec->_cap = 0;                                                                                     \
                                                                                                           \
        free(vec);                                                                                         \
        vecPtr = NULL;                                                                                     \
                                                                                                           \
        return 0;                                                                                          \
    }                                                                                                      \
                                                                                                           \
    /********** ELEMENT ACCESS **********/                                                                 \
                                                                                                           \
    /* Access specified element with bounds checking */                                                    \
    static inline type Vec##Name##At(Vec##Name##_t vec, size_t i) { return vec->data[i]; }                 \
    /* Access the first element */                                                                         \
    static inline type Vec##Name##Front(Vec##Name##_t vec) { return vec->data[0]; }                        \
    /* Access the last element */                                                                          \
    static inline type Vec##Name##Back(Vec##Name##_t vec) { return vec->data[vec->size - 1]; }             \
                                                                                                           \
    /********** ITERATORS **********/                                                                      \
                                                                                                           \
    /* Returns an iterator to the beginning */                                                             \
    static inline type *Vec##Name##Begin(Vec##Name##_t vec) { return vec->data; };                         \
    static inline const type *Vec##Name##CBegin(Vec##Name##_t vec) { return vec->data; };                  \
    /* Returns an iterator to the end */                                                                   \
    static inline type *Vec##Name##End(Vec##Name##_t vec) { return vec->data + vec->_cap; };               \
    static inline const type *Vec##Name##CEnd(Vec##Name##_t vec) { return vec->data + vec->_cap; };        \
    /* Returns a reverse iterator to the beginning */                                                      \
    static inline type *Vec##Name##RBegin(Vec##Name##_t vec) { return vec->data + vec->_cap - 1; };        \
    static inline const type *Vec##Name##CRBegin(Vec##Name##_t vec) { return vec->data + vec->_cap - 1; }; \
    /* Returns a reverse iterator to the end */                                                            \
    static inline type *Vec##Name##REnd(Vec##Name##_t vec) { return vec->data + vec->_cap; };              \
    static inline const type *Vec##Name##CREnd(Vec##Name##_t vec) { return vec->data + vec->_cap; };       \
                                                                                                           \
    /********** CAPACITY **********/                                                                       \
                                                                                                           \
    /* Checks whether the container is empty */                                                            \
    static inline bool Vec##Name##Empty(Vec##Name##_t vec) { return vec->size == 0; }                      \
    /* Returns the number of elements */                                                                   \
    static inline size_t Vec##Name##Size(Vec##Name##_t vec) { return vec->size; }                          \
    /* Returns the maximum possible number of elements for vector in stack */                              \
    static inline size_t Vec##Name##MaxSize(Vec##Name##_t vec) { return VEC_STACK_MAX / sizeof(type); }    \
    /* Reserves storage */                                                                                 \
    static inline int Vec##Name##Reserve(Vec##Name##_t vec, size_t cap)                                    \
    {                                                                                                      \
        if (vec->_in_stack)                                                                                \
            return -1;                                                                                     \
                                                                                                           \
        if (cap > vec->_cap)                                                                               \
        {                                                                                                  \
            type *temp_data = (type *)realloc(vec->data, cap * sizeof(type));                              \
            if (temp_data == NULL)                                                                         \
                return -1;                                                                                 \
                                                                                                           \
            vec->data = temp_data;                                                                         \
            vec->_cap = cap;                                                                               \
        }                                                                                                  \
        memset(vec->data + vec->size, 0, (vec->_cap - vec->size) * sizeof(type));                          \
        return 0;                                                                                          \
    }                                                                                                      \
    /* Returns the number of elements that can be held in currently allocated storage */                   \
    static inline size_t Vec##Name##Capacity(Vec##Name##_t vec) { return vec->_cap; }                      \
    /* Reduces memory usage by freeing unused memory */                                                    \
    static inline int Vec##Name##ShrinkToFit(Vec##Name##_t vec) { return 0; }                              \
                                                                                                           \
    /********** MODIFIERS **********/                                                                      \
                                                                                                           \
    /* Clears the contents */                                                                              \
    static inline int Vec##Name##Clear(Vec##Name##_t vec);                                                 \
    /* Inserts an element */                                                                               \
    static inline int Vec##Name##Insert(Vec##Name##_t vec, size_t i, type elem);                           \
    /* Constructs an element in-place */                                                                   \
    static inline int Vec##Name##Emplace(Vec##Name##_t vec, type (*func)(void));                           \
    /* Erases an element */                                                                                \
    static inline size_t Vec##Name##Erase(Vec##Name##_t vec, size_t i);                                    \
    /* Adds an element to the end */                                                                       \
    static inline int Vec##Name##PushBack(Vec##Name##_t vec, type elem);                                   \
    /* Constructs an element in-place at the end */                                                        \
    static inline int Vec##Name##EmplaceBack(Vec##Name##_t vec, type (*func)(void));                       \
    /* Removes the last element */                                                                         \
    static inline int Vec##Name##PopBack(Vec##Name##_t vec);                                               \
    /* Changes the number of elements stored */                                                            \
    static inline int Vec##Name##Resize(Vec##Name##_t vec, size_t size)                                    \
    {                                                                                                      \
        if (Vec##Name##Reserve(vec, size) != 0)                                                            \
            return -1;                                                                                     \
    }                                                                                                      \
    /* Swaps the contents */                                                                               \
    static inline int Vec##Name##Swap(Vec##Name##_t vec0, Vec##Name##_t vec1);                             \
                                                                                                           \
    /********** LOOKUP **********/                                                                         \
                                                                                                           \
    /* Returns the number of specific element */                                                           \
    static inline size_t Vec##Name##Count(Vec##Name##_t vec, type elem);                                   \
    /* Finds specific element and returns the index of the first one */                                    \
    static inline size_t Vec##Name##Find(Vec##Name##_t vec, type elem);                                    \
    /* Finds specific element and returns the list */                                                      \
    static inline size_t Vec##Name##FindElems(Vec##Name##_t vec, size_t *list, size_t *count);             \
                                                                                                           \
    /********** FAST METHOD **********/                                                                    \
                                                                                                           \
    /* Fills vector with specific element */                                                               \
    static inline int Vec##Name##Fill(Vec##Name##_t vec, size_t start, size_t count, type elem);           \
    /* Inserts elements */                                                                                 \
    static inline int Vec##Name##InsertElems(Vec##Name##_t vec, size_t i, size_t elemNum, ...);
#endif
