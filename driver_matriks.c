#include "matriks.h"

//Command: gcc -Wall driver_matriks.c matriks.c player.c listvillage.c village.c pcolor.c listofunit.c unit.c point.c -o DriverMatriks

int NB,NK,IndeksUnit;
char Str[15];
Player P1;
Player P2;
Player *CurrentPlayer;
ListVil Villages;
Unit Now;


PETA P;

void clrscr()
{
    system("@cls||clear");
}

int main(){
	clrscr();

/* 		========= Create New game =========		*/
	Make_Player(&P1,1);
	Make_Player(&P2,2);
	CreateEmptyVil(&Villages);

	printf("Masukkan input besar peta (KOLOM,BARIS)\n");
	scanf("%d %d", &NK,&NB);
	if(NK < 8 && NB <8){
		printf("Map are too little!\n");
		printf("Masukkan input besar peta (KOLOM,BARIS)\n");
		scanf("%d %d", &NK,&NB);
	}

	Now = CreateUnit("King",MakePOINT(NK-2,BrsMin+1));
	InsUnitFirst(&UnitList(P2),Now);

	Now = CreateUnit("King",MakePOINT(KolMin+1,NB-2));
	InsUnitFirst(&UnitList(P1),Now);
	MakePETA(NK,NB,&P);
	UpdatePETA(&P,P1,P2,Villages,Now);
	RandomVillage(&Villages,10,NK,NB,&P);


	CurrentPlayer = &P1;
	IndeksUnit = 2;

	clrscr();
	UpdatePETA(&P,P1,P2,Villages,Now);
	PrintPETA(P);

}