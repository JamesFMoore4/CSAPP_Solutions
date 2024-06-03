/* WARNING: This is buggy code */
// float sum_elements(float a[], unsigned length) {
//     int i;
//     float result = 0;

//     for (i = 0; i <= length-1; i++)
//     result += a[i];
//     return result;
// }

/* Fixed version */
float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;

    for (i = 0; i < length; i++)
        result += a[i];
    return result;
}

