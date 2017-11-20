#include "stackt.h"

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStackPlayer (Stack *S)
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
{
	Top(*S) = Nil;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStackPlayer (Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
	return TopPlayer(S) == Nil;
}

boolean IsFullStackPlayer (Stack S)
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
{
	return TopPlayer(S) == MaxEl;
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void PushPlayer (Stack * S, infotype X)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
	TopPlayer(*S)++;
	InfoTopPlayer(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void PopPlayer (Stack * S, infotype* X)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
	*X = InfoTopPlayer(*S);
	TopPlayer(*S)--;
}
