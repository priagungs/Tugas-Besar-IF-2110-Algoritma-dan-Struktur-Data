#include "stackofplayer.h"
#include <stdlib.h>

/* Prototype manajemen memori */
void Alokasi (address *P, infotype X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
  *P = (ElmtStackPlayer *)malloc(sizeof(ElmtStackPlayer));
  if(*P != Nil){
    Next(*P) = Nil;
    Info(*P) = X;
  }
}

void Dealokasi (address P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
  free(P);
}

/* ********* PROTOTYPE REPRESENTASI LOJIK StackPlayer ***************/
boolean IsEmpty (StackPlayer S)
/* Mengirim true jika StackPlayer kosong: TopPlayer(S) = Nil */
{
  return TopPlayer(S) == Nil;
}

void CreateEmpty (StackPlayer * S)
/* I.S. sembarang */
/* F.S. Membuat sebuah StackPlayer S yang kosong */
{
  TopPlayer(*S) = Nil;
}

void Push (StackPlayer * S, infotype X)
/* Menambahkan X sebagai elemen StackPlayer S */
/* I.S. S mungkin kosong, X terdefinisi */
/* F.S. X menjadi TopPlayer yang baru jika alokasi X berhasil, */
/*      jika tidak, S tetap */
/* Pada dasarnya adalah operasi Insert First pada list linier */
{
  address P;
  Alokasi(&P, X);
  if(P != Nil){
    Next(P) = TopPlayer(*S);
    TopPlayer(*S) = P;
  }
}

void Pop (StackPlayer * S, infotype * X)
/* Menghapus X dari StackPlayer S. */
/* I.S. S tidak mungkin kosong */
/* F.S. X adalah nilai elemen TopPlayer yang lama, */
/*      elemen TopPlayer yang lama didealokasi */
/* Pada dasarnya adalah operasi Delete First pada list linier */
{
  *X = InfoTopPlayer(*S);
  address P = TopPlayer(*S);
  TopPlayer(*S) = Next(TopPlayer(*S));
  Dealokasi(P);
}
