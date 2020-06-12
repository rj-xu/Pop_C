#include "../../include/pop_c.h"

INTERFACE(ISay)
{
    VBFUNC(ISay, void, SayName);
    VBFUNC(ISay, void, SayHello);
};

ABSTRACT(Animal, const char *name)
{
    char _name[30];
};
_FUNC(Animal, void, SetName, const char *name);

CLASS(Mouse, const char *name)
{
    INHERIT(Animal);
    INHERIT(ISay);
    VFUNC(ISay, void, SayName);
    VFUNC(ISay, void, SayHello);
};
