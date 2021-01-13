#include "stdc.h"

typedef struct
{
    int a;
} My_t;

#define VEC_INIT_CAP (cap > 0 ? cap : 1)
#define VEC_GROW_CAP (vec->cap > 0 ? vec->cap * 2 : 1)

#ifndef VEC
#define VEC(Name, type) _VEC(Name, type, type)
#define _VEC(Name, type, up_type) \
    typdef struct                 \
    {                             \
        size_t size;              \
        size_t _cap;              \
        type *data;               \
    } * Vec##Name##_t;
#endif

typedef struct
{
    size_t size;
    size_t _cap;
    My_t *data;
} * VecMy_t;
/* Constructor */
inline VecMy_t VecMyAlloc(size_t cap)
{
    VecMy_t vec = (VecMy_t)malloc(sizeof(*vec));
    if (vec == NULL)
        return NULL;
    vec->data = (My_t *)calloc(cap, sizeof(My_t));
    if (vec->data == NULL)
        return NULL;
    vec->size = 0;
    vec->_cap = cap;
    return vec;
}
#define _VecMyAlloca(cap)                                                     \
    {                                                                         \
        VecMy_t _vec = (VecMy_t *)alloca(sizeof(*_vec) + cap * sizeof(My_t)); \
        _vec->data = (type *)((size_t *)vec + 2);                             \
        _vec->size = 0;                                                       \
        _vec->_cap = cap;                                                     \
        _vec;                                                                 \
    }
/* Destructor */
inline void VecMyFree(VecMy_t *vecPtr)
{
    VecMy_t vec = *vecPtr;
    free(vec->data);
    vec->data = NULL;
    vec->size = 0;
    vec->_cap = 0;
    free(*vecPtr);
    vecPtr = NULL;
}
/* Element Access */
inline My_t *VecMyAt(VecMy_t vec, size_t i)
{
    return (i < vec->size) ? &vec->data[i] : NULL;
}
inline My_t *VecMyFront(VecMy_t vec) { return VecMyAt(vec, 0); }
inline My_t *VecMyBack(VecMy_t vec) { return VecMyAt(vec, vec->size - 1); }
/* Capacity */
inline int VecMyReserve(VecMy_t vec, size_t cap)
{
    if (cap > vec->_cap)
    {
        vec->data = (My_t *)realloc(vec->data, cap * sizeof(My_t));
        if (vec->data == NULL)
            return -1;
        vec->_cap = cap;
    }
    return 0;
}
inline int VecMyResize(VecMy_t vec, size_t size)
{
    if (size > vec->size)
    {
    }
}
inline int VecMyClear(VecMy_t vec);
/* Modifier */
inline int VecMyPush(VecMy_t vec, My_t elem);
inline int VecMyPop(VecMy_t vec);
inline int VecMyInsert(VecMy_t vec, size_t i, My_t elem);
/* Convenience Method */
inline size_t VecMyFind(VecMy_t vec, My_t elem);
inline int VecMyFill(VecMy_t vec, size_t start, size_t count, My_t elem);
inline int VecMyInsertElems(VecMy_t vec, size_t i, size_t elemNum, ...);
