#pragma once

#ifndef LAMBDA
#define LAMBDA(return_type, Function_body) \
    ({                                     \
        return_type __fn__ Function_body   \
            __fn__;                        \
    })
#endif
