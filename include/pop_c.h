#pragma once

#include <stddef.h>
#include <stdlib.h>

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

// Abstract Constructor
#define ABSTRACT_CTOR(Class, type_args...) \
    void __##Class##Ctor(Class *_this, ##type_args)

// Abstract Destructor
#define ABSTRACT_DTOR(Class) \
    void __##Class##Dtor(Class *_this)

// Class
#define CLASS(Class)            \
    typedef struct Class Class; \
    void __##Class##Ctor();     \
    void __##Class##Dtor();     \
    int __New##Class();         \
    int __Delete##Class();      \
    struct Class

// Class Constructor
#define CLASS_CTOR(Class, type_args...)          \
    int __New##Class(Class **c_ptr)              \
    {                                            \
        *c_ptr = (Class *)malloc(sizeof(Class)); \
        if (!*c_ptr)                             \
            return 1;                            \
        return 0;                                \
    }                                            \
    void __##Class##Ctor(Class *_this, ##type_args)

// Class Destructor
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

// New
#define NEW(Class, c, args...)          \
    ({                                  \
        {                               \
            __New##Class(&c);           \
            __##Class##Ctor(c, ##args); \
        }                               \
        c;                              \
    })

// Delete
#define DELETE(Class, c) \
    (__Delete##Class(c))

// Public Function Declaration
#define FUNC(Class, return_type, func, type_args...) \
    return_type (*func)(Class * _this, ##type_args)

// Private Function Declaration
#define _FUNC(Class, return_type, func, type_args...) \
    return_type (*_##func)(Class * _this, ##type_args)

// Virtual Function Declaration
#define VIRTUAL_FUNC(Base, Class, return_type, func, type_args...) \
    return_type (*func)(Base * *_base, ##type_args)

// Public Function Definition
#define METHOD(Class, return_type, func, type_args...) \
    return_type Class##func(Class *_this, ##type_args)

// Private Function Definition
#define _METHOD(Class, return_type, func, type_args...) \
    return_type _##Class##_##func(Class *_this, ##type_args)

// Virtual Function Definition
#define VIRTUAL_METHOD(Base, Class, return_type, func, type_args...) \
    return_type Class##func(Base **_base, ##type_args)


#define _VIRTUAL
// Virtual
#define VIRTUAL /_VIRTUAL/

// Inherit
#define INHERIT(Father) \
    struct Father Father

// Binding
#define BIND(Class, func) \
    _this->func = Class##func

// Override
#define OVERRIDE(inheritance, Class, func) \
    _this->inheritance.func = Class##func

// Super
#define SUPER(Father, c) \
    ((Father *)(&(c->Father)))

// Super 2
#define SUPER_2(GrandFather, Father, c) \
    SUPER(GrandFather, SUPER(Father, c)

// Super 3
#define SUPER_3(GrandGrandFather, GrandFather, Father, c) \
    SUPER(GrandGrandFather,SUPER(GrandFather, SUPER(Father, c))

// Sub
#define SUB(Father, Son, c) \
    ((Son *)((char *)c - offsetof(Son, Father)))

// Sub 2
#define SUB_2(GrandFather, Father, Son, c) \
    SUB(GrandFather, Father, SUB(Father, Son, c))

// Sub 3
#define SUB_3(GrandGrandFather, GrandFather, Father, Son, c) \
    SUB(GrandGrandFather, GrandFather, SUB(GrandFather, Father, SUB(Father, Son, c)))

// Father Ctor
#define SUPER_CTOR(Father, args...) \
    __##Father##Ctor(SUPER(Father, _this), ##args)

// Father Dtor
#define SUPER_DTOR(Father) \
    __##Father##Dtor(SUPER(Father, _this))

// This Pointer Only in Virtual Function
#define _THIS (*_base)

// Sub then Super Only in Virtual Function
#define SWITCH(DestFather, SrcFather, Son) \
    SUPER(DestFather, SUB(SrcFather, Son, _THIS));

// Lambda
#define LAMBDA(return_type, function_body) \
    ({                                     \
        return_type __fn__ function_body   \
            __fn__;                        \
    })
