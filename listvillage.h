#ifndef Listvillage_H
#define Listvillage_H

#include "village.h"
#include "boolean.h"

#define Nil NULL

typedef struct tElmtListVil *addressVillage;
typedef struct tElmtListVil {
	Village info;
	addressVillage next;
} ElmtListVil;
typedef struct {
	addressVillage First;
} ListVil;

/* Notasi Akses */
#define InfoVillage(P) (P)->info
#define NextVillage(P) (P)->next
#define FirstVillage(L) ((L).First)

/* PROTOTYPE */
/****************** TEST ListVil KOSONG ******************/
boolean IsEmptyVil (ListVil L);
/****************** PEMBUATAN ListVil KOSONG ******************/
void CreateEmptyVil (ListVil *L);

/****************** Manajemen Memori ******************/
addressVillage AlokasiVil (Village X);
/* Mengirimkan addressVillage hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressVillage tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
void DealokasiVil (addressVillage P);
/* Melakukan dealokasi/pengembalian addressVillage P */

/****************** PENCARIAN SEBUAH ELEMEN ListVil ******************/
addressVillage SearchVil (ListVil L, Village X);
/* Mencari apakah ada elemen ListVil dengan Info(P)= X */
/* Jika ada, mengirimkan addressVillage elemen tersebut. */

addressVillage SearchKoordinatVil (ListVil L, POINT Koordinat);

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstVil (ListVil *L, Village X);
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
void InsVLastVil (ListVil *L, Village X);
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen ListVil di akhir: elemen terakhir yang baru bernilai X*/

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstVil (ListVil *L, Village * X);
/* I.S. ListVil L tidak kosong  */
/* F.S. Elemen pertama ListVil dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
void DelVLastVil (ListVil *L, Village * X);
/* I.S. ListVil tidak kosong */
/* F.S. Elemen terakhir ListVil dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstVil (ListVil *L, addressVillage P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressVillage P sebagai elemen pertama */
void InsertLastVil (ListVil *L, addressVillage P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
void InsertAfterVil (ListVil *L, addressVillage P, addressVillage Prec);
/* I.S. Prec pastilah elemen ListVil dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstVil (ListVil *L, addressVillage *P);
/* I.S. ListVil tidak kosong */
/* F.S. P adalah alamat elemen pertama ListVil sebelum penghapusan */
/*      Elemen ListVil berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
void DelLastVil (ListVil *L, addressVillage *P);
/* I.S. ListVil tidak kosong */
/* F.S. P adalah alamat elemen terakhir ListVil sebelum penghapusan  */
/*      Elemen ListVil berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
void DelAfterVil (ListVil *L, addressVillage *Pdel, addressVillage Prec);
/* I.S. ListVil tidak kosong. Prec adalah anggota ListVil  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen ListVil yang dihapus  */
void DelPVil (ListVil *L, Village X);
/* I.S. Sembarang */
/* F.S. Jika ada elemen ListVil beraddressVillage P, dengan Info(P)=X  */
/* Maka P dihapus dari ListVil dan di-dealokasi */
/* Jika tidak ada elemen ListVil dengan Info(P)=X, maka ListVil tetap */
/* ListVil mungkin menjadi kosong karena penghapusan */

/****************** PROSES SEMUA ELEMEN ListVil ******************/
void PrintListVillage (ListVil L);
#endif