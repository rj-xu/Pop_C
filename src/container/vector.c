#include "vector.h"

struct My_t
{
    int a;
};


VEC_TYPEDEF(My, struct My_t);
VEC_TYPEDEF(Int, int);


int main()
{
    VecInt_t a = VEC(VecInt_t, 10);
    VecIntPushBack(a, 1);

}
