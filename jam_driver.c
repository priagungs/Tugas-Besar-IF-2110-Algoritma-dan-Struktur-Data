/* NIM      : 13516017 */
/* Nama     : Muhammad Nurraihan Naufal */
/* Tanggal  : 27 Nov 2017 */
/* Driver untuk menguji adt jam */

#include <stdio.h>
#include "jam.h"

int main() {
    /* KAMUS */
    JAM J1, J2;
    long N;
    /* ALGORITMA */
    printf("Masukan jam:\n");
    BacaJAM(&J1);
    printf("Jam: ");
    TulisJAM(J1);
    
    return 0;
}
