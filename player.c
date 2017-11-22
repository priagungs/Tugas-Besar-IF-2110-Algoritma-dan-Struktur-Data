/*#include "jam.h"*/
#include "stackofplayer.h"
#include "listvillage.h"
#include "matriks.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int NB,NK,IndeksUnit;
char Str[15];
Player P1;
Player P2;
Player *CurrentPlayer;
ListVil Villages;
StackPlayer SP;
int turn=1;


PETA P;

//Command: gcc -Wall main.c player.c matriks.c listofunit.c unit.c listvillage.c village.c pcolor.c point.c -o hasil

void RekrutUnit(void);

void PrintPlayerStatus(Player P,Unit U);

void Move(PETA M, Unit* CurrentUnit);

Player Undo(StackPlayer SP);

void ClearStack(StackPlayer *SP);
void clrscr();

int main(){
	clrscr();
	Make_Player(&P1,1);
	Make_Player(&P2,2);
	CreateEmptyVil(&Villages);

	printf("JUDUL\n");
	printf("Masukkan input besar peta (KOLOM,BARIS)\n");
	scanf("%d %d", &NK,&NB);

	MakePETA(NK,NB,&P);
	
	Unit Now = CreateUnit("King",MakePOINT(NK-2,BrsMin+1));
	InsUnitFirst(&UnitList(P2),Now);

	Now = CreateUnit("King",MakePOINT(KolMin+1,NB-2));
	InsUnitFirst(&UnitList(P1),Now);

	RandomVillage(&Villages,10,NK,NB,&P);
	CurrentPlayer = &P1;
	
	UpdatePETA(&P,P1,P2,Villages);
	IndeksUnit = 1;
	do{
		//clrscr();
		PrintPETA(P);
		PrintPlayerStatus(*CurrentPlayer,Now);
		printf("Your Input: ");
		scanf("%s",Str);

		if(!strcmp(Str,"MOVE")){
			//pop current unit from list of unit
			Del_Unit(CurrentPlayer, Now);
			Push(&SP,*CurrentPlayer);
			Move(P, &Now);
			//push moved current unit to list of unit
			if(!strcmp(Jenis_Unit(Now),"King"))
				Add_Unit_First(CurrentPlayer, Now);
			else
				Add_Unit_Last(CurrentPlayer, Now);
			//PrintListUnit(UnitList(P1));	
			//PrintListUnit(UnitList(P2));	
			//update map
			UpdatePETA(&P,P1,P2,Villages);
		}else if(!strcmp(Str,"UNDO")){
			if(!IsEmpty(SP)){
				*CurrentPlayer = Undo(SP);
			}else{
				printf("You cannot undo!\n");
			}
		}else if(!strcmp(Str,"CHANGE_UNIT")){
			int nomor;
			printf("                                       ============= YOUR UNITS =============\n");
			PrintListUnit(UnitList(*CurrentPlayer));
			printf("Choose unit number : ");
			scanf("%d",&nomor);
			IndeksUnit = nomor+1;
			Now = SearchNomor(UnitList(*CurrentPlayer),nomor);
			printf("Your current unit is %s\n",Jenis_Unit(Now));
		
		}else if(!strcmp(Str,"NEXT_UNIT")){
			boolean ada = false;
			Next_Unit(*CurrentPlayer, &IndeksUnit, &Now, &ada);
			if(!ada){
				IndeksUnit++;
				PrintPlayerStatus(*CurrentPlayer, Now);
			}	
		}else if(!strcmp(Str,"RECRUIT")){
			ClearStack(&SP);
			RekrutUnit();
			UpdatePETA(&P,P1,P2,Villages);
		}else if(!strcmp(Str,"ATTACK")){
			ClearStack(&SP);

		}else if(!strcmp(Str,"MAP")){
			UpdatePETA(&P,P1,P2,Villages);
			PrintPETA(P);

		}else if(!strcmp(Str,"INFO")){


		}else if(!strcmp(Str,"END_TURN")){
			ClearStack(&SP);
			if(turn%2){
				CurrentPlayer = &P2;
				turn++;
			} else {
				CurrentPlayer = &P1;
				turn++;
			}
			IndeksUnit = 1;
			// DelUnitFirst(&UnitList(*CurrentPlayer), &Now);
		}else if(!strcmp(Str,"SAVE")){
			ClearStack(&SP);
		}else{
			if(strcmp(Str,"EXIT")){
				printf("No command found!\n");
			}
		}

	}while(strcmp(Str,"EXIT"));
	ClearStack(&SP);
}

void RekrutUnit(void){
	printf("Masukan jenis unit yang ingin di rekrut.\n");
	printf("1. Swordsman\n");
	printf("2. Archer\n");
	printf("3. White Mage\n");
	printf("Masukan pilihan(string):\n");

	char jenisUnitRekrut[200];

	fgets(jenisUnitRekrut, 200, stdin);
	char *pos;
	fgets(jenisUnitRekrut, 200, stdin);
	if ((pos=strchr(jenisUnitRekrut, '\n')) != NULL)*pos = '\0';

	while ((strcmp(jenisUnitRekrut,"Archer")) && (strcmp(jenisUnitRekrut,"Swordsman")) && (strcmp(jenisUnitRekrut,"White Mage"))  )
	{
		printf("Masukan jenis unit anda masukan salah.\n");
		printf("Masukan kembali jenis unit yang ingin di rekrut.\n");
		printf("1. Swordsman\n");
		printf("2. Archer\n");
		printf("3. White Mage\n");
		printf("Masukan pilihan(string):\n");
		fgets(jenisUnitRekrut, 200, stdin);
		if ((pos=strchr(jenisUnitRekrut, '\n')) != NULL)*pos = '\0';
	}

	boolean bisaRekrutUnit = false;

	POINT lokasiUnitDirekrut; // tergantung player 1/2

	if (Warna(*CurrentPlayer) == 1 )
	{
		if (UP(P,KolMin+1,NBrsEff(P)-2)=='K')
		{
			boolean castleDipilih = false;
			while(castleDipilih == false){
				printf("Pilih castle di mana unit akan direkrut!\n");
				printf("Pilihan:\n");
				printf("1. Castle Utara\n");
				printf("2. Castle Barat\n");
				printf("3. Castle Selatan\n");
				printf("4. Castle Timur\n");
				printf("Masukan angka castle (1-4):\n");
				int castleRekrut;
				scanf("%d", &castleRekrut);
				while(castleRekrut<1 || castleRekrut>4){
					printf("Masukan anda salah! Masukan angka castle kembali.\n");
					scanf("%d", &castleRekrut);
				}

				if((UP(P,KolMin+1,NBrsEff(P)-3)=='N') && castleRekrut==1 ){
					lokasiUnitDirekrut = MakePOINT(KolMin+1,NBrsEff(P)-3);
					bisaRekrutUnit = true;
					castleDipilih = true;
				} else {

					if((UP(P,KolMin,NBrsEff(P)-2)=='N')&& castleRekrut==2){
						lokasiUnitDirekrut = MakePOINT(KolMin,NBrsEff(P)-2);
						bisaRekrutUnit = true;
						castleDipilih = true;
					} else {

						if((UP(P,KolMin+1,NBrsEff(P)-1)=='N')&& castleRekrut==3){
							lokasiUnitDirekrut = MakePOINT(KolMin+1,NBrsEff(P)-1);
							bisaRekrutUnit = true;
							castleDipilih = true;
						} else {

							if((UP(P,KolMin+2,NBrsEff(P)-2)=='N')&& castleRekrut==4){
								lokasiUnitDirekrut = MakePOINT(KolMin+2,NBrsEff(P)-2);
								bisaRekrutUnit = true;
								castleDipilih = true;
							} else {
								printf("Semua castle anda penuh!\n");

							}
						}

					}
				}
			}


		} else {
			printf("King anda harus berada di tower!\n");
		}

	} else {

		if (UP(P,NKolEff(P)-2,BrsMin+1) =='K')
		{
			boolean castleDipilih = false;
			while(castleDipilih == false){
				printf("Pilih castle di mana unit akan direkrut!\n");
				printf("Pilihan:\n");
				printf("1. Castle Utara\n");
				printf("2. Castle Barat\n");
				printf("3. Castle Selatan\n");
				printf("4. Castle Timur\n");
				printf("Masukan angka castle (1-4):\n");
				int castleRekrut;
				scanf("%d", &castleRekrut);
				while(castleRekrut<1 || castleRekrut>4){
					printf("Masukan anda salah! Masukan angka castle kembali.\n");
					scanf("%d", &castleRekrut);
				}

				if((UP(P,NKolEff(P)-2,BrsMin)=='N') && castleRekrut==1 ){
					lokasiUnitDirekrut = MakePOINT(NKolEff(P)-2,BrsMin);
					bisaRekrutUnit = true;
					castleDipilih = true;
				} else {

					if((UP(P,NKolEff(P)-3,BrsMin+1)=='N')&& castleRekrut==2){
						lokasiUnitDirekrut = MakePOINT(NKolEff(P)-2,BrsMin+1);
						bisaRekrutUnit = true;
						castleDipilih = true;
					} else {

						if((UP(P,NKolEff(P)-3,BrsMin+2)=='N')&& castleRekrut==3){
							lokasiUnitDirekrut = MakePOINT(NKolEff(P)-3,BrsMin+2);
							bisaRekrutUnit = true;
							castleDipilih = true;
						} else {

							if((UP(P,NKolEff(P)-1,BrsMin+1)=='N')&& castleRekrut==4){
								lokasiUnitDirekrut = MakePOINT(NKolEff(P)-1,BrsMin+1);
								bisaRekrutUnit = true;
								castleDipilih = true;
							} else {
								printf("Castle anda penuh!\n");

							}
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
		if(!strcmp(jenisUnitRekrut,"King"))
			Add_Unit_First(CurrentPlayer,RekrutUnit);
		else
			Add_Unit_Last(CurrentPlayer,RekrutUnit);
		printf("Unit berhasil direkrut!\n");
		
	} else {
		printf("Unit tidak berhasil direkrut.\n");
	}
}

void Move(PETA M, Unit* CurrentUnit){
	int X,Y;

	// print peta dengan posisi dimana unit bisa berpindah
	for(int i=0; i<NBrsEff(M); i++){
		for(int j=0; j<NKolEff(M); j++){
			POINT temp = MakePOINT(i,j);
			if(CanUnitMoveTo(*CurrentUnit, temp) && NoObstacle(*CurrentUnit, temp, M) && Panjang(temp, Lokasi_Unit(*CurrentUnit)) != 0){
				UP(M,i,j) = '#';
			}
		}
	}
	PrintPETA(M);

	printf("Please enter  coordinate x y : ");
	scanf("%d %d",&X,&Y);
	POINT p_after = MakePOINT(X,Y);
	while(!CanUnitMoveTo(*CurrentUnit, p_after) || !NoObstacle(*CurrentUnit, p_after, M)){
		printf("You can't move there!\n");
		printf("Please enter cell’s coordinate x y : ");
		scanf("%d %d",&X,&Y);
		p_after = MakePOINT(X,Y);
	}
	GeserUnit(CurrentUnit, p_after);
}

void PrintPlayerStatus(Player PlayerTemp,Unit U){
	printf("Player %d's Turn\n",Warna(PlayerTemp));
	printf("Cash: %dG | Income: %dG | Upkeep: %dG\n", Gold(PlayerTemp),Income(PlayerTemp),Upkeep(PlayerTemp));
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

Player Undo(StackPlayer SP){
	Player Temp;
	Pop(&SP,&Temp);
	return Temp;
}

void ClearStack(StackPlayer *SP){
	infotype temp;
	while(!IsEmpty(*SP))
		Pop(SP,&temp);
}

void clrscr()
{
    system("@cls||clear");
}
