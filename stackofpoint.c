#include "stackofpoint.h"
#include <stdlib.h>

/* Prototype manajemen memori */
void AlokasiPointStack (addressU *P, infotypeU X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  *P = (ElmtStackPoint *)malloc(sizeof(ElmtStackPoint));
  if(*P != Nil){
    Next(*P) = Nil;
    Info(*P) = X;
  }
}

void DealokasiPointStack (addressU P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK StackPoint ***************/
boolean IsEmptyPointStack (StackPoint S)
/* Mengirim true jika StackPoint kosong: TopPoint(S) = Nil */
{
  return TopPoint(S) == Nil;
}

void CreateEmptyPointStack (StackPoint * S)
/* I.S. sembarang */
/* F.S. Membuat sebuah StackPoint S yang kosong */
{
  TopPoint(*S) = Nil;
}

void PushPoint (StackPoint * S, infotypeU X)
/* Menambahkan X sebagai elemen StackPoint S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TopPoint yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
  addressU P;
  AlokasiPointStack(&P, X);
  if(P != Nil){
    Next(P) = TopPoint(*S);
    TopPoint(*S) = P;
  }
}

void PopPoint (StackPoint * S, infotypeU * X)
/* Menghapus X dari StackPoint S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TopPoint yang lama, */
/*      elemen TopPoint yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
  *X = InfoTopPoint(*S);
  addressU P = TopPoint(*S);
  TopPoint(*S) = Next(TopPoint(*S));
  DealokasiPointStack(P);
}
