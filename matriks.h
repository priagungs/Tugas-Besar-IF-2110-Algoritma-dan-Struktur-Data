
#ifndef PETA_H
#define PETA_H


#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "matriks.h"
#include "pcolor.h"
#include "listvillage.h"
#include "player.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 0
#define BrsMax 100
#define KolMin 0
#define KolMax 100

typedef int indeks; /* indeks baris, kolom */


typedef struct {
	char bangunanPetak; //Ada (T)ower, (C)astle, (V)illage, dan (N)ormal
	int kepemilikanBangunanPetak; //Ada (0)Normal, (1)Player1, dan (2)Player2
	char unitPetak; //Ada (K)ing, (A)rcher, (S)wordsman, (W)hite Mage, dan (N)othing
	int kepemilikanUnitPetak; //Ada (0)Normal, (1)Player1, dan (2)Player2
} PETAK;


typedef struct {
	PETAK Mem[BrsMax+1][KolMax+1];
  int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} PETA;
/* Indeks matriks of petak yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks of petak yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor *** */
#define NBrsEff(P) (P).NBrsEff
#define NKolEff(P) (P).NKolEff
#define BP(P,i,j) (P).Mem[i][j].bangunanPetak
#define KBP(P,i,j) (P).Mem[i][j].kepemilikanBangunanPetak
#define UP(P,i,j) (P).Mem[i][j].unitPetak
#define KUP(P,i,j) (P).Mem[i][j].kepemilikanUnitPetak

void InitiateTowerCastle (PETA *M);
/* Memposisikan tower dan castle setiap pemain */

void MakePETA (int NB, int NK, PETA *P);

void UpdatePETA(PETA *P, Player P1, Player P2, ListVil LV, Unit CurrentUnit );

void PrintPETA(PETA P);

void RandomVillage (ListVil *L, int NVillage, int x, int y,PETA *P);

boolean NoObstacle(Unit CurrentUnit, POINT P, PETA M);

#endif
