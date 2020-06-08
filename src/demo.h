#include "../include/pop_c.h"

INTERFACE(ISay)
{
    VIRTUAL_FUNC(ISay, ISay, void, SayName);
    VIRTUAL_FUNC(ISay, ISay, void, SayHello);
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
    VIRTUAL_FUNC(ISay, Mouse, void, SayName);
    VIRTUAL_FUNC(ISay, Mouse, void, SayHello);
};
