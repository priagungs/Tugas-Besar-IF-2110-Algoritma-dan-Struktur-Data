#include "village.h"
#include "boolean.h"
#include "point.h"
#include <stdio.h>

boolean IsVillageSame( Village V1, Village V2){
// menentukan apakah village ada di lokasi yang sama
	return (PosX(V1) == PosX(V2)) && (PosY(V1) == PosY(V2));
}

void CopyVillage( Village V1, Village V2){
	V2.indeks = V1.indeks;
}


void MakeVillage( Village *V, int x, int y, int money)
// membuat village dengan koordunat x,y , dan pendapatan = money;
{
	PosX(*V) = x;
	PosY(*V) = y;
	IncomeVil(*V) = money;
}

void PrintVillage( Village V)
{
	printf("Koordinat : (%d,%d)\n",PosX(V),PosY(V));
	printf("Income : %d\n",IncomeVil(V) );
}
