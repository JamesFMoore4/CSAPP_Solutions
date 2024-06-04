#include <stdint.h>

int tmult_ok(int x, int y)
{
    int64_t product = (int64_t) x*y;
    return product == (int)product;   
}

