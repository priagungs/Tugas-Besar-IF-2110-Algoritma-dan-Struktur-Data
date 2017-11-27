/* NIM      : 13516017 */
/* Nama     : Muhammad Nurraihan Naufal */
/* Tanggal  : 25 November 2017 */
/* Deskripsi: Ini merupakan implementasi dari header jam.h */

#include <stdio.h>
#include "jam.h"

/* ***************************************************************** */
/* DEFINISI PRIMITIF                                                 */
/* ***************************************************************** */
/* KELOMPOK VALIDASI TERHADAP TYPE                                   */
/* ***************************************************************** */
boolean IsJAMValid (int H, int M, int S)
/* Mengirim true  jika H,M,S dapat membentuk J yang valid */
/* dipakai untuk mentest SEBELUM membentuk sebuah Jam */
{
    return (((H>=0)&&(H<=23))&&((M>=0)&&(M<=59))&&((S>=0)&&(S<=59)));
}

/* *** Konstruktor: Membentuk sebuah JAM dari komponen-komponennya *** */
JAM MakeJAM (int HH, int MM, int SS)
/* Membentuk sebuah JAM dari komponen-komponennya yang valid */
/* Prekondisi : HH, MM, SS valid untuk membentuk JAM */
{   /* KAMUS */
    JAM J;
    /* ALGORITMA */
    Hour(J) = HH;
    Minute(J) = MM;
    Second(J) = SS;
    return J;
}

/* ***************************************************************** */
/* KELOMPOK BACA/TULIS                                               */
/* ***************************************************************** */
void BacaJAM (JAM * J)
/* I.S. : J tidak terdefinisi */
/* F.S. : J terdefinisi dan merupakan jam yang valid */
/* Proses : mengulangi membaca komponen HH, MM, SS sehingga membentuk J */
/* yang valid. Tidak mungkin menghasilkan J yang tidak valid. */
/* Pembacaan dilakukan dengan mengetikkan komponen HH, MM, SS
   dalam satu baris, masing-masing dipisahkan 1 spasi, diakhiri enter. */
/* Jika JAM tidak valid maka diberikan pesan: "Jam tidak valid", dan pembacaan
   diulangi hingga didapatkan jam yang valid. */
/* Contoh:
   60 3 4
   Jam tidak valid
   1 3 4
   --> akan terbentuk JAM <1,3,4> */
{
    int HH, MM, SS;

    scanf("%d %d %d",&HH,&MM,&SS);
    do {
        printf("Jam tidak valid\n");
        scanf("%d %d %d",&HH,&MM,&SS);
    }
    while (!IsJAMValid(HH,MM,SS));
    *J = MakeJAM(HH,MM,SS);
}

void TulisJAM (JAM J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS */
/* Proses : menulis nilai setiap komponen J ke layar dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
{
    if (Hour(J)<10)
        printf("0%d:",Hour(J));
    else printf("%d:",Hour(J));

    if (Minute(J)<10)
        printf("0%d:",Minute(J));
    else printf("%d:",Minute(J));

    if (Second(J)<10)
        printf("0%d",Second(J));
    else printf("%d",Second(J));
}

void TulisJAMtoFILE (FILE *fout, JAM J)
/* I.S. : J sembarang */
/* F.S. :   Nilai J ditulis dg format HH:MM:SS ke file fout */
/* Proses : menulis nilai setiap komponen J ke file fout dalam format HH:MM:SS
   tanpa karakter apa pun di depan atau belakangnya, termasuk spasi, enter, dll.*/
{
    if (Hour(J)<10)
        fprintf(fout,"0%d:",Hour(J));
    else fprintf(fout,"%d:",Hour(J));

    if (Minute(J)<10)
        fprintf(fout,"0%d:",Minute(J));
    else fprintf(fout,"%d:",Minute(J));

    if (Second(J)<10)
        fprintf(fout,"0%d",Second(J));
    else fprintf(fout,"%d",Second(J));
}