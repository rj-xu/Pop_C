#include <string.h>
#include <stdio.h>

#include "../../../include/pop_c.h"

/**
 * The base Component interface defines operations that can be altered by
 * decorators.
 */
INTERFACE(Component)
{
    VBFUNC(Component, const char *, Operation);
};

/**
 * Concrete Components provide default implementations of the operations. There
 * might be several variations of these classes.
 */
CLASS(ConcreteComponent)
{
    INHERIT(Component);
    VFUNC(Component, const char *, Operation);
};

VMETHOD(Component, ConcreteComponent, const char *, Operation)
{
    return "ConcreteComponent";
}

CLASS_CTOR(ConcreteComponent)
{
    OVERRIDE(Component, ConcreteComponent, Operation);
}

CLASS_DTOR(ConcreteComponent)
{
}

/**
 * The base Decorator class follows the same interface as the other components.
 * The primary purpose of this class is to define the wrapping interface for all
 * concrete decorators. The default implementation of the wrapping code might
 * include a field for storing a wrapped component and the means to initialize
 * it.
 */
ABSTRACT(Decorator, Component *component)
{
    INHERIT(Component);
    VFUNC(Component, const char *, Operation);

    Component *m_component;
};

VMETHOD(Component, Decorator, const char *, Operation)
{
    _THIS(Component, Decorator);
    Component *component = _this->m_component;
    return DO(component, Operation);
}

ABSTRACT_CTOR(Decorator, Component *component)
{
    OVERRIDE(Component, Decorator, Operation);
    _this->m_component = component;
}

ABSTRACT_DTOR(Decorator)
{
}

/**
 * Concrete Decorators call the wrapped object and alter its result in some way.
 */
CLASS(ConcreteDecoratorA, Component *component)
{
    INHERIT(Decorator);
    VFUNC(Component, const char *, Operation);
    char *temp_str;
};

VMETHOD(Component, ConcreteDecoratorA, const char *, Operation)
{
    _THIS_2(Component, Decorator, ConcreteDecoratorA);
    strcpy(_this->temp_str, "ConcreteDecoratorA(");
    strcat(_this->temp_str, _VDecoratorOperation(_base));
    strcat(_this->temp_str, ")");

    return _this->temp_str;
}

CLASS_CTOR(ConcreteDecoratorA, Component *component)
{
    SUPER_CTOR(Decorator, component);
    OVERRIDE(Decorator.Component, ConcreteDecoratorA, Operation);
    _this->temp_str = malloc(sizeof(char) * 100);
}

CLASS_DTOR(ConcreteDecoratorA)
{
    free(_this->temp_str);
    SUPER_DTOR(Decorator);
}

CLASS(ConcreteDecoratorB, Component *component)
{
    INHERIT(Decorator);
    VFUNC(Component, const char *, Operation);
    char *temp_str;
};

VMETHOD(Component, ConcreteDecoratorB, const char *, Operation)
{
    _THIS_2(Component, Decorator, ConcreteDecoratorB);
    strcpy(_this->temp_str, "ConcreteDecoratorB(");
    strcat(_this->temp_str, _VDecoratorOperation(_base));
    strcat(_this->temp_str, ")");

    return _this->temp_str;
}

CLASS_CTOR(ConcreteDecoratorB, Component *component)
{
    SUPER_CTOR(Decorator, component);
    OVERRIDE(Decorator.Component, ConcreteDecoratorB, Operation);
    _this->temp_str = malloc(sizeof(char) * 100);
}

CLASS_DTOR(ConcreteDecoratorB)
{
    free(_this->temp_str);
    SUPER_DTOR(Decorator);
}

/**
 * The client code works with all objects using the Component interface. This
 * way it can stay independent of the concrete classes of components it works
 * with.
 */
void ClientCode(Component *component)
{
    printf("RESULT: %s", DO(component, Operation));
}

int main()
{
    NEW(ConcreteComponent, concrete_component);
    Component *simple1 = SUPER(Component, concrete_component);

    printf("Client: I've got a simple component:\n");
    ClientCode(simple1);
    printf("\n\n");

    NEW(ConcreteDecoratorA, decorator1, simple1);
    Component *temp = SUPER_2(Component, Decorator, decorator1);
    NEW(ConcreteDecoratorB, decorator2, temp);
    Component *simple2 = SUPER_2(Component, Decorator, decorator2);

    printf("Client: Now I've got a decorated component:\n");
    ClientCode(simple2);
    printf("\n");

    DELETE(ConcreteDecoratorB, decorator2);
    DELETE(ConcreteDecoratorA, decorator1);
    DELETE(ConcreteComponent, concrete_component);

    return 0;
}