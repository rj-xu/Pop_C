#include "oop.h"

/**
 * The Target defines the domain-specific interface used by the client code.
 */
CLASS(Target)
{
    VBFUNC(Target, const char *, Request);
};

METHOD(Target, const char *, Request)
{
    return "Target: The default target's behavior.";
}

CLASS_CTOR(Target)
{
    BIND(Target, Request);
}

CLASS_DTOR(Target)
{
}

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
CLASS(Adaptee){};
FUNC(Adaptee, const char *, SpecificRequest);

METHOD(Adaptee, const char *, SpecificRequest)
{
    return ".eetpadA eht fo roivaheb laicepS";
}

CLASS_CTOR(Adaptee)
{
}

CLASS_DTOR(Adaptee)
{
}

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface.
 */
CLASS(Adapter, Adaptee *adaptee)
{
    INHERIT(Target);
    VFUNC(Target, const char *, Request);
    Adaptee *_adaptee;
    char *_temp_str;
};
_FUNC(Adapter, void, Reverse, char *str);

_METHOD(Adapter, void, Reverse, char *str)
{
    int len = strlen(str);
    char c = 0;
    for (int i = 0; i < len / 2; i++)
    {
        c = *(str + i);
        *(str + i) = *(str + len - 1 - i);
        *(str + len - 1 - i) = c;
    }
}

VMETHOD(Target, Adapter, const char *, Request)
{
    _THIS(Target, Adapter);
    char *to_reverse = malloc(sizeof(char) * 100);
    strcpy(to_reverse, AdapteeSpecificRequest(_this->_adaptee));
    _AdapterReverse(_this, to_reverse);
    sprintf(_this->_temp_str, "Adapter: (TRANSLATED) %s", to_reverse);
    free(to_reverse);
    return _this->_temp_str;
}

CLASS_CTOR(Adapter, Adaptee *adaptee)
{
    SUPER_CTOR(Target);
    OVERRIDE(Target, Adapter, Request);
    _this->_adaptee = adaptee;
    _this->_temp_str = malloc(sizeof(char) * 100);
}

CLASS_DTOR(Adapter)
{
    free(_this->_temp_str);
    SUPER_DTOR(Target);
}

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(Target *target)
{
    printf("%s", DO(target, Request));
}

int main()
{
    printf("Client: I can work just fine with the Target objects:\n");
    NEW(Target, target);
    ClientCode(target);
    printf("\n\n");

    printf("Client: The Adaptee class has a weird interface. See, I don't understand it:\n");
    NEW(Adaptee, adaptee);
    printf("Adaptee: %s\n\n", AdapteeSpecificRequest(adaptee));

    printf("Client: But I can work with it via the Adapter:\n");
    NEW(Adapter, adapter, adaptee);
    ClientCode(SUPER(Target, adapter));
    printf("\n");

    DELETE(Adapter, adapter);
    DELETE(Adaptee, adaptee);
    DELETE(Target, target);

    return 0;
}
