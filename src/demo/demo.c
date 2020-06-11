#include <stdio.h>
#include <string.h>

#include "demo.h"

// ISay

// Animal
_METHOD(Animal, void, SetName, const char *name)
{
    strcpy(_this->_name, name);
}

ABSTRACT_CTOR(Animal, const char *name)
{
    BIND(Animal, _SetName);
    DO(_this, _SetName, name);
}

ABSTRACT_DTOR(Animal)
{
}

// Mouse
VMETHOD(ISay, Mouse, void, SayName)
{
    _THIS_SW(Animal, ISay, Mouse);
    printf("Hi, I'm %s!\n", _this->_name);
}

VMETHOD(ISay, Mouse, void, SayHello)
{
    printf("Zi!\n");
}

CLASS_CTOR(Mouse, const char *name)
{
    SUPER_CTOR(Animal, name);

    OVERRIDE(ISay, Mouse, SayName);
    OVERRIDE(ISay, Mouse, SayHello);
}

CLASS_DTOR(Mouse)
{
    SUPER_DTOR(Animal);
}

int main(int argc, char *argv[])
{
    printf("Hello world!\n");

    NEW(Mouse, jerry, "Jerry");

    ISay *say = SUPER(ISay, jerry);
    DO(say, SayName);
    DO(say, SayHello);

    DELETE(Mouse, jerry);

    getchar();
    getchar();

    return 0;
}
