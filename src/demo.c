#include <stdio.h>
#include <string.h>

#include "demo.h"

// Animal
void AnimalSetName(Animal *_this, const char *name)
{
    strcpy(_this->name, name);
}

void AnimalSayHello(Animal *_this)
{
    printf("Hello, it's %s\n", _this->name);
}

ABSTRACT_CTOR(Animal, const char *name)
{
    BIND(Animal, SetName);
    BIND(Animal, SayHello);
    _this->SetName(_this, name);
}

// Mouse
void MouseSayHello(Animal *_this)
{
    AnimalSayHello(_this);
    printf("Zi!\n");
}

CLASS_CTOR(Mouse)
{
    SUPER_CTOR(Animal, "Jerry");
    OVERWRITE(Animal, Mouse, SayHello);
}

CLASS_DTOR(Mouse)
{
}

// Cat
void CatSayHello(Animal *_this)
{
    AnimalSayHello(_this);
    printf("Mew!\n");
}

CLASS_CTOR(Cat)
{
    SUPER_CTOR(Animal, "Tom");
    OVERWRITE(Animal, Cat, SayHello);
}

CLASS_DTOR(Cat)
{
}

// Dog
void DogSayHello(Animal *_this)
{
    AnimalSayHello(_this);
    printf("Wow!\n");
}

CLASS_CTOR(Dog, const char *name)
{
    SUPER_CTOR(Animal, name);
    OVERWRITE(Animal, Dog, SayHello);
}

CLASS_DTOR(Dog)
{
}

int main(int argc, char *argv[])
{
    printf("Hello world!\n");

    Cat *tom = NEW(Cat, tom);
    Mouse *jerry = NEW(Mouse, jerry);
    Dog *dog = NEW(Dog, dog, "Spike");

    Animal *animalList[3] = {0};

    animalList[0] = SUPER(Animal, tom);
    animalList[1] = SUPER(Animal, jerry);
    animalList[2] = SUPER(Animal, dog);

    for (int i = 0; i < 3; i++)
    {
        animalList[i]->SayHello(animalList[i]);
    }

    Dog *dog2;
    Animal *ani2 = SUPER(Animal, NEW(Dog, dog2, "Spike"));
    Dog *dog3 = ((Dog *)((char *)ani2 - offsetof(Dog, Animal)));

    DELETE(Dog, dog);
    DELETE(Mouse, jerry);
    DELETE(Cat, tom);

    getchar();
    getchar();

    return 0;
}
