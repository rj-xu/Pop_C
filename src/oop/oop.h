#pragma once

#include "stdc.h"

// Interface
#define INTERFACE(Class)        \
    typedef struct Class Class; \
    struct Class

// Abstract Class
#define ABSTRACT(Class, type_args...)                     \
    typedef struct Class Class;                           \
    void _##Class##Ctor(Class *const _this, ##type_args); \
    void _##Class##Dtor(Class *const _this);              \
    struct Class

// Abstract Constructor
#define ABSTRACT_CTOR(Class, type_args...) \
    void _##Class##Ctor(Class *const _this, ##type_args)

// Abstract Destructor
#define ABSTRACT_DTOR(Class) \
    void _##Class##Dtor(Class *const _this)

// Class
#define CLASS(Class, type_args...)                        \
    typedef struct Class Class;                           \
    void _##Class##Ctor(Class *const _this, ##type_args); \
    void _##Class##Dtor(Class *const _this);              \
    void _New##Class(Class **const c_ptr);                \
    void _Delete##Class(Class *const c);                  \
    struct Class

// Class Constructor
#define CLASS_CTOR(Class, type_args...)   \
    void _New##Class(Class **const c_ptr) \
    {                                     \
        *c_ptr = malloc(sizeof(Class));   \
        assert(*c_ptr);                   \
    }                                     \
    void _##Class##Ctor(Class *const _this, ##type_args)

// Class Destructor
#define CLASS_DTOR(Class)               \
    void _Delete##Class(Class *const c) \
    {                                   \
        assert(c);                      \
        _##Class##Dtor(c);              \
        free(c);                        \
    }                                   \
    void _##Class##Dtor(Class *const _this)

// New
#define NEW(Class, c, args...) \
    Class *c = NULL;           \
    _New##Class(&c);           \
    _##Class##Ctor(c, ##args)

// New Pointer
#define NEW_PTR(Class, c, args...)     \
    ({                                 \
        {                              \
            _New##Class(&c);           \
            _##Class##Ctor(c, ##args); \
        }                              \
        (Class *)c;                    \
    })

// Delete
#define DELETE(Class, c) \
    (_Delete##Class(c))

// Static Member Variable Declaration
#define SVAR(Class, type, arg) \
    ; // extern type Class##_arg

// Static Member Variable Definition
#define SMEMBER(Class, type, arg, default_value) \
    static type Class##_##arg = default_value;

// Public Member Function Declaration
#define FUNC(Class, return_type, Func, type_args...) \
    return_type Class##Func(Class *const _this, ##type_args)

// Public Member Function Definition
#define METHOD(Class, return_type, Func, type_args...) \
    return_type Class##Func(Class *const _this, ##type_args)

// Private Member Function Declaration
#define _FUNC(Class, return_type, Func, type_args...) \
    ; // return_type _##Class##Func(Class *const _this, ##type_args)

// Private Member Function Definition
#define _METHOD(Class, return_type, Func, type_args...) \
    static return_type _##Class##Func(Class *const _this, ##type_args)

// Static Member Function Declaration
#define SFUNC(Class, return_type, Func, type_args...) \
    extern return_type Class##Func(##type_args)

// Static Member Function Definition
#define SMETHOD(Class, return_type, Func, type_args...) \
    return_type Class##Func(##type_args)

// Virtual Member Function Declaration in Base
#define VBFUNC(Base, return_type, Func, type_args...) \
    return_type (*Func)(Base *const _base, ##type_args)

// Virtual Member Function Declaration in Class
#define VFUNC(Base, return_type, Func, type_args...) \
    ; // return_type Class##Func(Base *const _base, ##type_args)

// Virtual Member Function Definition
#define VMETHOD(Base, Class, return_type, Func, type_args...) \
    static return_type _V##Class##Func(Base *const _base, ##type_args)

// Public Inheritance
#define INHERIT(Father) \
    struct Father Father

// Binding
#define BIND(Class, Func) \
    _this->Func = Class##Func

// Override
#define OVERRIDE(inheritance, Class, Func) \
    _this->inheritance.Func = _V##Class##Func

// Super
#define SUPER(Father, c) \
    ((Father *)(&(c->Father)))

// Super 2
#define SUPER_2(GrandFather, Father, c) \
    SUPER(GrandFather, SUPER(Father, c))

// Super 3
#define SUPER_3(GrandGrandFather, GrandFather, Father, c) \
    SUPER(GrandGrandFather, SUPER(GrandFather, SUPER(Father, c)))

// Sub
#define SUB(Father, Son, c) \
    ((Son *)((char *)c - offsetof(Son, Father)))

// Sub 2
#define SUB_2(GrandFather, Father, Son, c) \
    SUB(Father, Son, SUB(GrandFather, Father, c))

// Sub 3
#define SUB_3(GrandGrandFather, GrandFather, Father, Son, c) \
    SUB(Father, Son, SUB(GrandFather, Father, SUB(GrandGrandFather, GrandFather, c)))

// Father Constructor Only in CLASS_CTOR Start
#define SUPER_CTOR(Father, args...) \
    _##Father##Ctor(SUPER(Father, _this), ##args)

// Father Destructor Only in CLASS_DTOR End
#define SUPER_DTOR(Father) \
    _##Father##Dtor(SUPER(Father, _this))

// Sub then Super Only in Virtual Member Function
#define SWITCH(DestFather, SrcFather, Son, c) \
    SUPER(DestFather, SUB(SrcFather, Son, c));

// Do Member Function of the Instance and input the Instance
#define DO(c, Func, args...) \
    c->Func(c, ##args)

// This Pointer Only in Virtual Member Function
#define _THIS(Father, Son) \
    Son *const _this = SUB(Father, Son, _base)

// This Pointer 2 Only in Virtual Member Function
#define _THIS_2(GrandFather, Father, Son) \
    Son *const _this = SUB_2(GrandFather, Father, Son, _base)

// This Pointer 3 Only in Virtual Member Function
#define _THIS_3(GrandGrandFather, GrandFather, Father, Son) \
    Son *const _this = SUB_3(GrandGrandFather, GrandFather, Father, Son, _base)

// This Pointer Switch Only in Virtual Member Function
#define _THIS_SW(DestFather, SrcFather, Son) \
    DestFather *const _this = SWITCH(DestFather, SrcFather, Son, _base);

// Super This Pointer
#define _BASE(Father, c, args...) \
    Father *const args##_base = SUPER(Father, c);

// Super 2 This Pointer
#define _BASE_2(GrandFather, Father, c, args...) \
    Father *const args##_base_2 = SUPER_2(GrandFather, Father, c);

// Super 3 This Pointer
#define _BASE_3(GrandGrandFather, GrandFather, Father, c, args...) \
    Father *const args##_base_3 = SUPER_3(GrandGrandFather, GrandFather, Father, c);