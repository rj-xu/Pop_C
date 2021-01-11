#pragma once

#ifndef ENUM_CLASS
#define ENUM_CLASS(Class) \
    typedef struct        \
    {                     \
        int _raw;         \
    } Class;              \
    enum _##Class
//  {
//      _CLASS_ENUM_0,
//      _CLASS_ENUM_1,
//  };
// #define CLASS_ENUM_0 ((Class){_CLASS_ENUM_0})
// #define CLASS_ENUM_1 ((Class){_CLASS_ENUM_1})
#define ENUM_EQ(x, value) ({typeof(x) _y = value; (void) _y; x._raw == _##value; })
#endif
