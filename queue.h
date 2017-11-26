/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#ifndef queue_H
#define queue_H

#include "boolean.h"

/* Konstanta untuk mendefinisikan addressqueue tak terdefinisi */

/* Definisi elemen dan addressqueue */
typedef int addressqueue;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { int * T;   /* tabel penyimpan elemen */
                 addressqueue HEAD;  /* alamat penghapusan */
                 addressqueue TAIL;  /* alamat penambahan */
                 int MaxEl;     /* Max elemen qxueue */
               } Queue;
/* Definisi Queue kosong: HEAD=0; TAIL=0. */
/* Catatan implementasi: T[0] tidak pernah dipakai */

/* ********* AKSES (Selektor) ********* */
/* Jika Q adalah Queue, maka akses elemen : */
#define HeadQueue(Q) (Q).HEAD
#define TailQueue(Q) (Q).TAIL
#define InfoHeadQueue(Q) (Q).T[(Q).HEAD]
#define InfoTailQueue(Q) (Q).T[(Q).TAIL]
#define MaxElQueue(Q) (Q).MaxEl

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueue (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmtQueue (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasiQueue(Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, int X);
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
void DelQueue (Queue * Q, int * X);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = 0ai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

#endif