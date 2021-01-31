#pragma once

#ifndef ENUM_CLASS
#define ENUM_CLASS(NAME, _ENUMS...) \
    typedef enum                    \
    {                               \
        _ENUMS                      \
    } _##NAME;                      \
    typedef struct                  \
    {                               \
        _##NAME _raw;               \
    } NAME
// #define ENUM_0 ((NAME){_ENUM_0})
// #define ENUM_1 ((NAME){_ENUM_1})
#define ENUM_EQ(x, value) ({typeof(x) _y = value; (void) _y; x._raw == _##value; })
#endif
