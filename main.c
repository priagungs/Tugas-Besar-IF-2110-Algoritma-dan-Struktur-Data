/*#include "jam.h"*/
/*#include "stackofplayer.h"*/
#include "listvillage.h"
#include "matriks.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NB,NK;
char Str[15];
Player P1;
Player P2;
Player *CurrentPlayer;
ListVil Villages;
int turn=1;

PETA P;

//Command: gcc -Wall main.c player.c matriks.c listofunit.c unit.c listvillage.c village.c pcolor.c point.c -o hasil

void PrintPlayerStatus(Player P,Unit U){
	printf("Player %d's Turn\n",Warna(P));
	printf("Cash: %dG | Income: %dG | Upkeep: %dG\n", Gold(P),Income(P),Upkeep(P));
	printf("Unit: %s (%d,%d) | Health %d/%d | Movement Point: %d | Can Attack: ", 
		Jenis_Unit(U),
		Absis(Lokasi_Unit(U)),
		Ordinat(Lokasi_Unit(U)),
		Health(U),
		Max_Health(U),
		Movement_Point(U));

	if(Kesempatan_Serangan(U)){
		printf("Yes\n");
	}else{
		printf("No\n");
	}
}


int main(){
	Make_Player(&P1,1);
	Make_Player(&P2,2);
	CreateEmptyVil(&Villages);
	CurrentPlayer = &P1;

	printf("JUDUL\n");

	printf("Masukkan input besar peta (BARIS,KOLOM)\n");
	scanf("%d %d", &NB,&NK);
	
	MakePETA(NB,NK,&P);
	Unit Now = CreateUnit("King",MakePOINT(NB-2,KolMin+1));
	InsUnitFirst(&UnitList(P1),Now);
	Now = CreateUnit("King",MakePOINT(BrsMin+1,NK-2));
	InsUnitFirst(&UnitList(P2),Now);

	RandomVillage(&Villages,10,NB,NK,&P);
	PrintListVillage(Villages);
	
	UpdatePETA(&P,P1,P2,Villages);
	PrintPETA(P);
	do{
		PrintPlayerStatus(*CurrentPlayer,Now);
		printf("Your Input: ");
		scanf("%s",Str);
		
		if(!strcmp(Str,"MOVE")){
			
		}else if(!strcmp(Str,"UNDO")){
			
		}else if(!strcmp(Str,"CHANGE_UNIT")){

		}else if(!strcmp(Str,"NEXT_UNIT")){

		}else if(!strcmp(Str,"RECRUIT")){
			printf("Masukan jenis unit yang ingin di rekrut.\n");
			char jenisUnitRekrut[200];

			fgets(jenisUnitRekrut, 200, stdin);
			char *pos;
			fgets(jenisUnitRekrut, 200, stdin);
			if ((pos=strchr(jenisUnitRekrut, '\n')) != NULL)*pos = '\0';

			while ( (strcmp(jenisUnitRekrut,"King")) && (strcmp(jenisUnitRekrut,"Archer")) && (strcmp(jenisUnitRekrut,"Swordsman")) && (strcmp(jenisUnitRekrut,"White Mage"))  )
			{
				printf("Masukan jenis unit anda masukan salah.\n");
				printf("Masukan kembali jenis unit yang ingin di rekrut.\n");
				fgets(jenisUnitRekrut, 200, stdin);
				if ((pos=strchr(jenisUnitRekrut, '\n')) != NULL)*pos = '\0';
			} 

			boolean bisaRekrutUnit = false;

			POINT lokasiUnitDirekrut; // tergantung player 1/2 

			if (Warna(*CurrentPlayer) == 1 )
			{
				if (UP(P,NBrsEff(P)-2,KolMin+1)=='K')
				{

					if(UP(P,NBrsEff(P)-3,KolMin+1)=='N'){
						lokasiUnitDirekrut = MakePOINT(NBrsEff(P)-3,KolMin+1);
						bisaRekrutUnit = true;
					} else {

						if(UP(P,NBrsEff(P)-2,KolMin)=='N'){
							lokasiUnitDirekrut = MakePOINT(NBrsEff(P)-2,KolMin);
							bisaRekrutUnit = true;
						} else {

							if(UP(P,NBrsEff(P)-1,KolMin+1)=='N'){
								lokasiUnitDirekrut = MakePOINT(NBrsEff(P)-1,KolMin+1);
								bisaRekrutUnit = true;
							} else {

								if(UP(P,NBrsEff(P)-2,KolMin+2)=='N'){
									lokasiUnitDirekrut = MakePOINT(NBrsEff(P)-2,KolMin+2);
									bisaRekrutUnit = true;
								} else {
									printf("Semua castle anda penuh!\n");
									
								}	
							}
							
						}
					}

				} else {
					printf("King anda harus berada di tower!\n");
				}
					
			} else {

				if (UP(P,BrsMin+1,NKolEff(P)-2)=='K')
				{

					if(UP(P,BrsMin,NKolEff(P)-2)=='N'){
						lokasiUnitDirekrut = MakePOINT(BrsMin,NKolEff(P)-2);
						bisaRekrutUnit = true;
					} else {

						if(UP(P,BrsMin+1,NKolEff(P)-3)=='N'){
							lokasiUnitDirekrut = MakePOINT(BrsMin+1,NKolEff(P)-3);
							bisaRekrutUnit = true;
						} else {

							if(UP(P,BrsMin+2,NKolEff(P)-2)=='N'){
								lokasiUnitDirekrut = MakePOINT(BrsMin+2,NKolEff(P)-2);
								bisaRekrutUnit = true;
							} else {

								if(UP(P,BrsMin+1,NKolEff(P)-1)=='N'){
									lokasiUnitDirekrut = MakePOINT(BrsMin+1,NKolEff(P)-1);
									bisaRekrutUnit = true;
								} else {
									printf("Semua castle anda penuh!\n");
									
								}	
							}
							
						}
					}

				} else {
					printf("King anda harus berada di tower!\n");
				}
			}

			if (bisaRekrutUnit){
				Unit RekrutUnit = CreateUnit(jenisUnitRekrut,lokasiUnitDirekrut);
				InsUnitLast(&UnitList(*CurrentPlayer),RekrutUnit);
				printf("Unit berhasil direkrut!\n");
			} else {
				printf("Unit tidak berhasil direkrut.\n");
			}
				
		}else if(!strcmp(Str,"ATTACK")){
			
		}else if(!strcmp(Str,"MAP")){
			UpdatePETA(&P,P1,P2,Villages);
			PrintPETA(P);
			
		}else if(!strcmp(Str,"INFO")){

			
		}else if(!strcmp(Str,"END_TURN")){
			if(turn%2){
				CurrentPlayer = &P2;
				turn++;
			} else {
				CurrentPlayer = &P1;
				turn++;
			}
		}else if(!strcmp(Str,"SAVE")){
			
		}else{
			if(strcmp(Str,"EXIT")){
				printf("No command found!\n");
			}
		}

	}while(strcmp(Str,"EXIT"));
}