#include "../include/pop_c.h"

ABSTRACT(Animal)
{
    char name[30];

    void (*SetName)(Animal * _this, const char *name);
    void (*SayHello)(Animal * _this);
};

CLASS(Mouse)
{
    INHERIT(Animal);
};

CLASS(Cat)
{
    INHERIT(Animal);
};

CLASS(Dog)
{
    char master[30];
    INHERIT(Animal);
};
