/* File : queue.h */
/* Definisi ADT Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi III dengan circular buffer */

#include "boolean.h"
#include "queue.h"
#include <math.h>
#include <stdlib.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{		
	 return ((HeadQueue(Q)==0) && (TailQueue(Q)==0)); 
}

boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
	return ((abs(HeadQueue(Q) - TailQueue(Q)) == 1) || (HeadQueue(Q) == 1 && TailQueue(Q) == MaxElQueue(Q)));
}

int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
	if(IsEmptyQueue(Q)) return 0;
	int panjang = TailQueue(Q) - HeadQueue(Q);
	panjang += (panjang < 0 )? (MaxElQueue(Q)+1) : 1;
	return panjang;
}

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
	(*Q).T = (int *) malloc ((Max+1) * sizeof(int)); 	
	if ((*Q).T != NULL) {       
		MaxElQueue(*Q) = Max;        
		HeadQueue(*Q) = 0;        
		TailQueue(*Q) = 0; 
	}else /* alokasi gagal */
		MaxElQueue(*Q) = 0; 
}

/* *** Destruktor *** */
void DeAlokasiQueue(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
	MaxElQueue(*Q) = 0;
	free((*Q).T); 
}

/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, int X)
/* Proses: Menambahkan X pada Q dengan aturan FIFO */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer */
{
	TailQueue(*Q) ++;
	if(HeadQueue(*Q) == 0) HeadQueue(*Q) = 1;
	if(TailQueue(*Q) > MaxElQueue(*Q)) TailQueue(*Q) -= MaxElQueue(*Q);
	InfoTailQueue(*Q) = X;
}

void DelQueue (Queue * Q, int * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = 0ai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
	*X = InfoHeadQueue(*Q);
	if(TailQueue(*Q) == HeadQueue(*Q)){
		TailQueue(*Q) = 0;
		HeadQueue(*Q) = 0;
	}
	else{
		HeadQueue(*Q) ++;
		if(HeadQueue(*Q) > MaxElQueue(*Q)) HeadQueue(*Q) -= MaxElQueue(*Q);
	}
}