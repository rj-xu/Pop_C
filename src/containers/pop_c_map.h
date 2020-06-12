#include "../../include/pop_c.h"

CLASS(_cmap_node_t)
{
    char *key;
    void * val;
    int type;
}

CLASS(cmap)
{
    FUNC(cmap, void, Add, char *key, void *val);
    FUNC(cmap, int, Get, char *key);
    FUNC(cmap, void, Delete, char *key);
    
}