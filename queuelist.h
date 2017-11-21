/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#ifndef _QUEUELIST_H
#define _QUEUELIST_H
#include "boolean.h"
#include <stdlib.h>

/* Konstanta */
#define Nil NULL

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueue * addressqueue;
typedef struct tElmtQueue {
	int Info;
	addressqueue Next;
} ElmtQueue;

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct {
	addressqueue HEAD;  /* alamat penghapusan */
	addressqueue TAIL;  /* alamat penambahan */
} Queue;

/* Selektor */
#define HeadQueue(Q) (Q).HEAD
#define TailQueue(Q) (Q).TAIL
#define InfoHeadQueue(Q) (Q).HEAD->Info
#define InfoTailQueue(Q) (Q).TAIL->Info
#define NextQueue(P) (P)->Next
#define InfoQueue(P) (P)->Info

/* Prototype manajemen memori */
void AlokasiQueue (addressqueue *P, int X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void DealokasiQueue (addressqueue P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
boolean IsEmptyQueue (Queue Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
int NbElmtQueue(Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
void CreateEmptyQueue(Queue * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void AddQueue (Queue * Q, int X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void DelQueue(Queue * Q, int * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */

#endif
