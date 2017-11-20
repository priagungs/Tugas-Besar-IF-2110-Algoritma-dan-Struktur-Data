/* File : StackPlayerlist.h */
#ifndef _StackPlayerLIST_H
#define _StackPlayerLIST_H

#include "boolean.h"
#include <stdlib.h>
#include "player.h"

/* Konstanta */
#define Nil NULL

/* Deklarasi infotype */
typedef Player infotype;

/* StackPlayer dengan representasi berkait dengan pointer */
typedef struct tElmtStackPlayer * address;
typedef struct tElmtStackPlayer {
	infotype Info;
	address Next;
} ElmtStackPlayer;

/* Type StackPlayer dengan ciri TOP : */
typedef struct {
	address TOP;  /* alamat TOP: elemen puncak */
} StackPlayer;

/* Selektor */
#define TopPlayer(S) (S).TOP
#define InfoTopPlayer(S) (S).TOP->Info
#define Next(P) (P)->Next
#define Info(P) (P)->Info

/* Prototype manajemen memori */
void Alokasi (address *P, infotype X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void Dealokasi (address P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */

/* ********* PROTOTYPE REPRESENTASI LOJIK StackPlayer ***************/
boolean IsEmpty (StackPlayer S);
/* Mengirim true jika StackPlayer kosong: TOP(S) = Nil */
void CreateEmpty (StackPlayer * S);
/* I.S. sembarang */
/* F.S. Membuat sebuah StackPlayer S yang kosong */
void Push (StackPlayer * S, infotype X);
/* Menambahkan X sebagai elemen StackPlayer S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TOP yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
void Pop (StackPlayer * S, infotype * X);
/* Menghapus X dari StackPlayer S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, */
/*      elemen TOP yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */

#endif
