# Pop C

Write C like C++ using specific macros and naming rules.

## Features

| Feature        | Status | Note                              |
| -------------- | ------ | --------------------------------- |
| Class          | Done   | Use macro ```CLASS```             |
| Abstract Class | Done   | Use macro ```ABSTRACT```          |
| Interface      | Doing  | Use macro ```INTERFACE```         |
| Constructor    | Done   | Use macro ```CLASS_CTOR```        |
| Destructor     | Done   | Use macro ```CLASS_DTOR```        |
| New            | Done   | Use macro ```NEW```               |
| Delete         | Done   | Use macro ```DELETE```            |
| Inherit        | Done   | Use macro ```INHERIT```           |
| Overwrite      | Done   | Use macro ```OVERWRITE```         |
| Super & Sub    | Doing  | Use macro ```SUPER``` & ```SUB``` |
| Lambda         | Done   | Use macro ```LAMBDA```            |ly
| Namespace      | Done   | Add name prefix ```Namespace```   |
| Private        | Done   | Add name prefix ```_```           |

## Todo

- List initialize
- Protected
- Macro variable name

## Issues

- Destructor and All Methods are not virtual: Normal Inheritance. Son must do ```SUPER_CTOR``` first in own ```CLASS_CTOR``` and do ```SUPER_DTOR``` last in own ```CLASS_DTOR```.
- Destructor is virtual: Base Class. Use macro ```#VIRTUAL_DTOR, SUB, OVERWRITE```.
- Destructor is pure virtual: Abstract Base Class.
- Method is virtual
- Method is pure virtual
- Destructor and All Methods are pure virtual: Interface


