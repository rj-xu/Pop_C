#pragma once

#ifndef STRINGIZE
#define STRINGIZE(x) _STRINGIZE(x)
#define _STRINGIZE(x) #x
#endif

#ifndef CONCATE
#define CONCATE(x, y) _CONCATE(x, y)
#define _CONCATE(x, y) x##y
#endif

#ifndef COUNT_ARGS
#define COUNT_ARGS(args...) _COUNT_ARGS(_, ##args,      \
                                        10, 9, 8, 7, 6, \
                                        5, 4, 3, 2, 1,  \
                                        0)
#define _COUNT_ARGS(_,                  \
                    _0, _1, _2, _3, _4, \
                    _5, _6, _7, _8, _9, \
                    args...) _COUT_ARGS_FIRST(args)
#define _COUT_ARGS_FIRST(count, args...) count
#endif

// int a0 = COUNT_ARGS(0);
// int a1 = COUNT_ARGS(a);
// int a2 = COUNT_ARGS(a, b);
// int a10 = COUNT_ARGS(a, b, c, d, e,
//                      f, g, h, i, j);
// int a11 = COUNT_ARGS(a, b, c, d, e,
//                      f, g, h, i, j, k);
