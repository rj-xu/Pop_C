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
    BIND(_Animal, _SetName);
    _this->_SetName(_this, name);
}

ABSTRACT_DTOR(Animal)
{
}

// Mouse
VIRTUAL_METHOD(ISay, Mouse, void, SayName)
{
    Animal *_this_animal = SUPER(Animal, SUB(ISay, Mouse, _THIS));
    printf("Hi, I'm %s!\n", _this_animal->_name);
}

VIRTUAL_METHOD(ISay, Mouse, void, SayHello)
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

    Mouse *jerry = NEW(Mouse, jerry, "Jerry");

    ISay *say = SUPER(ISay, jerry);
    say->SayName(&say);
    say->SayHello(&say);

    DELETE(Mouse, jerry);

    getchar();
    getchar();

    return 0;
}
