/* Determine whether string s is longer than string t */
/* WARNING: This function is buggy */
// int strlonger(char *s, char *t) {
//     return strlen(s) - strlen(t) > 0;
// }

/*
    A. When string t is longer than string s, the result is incorrect.
    B. The result of the subtraction operation would result in a negative number, were integers being subtracted. However, with unsigned numbers, this will cause a "wrap-around",
    where the result will be a very high number. Thus, the correct output will only be achieved when strlen(s) - strlen(t) >= 0.
    C. See function below.
*/
#include <string.h>

int strlonger(char *s, char *t) {
    return strlen(s) > strlen(t);
}