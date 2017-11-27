/* File : listsirkuler.h */
/* ADT List Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan addressUnit adalah pointer */
/* infotype adalah integer */

#ifndef listofunit_H
#define listofunit_H

#include "unit.h"
#include "point.h"
#include "boolean.h"

#define Nil NULL

typedef struct tElmtlistUnit *addressUnit;
typedef struct tElmtlistUnit {
	Unit info;
	addressUnit next;
} ElmtListUnit;
typedef struct {
	addressUnit First;
} ListUnit;

/* Definisi list : */
/* List kosong : First(L) = Nil */
/* Setiap elemen dengan addressUnit P dapat diacu Info(P), Next(P) */
/* Elemen terakhir list: jika addressUnitnya Last, maka Next(Last)=First(L) */

/* Notasi Akses */
#define InfoUnit(P) (P)->info
#define NextUnit(P) (P)->next
#define FirstUnit(L) ((L).First)

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyUnit (ListUnit L);
/* Mengirim true jika list kosong. Lihat definisi di atas. */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyUnit (ListUnit *L);
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */

/****************** Manajemen Memori ******************/
addressUnit AlokasiUnit (Unit X);
/* Mengirimkan addressUnit hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressUnit tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiUnit (addressUnit P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressUnit P */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressUnit SearchKoordinatUnit (ListUnit L, POINT Koordinat);

boolean IsKingDead(ListUnit L);
/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsUnitFirst (ListUnit *L, Unit X);

void InsUnitLast (ListUnit *L, Unit X);

/*** PENGHAPUSAN ELEMEN ***/
void DelUnitFirst (ListUnit *L, Unit *X);
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelUnitLast (ListUnit *L, Unit *X);
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstUnit (ListUnit *L, addressUnit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressUnit P sebagai elemen pertama */
void InsertLastUnit (ListUnit *L, addressUnit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertAfterUnit (ListUnit *L, addressUnit P, addressUnit Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstUnit (ListUnit *L, addressUnit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelLastUnit (ListUnit *L, addressUnit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void DelAfterUnit (ListUnit *L, addressUnit *Pdel, addressUnit Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
void DelKoordinatUnit (ListUnit *L, POINT Koordinat, Unit *X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressUnit P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
void PrintListUnit(ListUnit L);
Unit SearchNomor( ListUnit L, int nomor);
void ResetMovementPoint(ListUnit *L);
boolean IsKingDead(ListUnit L);
void ResetAttackChance(ListUnit *L);
#endif
