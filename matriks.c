#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "matriks.h"
#include "pcolor.h"
#include "listvillage.h"
#include "player.h"
#include <time.h>


void InitiateTowerCastle (PETA *M){

/* Menginisiasi pemilik petak */
	/* Untuk Player 1 */
    KBP(*M,KolMin,NBrsEff(*M)-2) = 1;
    KBP(*M,KolMin+1,NBrsEff(*M)-3) = 1;
    KBP(*M,KolMin+1,NBrsEff(*M)-2) = 1;
    KBP(*M,KolMin+1,NBrsEff(*M)-1) = 1;
    KBP(*M,KolMin+2,NBrsEff(*M)-2) = 1;
    /* Untuk Player 2 */
    KBP(*M,NKolEff(*M)-3,BrsMin+1) = 2;
   	KBP(*M,NKolEff(*M)-2,BrsMin) = 2;
    KBP(*M,NKolEff(*M)-2,BrsMin+1) = 2;
    KBP(*M,NKolEff(*M)-2,BrsMin+2) = 2;
    KBP(*M,NKolEff(*M)-1,BrsMin+1) = 2;

/* Memposisikan tower dan castle setiap pemain */

    /* Untuk Player 1 */
    BP(*M,KolMin,NBrsEff(*M)-2) = 'C';
    BP(*M,KolMin+1,NBrsEff(*M)-3) = 'C';
    BP(*M,KolMin+1,NBrsEff(*M)-2) = 'T';
    BP(*M,KolMin+1,NBrsEff(*M)-1) = 'C';
    BP(*M,KolMin+2,NBrsEff(*M)-2) = 'C';

    /* Untuk Player 2 */
    BP(*M,NKolEff(*M)-3,BrsMin+1) = 'C';
   	BP(*M,NKolEff(*M)-2,BrsMin) = 'C';
    BP(*M,NKolEff(*M)-2,BrsMin+1) = 'T';
    BP(*M,NKolEff(*M)-2,BrsMin+2) = 'C';
    BP(*M,NKolEff(*M)-1,BrsMin+1) = 'C';
}

/* *** Konstruktor membentuk PETA *** */
void MakePETA(int NK, int NB, PETA *P){
	NBrsEff(*P) = NB;
	NKolEff(*P) = NK;

	//Setting isi semua peta ke defaultnya, yaitu:
	// char jenisPetak = (N)ormal
	// int kepemilikanPetak = (0)Normal
	// char unitPetak = (N)othing

	for (int j = 0; j < NBrsEff(*P); ++j)
	{
		for (int i = 0; i < NKolEff(*P); ++i)
		{
			BP(*P,i,j) = 'N';
			KBP(*P,i,j) = 0;
			UP(*P,i,j) = 'N';
			KUP(*P,i,j) = 0;
		}
	}
	InitiateTowerCastle(P);
}


void UpdatePETA(PETA *P, Player P1, Player P2, ListVil LV, Unit CurrentUnit ){

	//Set peta jadi kosong lagi
	for (int i = 0; i < NBrsEff(*P); ++i)
	{
		for (int j = 0; j < NKolEff(*P); ++j)
		{
			BP(*P,i,j) = 'N';
			KBP(*P,i,j) = 0;
			UP(*P,i,j) = 'N';
			KUP(*P,i,j) = 0;
		}
	}
	InitiateTowerCastle(P);

	//Memperbaharui Letak Unit Player 1
	ListUnit LU1 = UnitList(P1);
	addressUnit AlamatU;
  	if (!IsEmptyUnit(LU1)) {
    	AlamatU = FirstUnit(LU1);
    	int i = InfoUnit(AlamatU).Lokasi.X;
    	int j = InfoUnit(AlamatU).Lokasi.Y;
    	char* temp1 = Jenis_Unit(InfoUnit(AlamatU));
      	UP(*P,i,j) = temp1[0];
    	KUP(*P,i,j) = 1;

    	AlamatU = NextUnit(AlamatU);
    	while (AlamatU != FirstUnit(LU1)) {
      		int i = InfoUnit(AlamatU).Lokasi.X;
      		int j = InfoUnit(AlamatU).Lokasi.Y;
      		temp1 = Jenis_Unit(InfoUnit(AlamatU));
      		UP(*P,i,j) = temp1[0];
      		KUP(*P,i,j) = 1;
      		AlamatU = NextUnit(AlamatU);
    	}
  	}

  	//Memperbahar Letak Unit Player 2
  	ListUnit LU = UnitList(P2);
	addressUnit AlamatU2;
  	if (!IsEmptyUnit(LU)) {
    	AlamatU2 = FirstUnit(LU);
    	int i = InfoUnit(AlamatU2).Lokasi.X;
    	int j = InfoUnit(AlamatU2).Lokasi.Y;
    	char* temp2 = Jenis_Unit(InfoUnit(AlamatU2));
    	UP(*P,i,j) = temp2[0];
    	KUP(*P,i,j) = 2;

    	AlamatU2 = NextUnit(AlamatU2);
    	while (AlamatU2 != FirstUnit(LU)) {
      		int i = InfoUnit(AlamatU2).Lokasi.X;
      		int j = InfoUnit(AlamatU2).Lokasi.Y;
      		temp2 = Jenis_Unit(InfoUnit(AlamatU2));
    		UP(*P,i,j) = temp2[0];
      		KUP(*P,i,j) = 2;
      		AlamatU2 = NextUnit(AlamatU2);
    	}
  	}


  	//Membuat Semua Village
	addressVillage AlamatV;
  	if (!IsEmptyVil(LV)) {
    	AlamatV = FirstVillage(LV);
    	int i = PosX(InfoVillage(AlamatV));
    	int j =	PosY(InfoVillage(AlamatV));
    	BP(*P,i,j) = 'V';
    	KBP(*P,i,j) = 0;

    	AlamatV = NextVillage(AlamatV);
    	while (AlamatV != FirstVillage(LV)) {
      		int i = PosX(InfoVillage(AlamatV));
      		int j =	PosY(InfoVillage(AlamatV));
      		BP(*P,i,j) = 'V';
      		KBP(*P,i,j) = 0;
      		AlamatV = NextVillage(AlamatV);
    	}
  	}

  	//Memperbaharui Kepemilikannya berdasarkan player 1
  	ListVil LV1 = VillageList(P1);
  	addressVillage AlamatV1;
  	if (!IsEmptyVil(LV1)) {
    	AlamatV1 = FirstVillage(LV1);
    	int i = PosX(InfoVillage(AlamatV1));
    	int j =	PosY(InfoVillage(AlamatV1));
    	BP(*P,i,j) = 'V';
    	KBP(*P,i,j) = 1;

    	AlamatV1 = NextVillage(AlamatV1);
    	while (AlamatV1 != FirstVillage(LV1)) {
      		int i = PosX(InfoVillage(AlamatV1));
      		int j =	PosY(InfoVillage(AlamatV1));
      		BP(*P,i,j) = 'V';
      		KBP(*P,i,j) = 1;
      		AlamatV1 = NextVillage(AlamatV1);
    	}
  	}

  	//Memperbaharui Kepemilikannya berdasarkan player 2
  	ListVil LV2 = VillageList(P2);
  	addressVillage AlamatV2;
  	if (!IsEmptyVil(LV2)) {
    	AlamatV2 = FirstVillage(LV2);
    	int i = PosX(InfoVillage(AlamatV2));
    	int j =	PosY(InfoVillage(AlamatV2));
    	BP(*P,i,j) = 'V';
    	KBP(*P,i,j) = 2;

    	AlamatV2 = NextVillage(AlamatV2);
    	while (AlamatV2 != FirstVillage(LV2)) {
      		int i = PosX(InfoVillage(AlamatV2));
      		int j =	PosY(InfoVillage(AlamatV2));
      		BP(*P,i,j) = 'V';
      		KBP(*P,i,j) = 2;
      		AlamatV2 = NextVillage(AlamatV2);
    	}
  	}

  	//Update warna current unit
  	KUP(*P,Absis(Lokasi_Unit(CurrentUnit)), Ordinat(Lokasi_Unit(CurrentUnit))) = 3;
}

// Print PETA //
void PrintPETA(PETA P){


	// Print indeks Peta
	printf("  ");
	for (int i = 0; i < NKolEff(P); ++i)
	{
		if(i<10){
			printf("  %d ", i);
		} else {
			printf(" %d ", i);
		}

	}
	printf(" \n");

	// Print peta perbaris

	for (int i = 0; i < NBrsEff(P); ++i)
	{
		//Print Garis Penutup Atas
		printf("  ");
		for (int j = 0; j < NKolEff(P); ++j)
		{
			printf("****");
		}
		printf("*\n");

		//Cek bangunanPetak
		printf("  ");
		for (int j = 0; j < NKolEff(P); ++j)
		{
			printf("* ");
			if(KBP(P,j,i) == 0){

				if(BP(P,j,i) == 'N'){
					printf(" ");
				} else if (BP(P,j,i) == 'T'){
					printf("T");
				} else if (BP(P,j,i) == 'C'){
					printf("C");
				} else if (BP(P,j,i) == 'V'){
					printf("V");

				}

			} else if (KBP(P,j,i) == 1){

				if(BP(P,j,i) == 'N'){
					printf(" ");
				} else if (BP(P,j,i) == 'T'){
					print_green('T');
				} else if (BP(P,j,i) == 'C'){
					print_green('C');
				} else if (BP(P,j,i) == 'V'){
					print_green('V');
				}

			} else {

				if(BP(P,j,i) == 'N'){
					printf(" ");
				} else if (BP(P,j,i) == 'T'){
					print_red('T');
				} else if (BP(P,j,i) == 'C'){
					print_red('C');
				} else if (BP(P,j,i) == 'V'){
					print_red('V');
				}


			}
			printf(" ");

		}
		printf("*\n");

		//Cek unitPetak
		if(i>=10){
			printf("%d", i);
		} else {
			printf(" %d", i);
		}

		for (int j = 0; j < NKolEff(P); ++j)
		{
			printf("* ");
			if(KUP(P,j,i) == 0){

				if (UP(P,j,i) == 'K') {
					printf("K");
				}else if (UP(P,j,i) == 'A'){
					printf("A");
				}else if (UP(P,j,i) == 'S'){
					printf("S");
				}else if (UP(P,j,i) == 'W'){
					printf("W");
				}else if(UP(P,j,i) == '#'){
		          	printf("#");
		        }else {
					printf(" ");
				}


			} else if (KUP(P,j,i) == 1){

				if (UP(P,j,i) == 'K') {
					print_green('K');
				}else if (UP(P,j,i) == 'A'){
					print_green('A');
				}else if (UP(P,j,i) == 'S'){
					print_green('S');
				}else if (UP(P,j,i) == 'W'){
					print_green('W');
				}else if(UP(P,j,i) == '#'){
		          	printf("#");
		        }else {
					print_green(' ');
				}

			} else if (KUP(P,j,i) == 2){

				if (UP(P,j,i) == 'K') {
					print_red('K');
				}else if (UP(P,j,i) == 'A'){
					print_red('A');
				}else if (UP(P,j,i) == 'S'){
					print_red('S');
				}else if (UP(P,j,i) == 'W'){
					print_red('W');
				}else if(UP(P,j,i) == '#'){
		          	printf("#");
		        }else {
					print_red(' ');
				}

				

			} else if (KUP(P,j,i) == 3) {

				if (UP(P,j,i) == 'K') {
					print_magenta('K');
				}else if (UP(P,j,i) == 'A'){
					print_magenta('A');
				}else if (UP(P,j,i) == 'S'){
					print_magenta('S');
				}else if (UP(P,j,i) == 'W'){
					print_magenta('W');
				}else if(UP(P,j,i) == '#'){
		          	printf("#");
		        }else {
					print_magenta(' ');
				}

			}
			printf(" ");
		}
		printf("*\n");

		// Print baris kosong terakhir
		printf("  ");
		for (int j = 0; j < NKolEff(P); ++j)
		{
			printf("*   ");

		}
		printf("*\n");
	}

	//Print garis penutup
	printf("  ");
	for (int j = 0; j < NKolEff(P); ++j)
	{
		printf("****");
	}
	printf("*\n");

}

void RandomVillage (ListVil *L, int NVillage, int x, int y, PETA *P)
{
	Village Vil;
	srand(time(NULL));   // should only be called once
	int idx, i, j, uang;
	CreateEmptyVil(L);
	for(idx = 1; idx <= NVillage ; idx++){
		i = rand()%x;
		j = rand()%y;
		while((*P).Mem[i][j].bangunanPetak == 'V' || (*P).Mem[i][j].bangunanPetak == 'C' || (*P).Mem[i][j].bangunanPetak == 'T'){
			i = rand()%x;
			j = rand()%y;
		}
		(*P).Mem[i][j].bangunanPetak='V';
		uang = rand() % 50;
		MakeVillage(&Vil,i,j,uang);
		InsVFirstVil (L, Vil);
	}
}

boolean NoObstacle(Unit U, POINT P, PETA M){
	//horizontal, vertical, and diagonal Checking
  boolean noObstacle = true;

  if(KUP(M,Absis(P),Ordinat(P)) == KUP(M,Absis(Lokasi_Unit(U)), Ordinat(Lokasi_Unit(U)))){
    return false;
  }

  // horizontal
  if(Ordinat(P) == Ordinat(Lokasi_Unit(U))){
    if(Absis(P) > Absis(Lokasi_Unit(U))){
      for(int i=Absis(Lokasi_Unit(U)); i <= Absis(P); i++){ //row checking
        if(KUP(M, i, Ordinat(P)) != KUP(M, Absis(Lokasi_Unit(U)), Ordinat(Lokasi_Unit(U))) && KUP(M,i,Ordinat(P)) != 0){
          return false;
        }
      }
    }
    else if(Absis(P) < Absis(Lokasi_Unit(U))){
      for(int i=Absis(Lokasi_Unit(U)); i >= Absis(P); i--){ //row checking
        if(KUP(M, i, Ordinat(P)) != KUP(M, Absis(Lokasi_Unit(U)), Ordinat(Lokasi_Unit(U))) && KUP(M,i,Ordinat(P)) != 0){
          return false;
        }
      }
    }
  }
  // vertical
  else if(Absis(P) == Absis(Lokasi_Unit(U))){
    if(Ordinat(P) > Ordinat(Lokasi_Unit(U))){
      for(int i=Ordinat(Lokasi_Unit(U)); i <= Ordinat(P); i++){ //row checking
        if(KUP(M, Absis(P), i) != KUP(M, Absis(Lokasi_Unit(U)), Ordinat(Lokasi_Unit(U))) && KUP(M,Absis(P),i) != 0){
          return false;
        }
      }
    }
    else if(Ordinat(P) < Ordinat(Lokasi_Unit(U))){
      for(int i=Ordinat(Lokasi_Unit(U)); i >= Ordinat(P); i--){ //row checking
        if(KUP(M, Absis(P), i) != KUP(M, Absis(Lokasi_Unit(U)), Ordinat(Lokasi_Unit(U))) && KUP(M,Absis(P),i) != 0){
          return false;
        }
      }
    }
  }
  return noObstacle;
}
