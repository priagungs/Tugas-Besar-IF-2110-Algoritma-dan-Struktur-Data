/* File : StackPointlist.h */
#ifndef _StackPointLIST_H
#define _StackPointLIST_H

#include "boolean.h"
#include <stdlib.h>
#include "point.h"

/* Konstanta */
#define Nil NULL

/* Deklarasi infotype */
typedef struct{
	POINT Pt;
	int mp;
}infotypeU;

/* StackPoint dengan representasi berkait dengan pointer */
typedef struct tElmtStackPoint * addressU;
typedef struct tElmtStackPoint {
	infotypeU Info;
	addressU Next;
} ElmtStackPoint;

/* Type StackPoint dengan ciri TOP : */
typedef struct {
	addressU TOP;  /* alamat TOP: elemen puncak */
} StackPoint;

/* Selektor */
#define TopPoint(S) (S).TOP
#define InfoTopPoint(S) (S).TOP->Info
#define Next(P) (P)->Next
#define Info(P) (P)->Info

/* Prototype manajemen memori */
void AlokasiPointStack (addressU *P, infotypeU X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void DealokasiPointStack (addressU P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

/* ********* PROTOTYPE REPRESENTASI LOJIK StackPoint ***************/
boolean IsEmptyPointStack (StackPoint S);
/* Mengirim true jika StackPoint kosong: TOP(S) = Nil */
void CreateEmptyPointStack (StackPoint * S);
/* I.S. sembarang */
/* F.S. Membuat sebuah StackPoint S yang kosong */
void PushPoint (StackPoint * S, infotypeU X);
/* Menambahkan X sebagai elemen StackPoint S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void PopPoint (StackPoint * S, infotypeU * X);
/* Menghapus X dari StackPoint S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif
