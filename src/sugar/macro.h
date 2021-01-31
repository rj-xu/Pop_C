#define FIELD_SIZEOF(t, f) (sizeof(((t *)0)->f))

#define BUILD_BUG_ON_ZERO(e) (sizeof(char[1 - 2 * !!(e)]) - 1)

#define __must_be_array(a) BUILD_BUG_ON_ZERO(__builtin_types_compatible_p(typeof(a), typeof(&a[0])))

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]) + __must_be_array(a)
#define IS_ARRAY_PTR(p)    (!__builtin_types_compatible_p(typeof(p), typeof(&p[0])))
