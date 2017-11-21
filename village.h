/* File: village.h */
/* Tanggal: 11 November 2017 */
/* made by : rwk03 */


#ifndef _VILLAGE_h
#define _VILLAGE_h

#include "boolean.h"
#include "point.h"

typedef struct
{
	POINT indeks;
	int income; // nilai pendapatan desa
} Village;

#define PosX(V) Absis((V).indeks)
#define PosY(V) Ordinat((V).indeks)
#define	IncomeVil(V) (V).income

boolean IsVillageSame( Village V1, Village V2);
void CopyVillage( Village V1, Village V2);
void MakeVillage( Village *V, int x, int y, int money);
void PrintVillage( Village V);

#endif
