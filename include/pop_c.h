#pragma once

#include <stddef.h>
#include <stdlib.h>

// Lambda
#define LAMBDA(return_type, function_body) \
    ({                                     \
        return_type __fn__ function_body   \
            __fn__;                        \
    })

// Function Declartion
#define FUNC(Class, return_type, func, type_args...) \
    return_type (*func)(Class * _this, ##type_args)

// Method Definition
#define METHOD(Class, return_type, func, type_args...) \
    return_type Class##func(Class *_this, ##type_args)

// Private Method Definition
#define _METHOD(Class, return_type, func, type_args...) \
    return_type _##Class##func(Class *_this, ##type_args)

#define VIRTUAL_METHOD(Father, Class, return_type, func, type_args...) \
    return_type Class##func(Father *_this, ##type_args)

// Interface
#define INTERFACE(Class)        \
    typedef struct Class Class; \
    struct Class

// Abstract Class
#define ABSTRACT(Class)         \
    typedef struct Class Class; \
    void __##Class##Ctor();     \
    void __##Class##Dtor();     \
    struct Class

#define ABSTRACT_CTOR(Class, type_args...) \
    void __##Class##Ctor(Class *_this, ##type_args)

#define ABSTRACT_DTOR(Class)      \
    int __Delete##Class(Class *c) \
    {                             \
        if (!c)                   \
            return 1;             \
        __##Class##Dtor(c);       \
        free(c);                  \
        return 0;                 \
    }                             \
    void __##Class##Dtor(Class *_this)

// Class
#define CLASS(Class)            \
    typedef struct Class Class; \
    void __##Class##Ctor();     \
    void __##Class##Dtor();     \
    int __New##Class();         \
    int __Delete##Class();      \
    struct Class

#define CLASS_CTOR(Class, type_args...)          \
    int __New##Class(Class **c_ptr)              \
    {                                            \
        *c_ptr = (Class *)malloc(sizeof(Class)); \
        if (!*c_ptr)                             \
            return 1;                            \
        return 0;                                \
    }                                            \
    void __##Class##Ctor(Class *_this, ##type_args)

#define CLASS_DTOR(Class)         \
    int __Delete##Class(Class *c) \
    {                             \
        if (!c)                   \
            return 1;             \
        __##Class##Dtor(c);       \
        free(c);                  \
        return 0;                 \
    }                             \
    void __##Class##Dtor(Class *_this)

#define VIRTUAL_DTOR(Base, Class) \
    int __Delete##Class(Class *c) \
    {                             \
        if (!c)                   \
            return 1;             \
        __##Class##Dtor(c);       \
        free(c);                  \
        return 0;                 \
    }                             \
    void __##Class##Dtor(Base *_this)

#define NEW(Class, c, args...)          \
    ({                                  \
        {                               \
            __New##Class(&c);           \
            __##Class##Ctor(c, ##args); \
        }                               \
        c;                              \
    })

#define DELETE(Class, c) \
    (__Delete##Class(c))

#define INHERIT(Father) \
    struct Father Father

#define BIND(Class, func) \
    _this->func = Class##func

#define OVERRIDE(inheritance, Class, func) \
    _this->inheritance.func = Class##func

#define OVERRIDE_VIRTUAL_DTOR(inheritance, Class, func) \
    _this->inheritance.__##Base##Dtor = __##Class##Dtor

#define SUPER(Father, c) \
    ((Father *)(&c->Father))

#define SUPER_2(GrandFather, Father, c) \
    SUPER(GrandFather, SUPER(Father, c)

#define SUPER_3(GrandGrandFather, GrandFather, Father, c) \
    SUPER(GrandGrandFather,SUPER(GrandFather, SUPER(Father, c))

#define SUPER_CTOR(Father, args...) \
    __##Father##Ctor(SUPER(Father, _this), ##args)

#define SUPER_DTOR(Father) \
    __##Father##Dtor(SUPER(Father, _this))

#define SUB(Father, Son, c) \
    ((Son *)((char *)c - offsetof(Son, Father)))

#define SUB_2(GrandFather, Father, Son, c) \
    SUB(GrandFather, Father, SUB(Father, Son, c))

#define SUB_3(GrandGrandFather, GrandFather, Father, Son, c) \
    SUB(GrandGrandFather, GrandFather, SUB(GrandFather, Father, SUB(Father, Son, c)))