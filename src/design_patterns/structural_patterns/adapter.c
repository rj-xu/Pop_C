#include <stdio.h>

#include "../../../include/pop_c.h"

/**
 * The Target defines the domain-specific interface used by the client code.
 */
ABSTRACT(Target)
{
    VBFUNC(Target, const char *, Request);
};

METHOD(Target, const char *, Request)
{
    return "Target: The default target's behavior.";
}

ABSTRACT_CTOR(Target)
{
    BIND(Target, Request);
}

ABSTRACT_DTOR(Target)
{
}

/**
 * The Adaptee contains some useful behavior, but its interface is incompatible
 * with the existing client code. The Adaptee needs some adaptation before the
 * client code can use it.
 */
CLASS(Adaptee)
{
    FUNC(Adaptee, const char *, SpecificRequest);
};

METHOD(Adaptee, const char *, SpecificRequest)
{
    return ".eetpadA eht fo roivaheb laicepS";
}

CLASS_CTOR(Adaptee)
{
    BIND(Adaptee, SpecificRequest);
}

CLASS_DTOR(Adaptee)
{
}

/**
 * The Adapter makes the Adaptee's interface compatible with the Target's
 * interface.
 */
CLASS(Adapter)
{
    INHERIT(Target);
    VFUNC(Target, const char *, Request);
    _FUNC(Adapter, void, Reverse, char *s);
    Adaptee *_adaptee;
};

VMETHOD(Target, Adapter, const char *, Request)
{
    _THIS(Target, Adapter);
    char *to_reverse = malloc(sizeof(char) * 100);
    strcpy(to_reverse, _this->_adaptee->SpecificRequest(_base));
    std::reverse(to_reverse.begin(), to_reverse.end());
    return "Adapter: (TRANSLATED) " + to_reverse;
}

_FUNC(dapter, void, Reverse, char *s)
{
}

CLASS_CTOR(Adapter, Adaptee *adaptee)
{
    SUPER_CTOR(Target);
    OVERRIDE(Target, Adapter, Request);
    _this->_adaptee = adaptee;
}

CLASS_DTOR(Adapter)
{
    SUPER_DTOR(Target);
}

/**
 * The client code supports all classes that follow the Target interface.
 */
void ClientCode(const Target *target)
{
    std::cout << target->Request();
}

int main()
{
    std::cout << "Client: I can work just fine with the Target objects:\n";
    Target *target = new Target;
    ClientCode(target);
    std::cout << "\n\n";
    Adaptee *adaptee = new Adaptee;
    std::cout << "Client: The Adaptee class has a weird interface. See, I don't understand it:\n";
    std::cout << "Adaptee: " << adaptee->SpecificRequest();
    std::cout << "\n\n";
    std::cout << "Client: But I can work with it via the Adapter:\n";
    Adapter *adapter = new Adapter(adaptee);
    ClientCode(adapter);
    std::cout << "\n";

    delete target;
    delete adaptee;
    delete adapter;

    return 0;
}