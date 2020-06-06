#pragma once

#include <stddef.h>
#include <stdlib.h>


#define LAMBDA(return_type, function_body) \
    ({                                     \
        return_type __fn__ function_body   \
            __fn__;                        \
    })

#define INTERFACE(_Class)         \
    typedef struct _Class _Class; \
    void __##_Class##Ctor();       \
    void __##_Class##Dtor();       \
    struct _Class

#define ABSTRACT(_Class)          \
    typedef struct _Class _Class; \
    void __##_Class##Ctor();       \
    void __##_Class##Dtor();       \
    int __Delete##_Class();        \
    struct _Class

#define ABSTRACT_CTOR(_Class, _type_args...) \
    void __##_Class##Ctor(_Class *_this, ##_type_args)

#define CLASS(_Class)             \
    typedef struct _Class _Class; \
    void __##_Class##Ctor();       \
    void __##_Class##Dtor();       \
    int __New##_Class();           \
    int __Delete##_Class();        \
    struct _Class

#define CLASS_CTOR(_Class, _type_args...)           \
    int __New##_Class(_Class **_c_ptr)               \
    {                                               \
        *_c_ptr = (_Class *)malloc(sizeof(_Class)); \
        if (!*_c_ptr)                               \
            return 1;                               \
        return 0;                                   \
    }                                               \
    void __##_Class##Ctor(_Class *_this, ##_type_args)

#define CLASS_DTOR(_Class)          \
    int __Delete##_Class(_Class *_c) \
    {                               \
        if (!_c)                    \
            return 1;               \
        __##_Class##Dtor(_c);        \
        free(_c);                   \
        return 0;                   \
    }                               \
    void __##_Class##Dtor(_Class *_this)

#define NEW(_Class, _c, _args...)         \
    ({                                    \
        {                                 \
            __New##_Class(&_c);            \
            __##_Class##Ctor(_c, ##_args); \
        }                                 \
        _c;                               \
    })

#define DELETE(_Class, _c) \
    (__Delete##_Class(_c))

#define INHERIT(_Father) \
    struct _Father _Father

#define BIND(_Class, _func) \
    _this->_func = _Class##_func

#define OVERWRITE(_Father, _Son, _Func) \
    _this->_Father._Func = _Son##_Func

#define SUPER(_Father, _c) \
    ((_Father *)(&_c->_Father))

#define SUPER_CTOR(_Father, _args...) \
    __##_Father##Ctor(SUPER(_Father, _this), ##_args)

#define SUB(_Father, _Son, _c) \
    ((_Son *)((char *)_c - offsetof(_Son, _Father)))
