#include "../include/pop_c.h"

INTERFACE(SayInter)
{
    FUNC(SayInter, void, SayName);
    FUNC(SayInter, void, SayHello);
};

ABSTRACT(Animal)
{
    INHERIT(SayInter);
    FUNC(Animal, void, SetName, const char *name);
    char _name[30];
};

CLASS(Mouse)
{
    INHERIT(Animal);
};
