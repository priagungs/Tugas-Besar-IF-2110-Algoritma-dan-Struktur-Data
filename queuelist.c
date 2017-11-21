#include "queuelist.h"
#include <stdlib.h>

/* Prototype manajemen memori */
void AlokasiQueue (addressqueue *P, int X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka InfoQueue(P)=X dan
        NextQueue(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  *P = (ElmtQueue *)malloc(sizeof(ElmtQueue));
  if(*P != Nil){
    NextQueue(*P) = Nil;
    InfoQueue(*P) = X;
  }
}

void DealokasiQueue (addressqueue  P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  free(P);
}

boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: HeadQueue(Q)=Nil and TailQueue(Q)=Nil */
{
  return HeadQueue(Q) == Nil && TailQueue(Q) == Nil;
}

int NbElmtQueue(Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong */
/*** Kreator ***/
{
  int count=0;
  if(!IsEmptyQueue(Q)){
    count++;
    addressqueue P = HeadQueue(Q);
    while(P != TailQueue(Q)){
      count++;
      P = NextQueue(P);
    }
  }
  return count;
}

void CreateEmptyQueue(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
{
  HeadQueue(*Q) = Nil;
  TailQueue(*Q) = Nil;
}

void AddQueue (Queue * Q, int X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TailQueue dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TailQueue, TailQueue "maju" */
{
  addressqueue P;
  AlokasiQueue(&P, X);
  if(P!=Nil){
    if(!IsEmptyQueue(*Q)){
      NextQueue(TailQueue(*Q)) = P;
      TailQueue(*Q) = P;
    }
    else{
      HeadQueue(*Q) = P;
      TailQueue(*Q) = P;
    }
  }
}

void DelQueue(Queue * Q, int * X)
/* Proses: Menghapus X pada bagian HeadQueue dari Q dan mendealokasi
   elemen HeadQueue */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HeadQueue pd I.S., HeadQueue "mundur" */
{
  *X = InfoHeadQueue(*Q);
  if(HeadQueue(*Q) == TailQueue(*Q)){
    CreateEmptyQueue(Q);
  }
  else{
    HeadQueue(*Q) = NextQueue(HeadQueue(*Q));
  }
}
