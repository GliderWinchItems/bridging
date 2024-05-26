/*******************************************************************************
* File Name          : bubblesort_uint32_t.c
* Date First Issued  : 05/18/2024
* Board              : 
* Description        : Basic bubble sort Rosetta code
*******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
/* **************************************************************************************
 * uint32_t bubble_sort_uint32t(uint32_t *a, uint32_t n);
 * @brief   : Convert CAN id from ascii/hex to unint32_t
 * @param   : pc = pointer to uint32_t array
 * @param   " n  = size of array"
 * @return  : number of compares
 * ************************************************************************************** */
uint32_t bubble_sort_uint32t(uint32_t *a, uint32_t n) 
{
	uint32_t cmpct = 0;
    int i, t, j = n, s = 1;
    while (s) {
        s = 0;
        for (i = 1; i < j; i++) 
        {
            if (a[i] < a[i - 1]) 
            {
                t = a[i];
                a[i] = a[i - 1];
                a[i - 1] = t;
                s = 1;
            }
        }
        cmpct += j;
        j--;
    }
    return cmpct;
}
#if 0
int main () {
	uint32_t ct;
    int a[] = {4, 65, 2, -31, 0, 99, 2, 83, 782, 1};
    int n = sizeof a / sizeof a[0];
    int i;
    for (i = 0; i < n; i++)
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    ct = bubble_sort(a, n);
    printf("cmpct: %i\n",ct);
    for (i = 0; i < n; i++)
        printf("%d%s", a[i], i == n - 1 ? "\n" : " ");
    return 0;
}
#endif