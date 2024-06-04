/* Determine whether string s is longer than string t */
/* WARNING: This function is buggy */
// int strlonger(char *s, char *t) {
//     return strlen(s) - strlen(t) > 0;
// }

/*Fixed code*/
#include <string.h>

int strlonger(char *s, char *t) {
    return strlen(s) > strlen(t);
}