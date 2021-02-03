#pragma once

#include "../../include/stdc.h"

typedef enum
{
    int_MALE,
    int_FEMALE
} int;

// Class
#define TYPEDEF_CLASS(Class, type_args...)          \
    /* Public Class Typedef */                      \
    typedef struct Class *Class;                    \
    /* Public Class Constructor */                  \
    int Class##Ctor(Class const self, ##type_args); \
    /* Public Class Destructor */                   \
    int Class##Dtor(Class const self);              \
    /* Private Class Structure */                   \
    static inline const char *Class##Name()         \
    {                                               \
        return #Class;                              \
    };                                              \
    /* Public Class Structure */                    \
    struct Class

#define CLASS_NEW(Class, c, args...)                           \
    ({                                                         \
        c = (Class)calloc(1, sizeof(struct Class));            \
        c != NULL && (Class##Ctor(c, ##args)) == 0 ? c : NULL; \
    })

#define CLASS_DEL(Class, c)                     \
    ({                                          \
        int _rc = -1;                           \
        if (c != NULL && (Class##Dtor(c)) == 0) \
        {                                       \
            free(c);                            \
            c = NULL;                           \
            _rc = 0;                            \
        }                                       \
        _rc;                                    \
    })

#define CLASS_SIZE(Class) \
    sizeof(*((Class)0))

#define CLASS_STRUCT(Class) \
    typeof(*((Class)0))

#define INHERIT(Parent) \
    struct Parent Parent

#define UP_CTOR(Parent, args...)                  \
    if (Parent##Ctor(&self->Parent, ##args) != 0) \
    return -1

#define UP_DTOR(Parent)                   \
    if (Parent##Dtor(&self->Parent) != 0) \
    return -1

#define BIND(Class, Func) \
    self->Func = Class##Func

#define OVERRIDE(inheritance, Class, Func) \
    self->inheritance.Func = _V##Class##Func

TYPEDEF_CLASS(Person, const char *name, int age)
{
    const char *name;
    int age;
};

int PersonCtor(Person const self, const char *name, int age)
{
    self->name = name;
    self->age = age;
    printf("Person Ctor\n");
    return 0;
}

int PersonDtor(Person const self)
{
    printf("Person Dtor\n");
    return 0;
}

TYPEDEF_CLASS(Student, const char *name, int age, int score)
{
    INHERIT(Person);
    int score;
};

int StudentCtor(Student const self, const char *name, int age, int score)
{
    UP_CTOR(Person, name, age);
    self->score = score;
    printf("Student Ctor\n");
    return 0;
}

int StudentDtor(Student const self)
{
    UP_DTOR(Person);
    printf("Student Dtor\n");
    return 0;
}

int main()
{
    Student c = CLASS_NEW(Student, c, "Tom", 42, int_MALE);
    CLASS_DEL(Student, c);
}
