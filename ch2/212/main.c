#include <stdio.h>

int main(void)
{

    long x = 0x87654321;

    printf("0x%.16x\n", x & 0xFF);
    printf("0x%.16x\n", x ^ ~0xFF);
    printf("0x%.16x\n", x | 0xFF);

    return 0;
}