/* File : listofunit.h */
/* ADT List Sirkuler dengan elemen terakhir menunjuk pada elemen pertama */
/* Representasi berkait dengan addressUnit adalah pointer */
/* infotype adalah Unit */

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
/* Mengirimkan addressUnit hasil alokasi sebuah unit */
/* Jika alokasi berhasil, maka addressUnit tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */

void DealokasiUnit (addressUnit P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressUnit P */

/****************** PENCARIAN SEBUAH unit LIST ******************/
addressUnit SearchKoordinatUnit (ListUnit L, POINT Koordinat);
/* Searching Unit X yang memiliki posisi di Koordinat */
/* Jika ketemu, makam mengirimkan addressUnit dari Unit X tsb */
/* Jika tidak, mengirimkan Nil */

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN UNIT ***/
void InsUnitFirst (ListUnit *L, Unit X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah unit dan */
/* menambahkan unit X sebagai unit pertama pada list jika alokasi berhasil */

void InsUnitLast (ListUnit *L, Unit X);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah unit dan */
/* menambahkan unit X pada list di akhir: unit terakhir yang baru */
/* jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

/*** PENGHAPUSAN unit ***/
void DelUnitFirst (ListUnit *L, Unit * X);
/* I.S. List L tidak kosong  */
/* F.S. unit pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat unit pertama di-dealokasi */

void DelUnitLast (ListUnit *L, Unit * X);
/* I.S. list tidak kosong */
/* F.S. unit terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat unit terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN unit BERDASARKAN ALAMAT ***/
void InsertFirstUnit (ListUnit *L, addressUnit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan unit ber-addressUnit P sebagai unit pertama */

void InsertLastUnit (ListUnit *L, addressUnit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai unit terakhir yang baru */

void InsertAfterUnit (ListUnit *L, addressUnit P, addressUnit Prec); 
/* I.S. Prec pastilah unit list dan bukan unit terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai unit sesudah unit beralamat Prec */

/*** PENGHAPUSAN SEBUAH unit ***/
void DelFirstUnit (ListUnit *L, addressUnit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat unit pertama list sebelum penghapusan */
/*      unit list berkurang satu (mungkin menjadi kosong) */
/* First unitt yg baru adalah suksesor unit pertama yang lama */

void DelLastUnit (ListUnit *L, addressUnit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat unit terakhir list sebelum penghapusan  */
/*      unit list berkurang satu (mungkin menjadi kosong) */
/* Last unitt baru adalah predesesor unit pertama yg lama, */
/* jika ada */

void DelAfterUnit (ListUnit *L, addressUnit *Pdel, addressUnit Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat unit list yang dihapus  */

void DelKoordinatUnit (ListUnit *L, POINT Koordinat, Unit *X);
/* I.S. Sembarang */
/* F.S. Jika ada unit list beraddressUnit P, dengan lokasi Koordinat  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada unit list dengan lokasi Koordinat, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

/* OPERASI TRAVERSAL */
void PrintListUnit(ListUnit L);
/* Menuliskan ke layar daftar unit yang dimiliki L */

Unit SearchNomor( ListUnit L, int nomor);
/* Mengirimkan Unit yang memiliki indeks nomor */

void ResetMovementPoint(ListUnit *L);
/* Mereset movement point seluruh unit pada ListUnit L menjadi Max */

boolean IsKingDead(ListUnit L);
/* Mengirimkan nilai true jika Unit King
   yang berada pada ListUnit L sudah tidak ada/mati */

void ResetAttackChance(ListUnit *L);
/* Mereset attack chance seluruh unit pada ListUnit L nenjadi true */

#endif
