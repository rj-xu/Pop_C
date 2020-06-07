#include <stdio.h>
#include <string.h>

#include "demo.h"

// SayInter

// Animal
METHOD(Animal, void, SetName, const char *name)
{
    strcpy(_this->_name, name);
}

ABSTRACT_CTOR(Animal, const char *name)
{
    BIND(Animal, SetName);
    _this->SetName(_this, name);
}

ABSTRACT_DTOR(Animal)
{
}

// Mouse
VIRTUAL_METHOD(SayInter, Mouse, void, SayHello)
{
    printf("Zi!\n");
}

CLASS_CTOR(Mouse)
{
    SUPER_CTOR(Animal, "Jerry");
    OVERRIDE(Animal.SayInter, Mouse, SayHello);
}

CLASS_DTOR(Mouse)
{
    SUPER_DTOR(Animal);
}

int main(int argc, char *argv[])
{
    printf("Hello world!\n");

    Mouse *jerry = NEW(Mouse, jerry);

    Animal *animalList[3] = {0};

    // animalList[0] = SUPER(Animal, tom);
    animalList[1] = SUPER(Animal, jerry);
    // animalList[2] = SUPER(Animal, dog);

    for (int i = 1; i < 2; i++)
    {
        animalList[i]->SayHello(animalList[i]);
    }

    // DELETE(Dog, dog);
    DELETE(Mouse, jerry);
    // DELETE(Cat, tom);

    getchar();
    getchar();

    return 0;
}
