#include "../include/pop_c.h"

INTERFACE(ISay)
{
    VBFUNC(ISay, void, SayName);
    VBFUNC(ISay, void, SayHello);
};

ABSTRACT(Animal)
{
    _FUNC(Animal, void, SetName, const char *name);
    char _name[30];
};

CLASS(Mouse)
{
    INHERIT(Animal);
    INHERIT(ISay);
    VFUNC(ISay, void, SayName);
    VFUNC(ISay, void, SayHello);
};
