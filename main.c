/*#include "jam.h"*/
#include "stackofpoint.h"
#include "listvillage.h"
#include "matriks.h"
#include "player.h"
#include "mesinkata.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "saveload.h"
#include "listofunit.h"
#include "interface.h"


int NB,NK,IndeksUnit;
char Str[15];
Player P1;
Player P2;
Player *CurrentPlayer;
ListVil Villages;
StackPoint SP;
int turn=1;
Unit Now;
boolean endgame = false;
FILE *pitaa;
infotypeU history;


PETA P;

//Command: gcc -Wall main.c player.c matriks.c listofunit.c unit.c listvillage.c village.c pcolor.c point.c stackofplayer.c mesinkata.c mesinkar.c stackofpoint.c saveload.c interface.c -lm -o hasil

void PrintPlayerStatus(Player P,Unit U);
void Attack(Unit* Now, Player* Enemy);
void Move(PETA M, Unit* CurrentUnit);
void ClearStack(StackPoint *SP);
void RekrutUnit(void);
void clrscr();
void INFO(POINT temp);
infotypeU Undo(StackPoint SP);
void HealWhiteMage(Player* P, PETA M);
void HealVillage(PETA *P, Player *P1, Player *P2, ListVil LV );

int main(){
	clrscr();
	int choice;
	BattleForOlympia();
	delay(2);
	printf("1. New Game\n2. Load Game\nInput : ");
	scanf("%d", &choice);
	while(choice != 1 && choice != 2){
		printf("Input Unknown\n");
		printf("1. New Game\n2. Load Game\nInput : ");
		scanf("%d", &choice);
	}

	if(choice == 1){
		clrscr();

/* 		========= Create New game =========		*/
		Make_Player(&P1,1);
		Make_Player(&P2,2);
		CreateEmptyVil(&Villages);

		BattleForOlympia();
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
		UpdatePETA(&P,P1,P2,Villages);
		RandomVillage(&Villages,10,NK,NB,&P);
	}
	else if (choice == 2){
		clrscr();

		Load(&NK, &NB, &P1, &P2, &Villages);
		Now = InfoUnit(FirstUnit(UnitList(P1)));
		MakePETA(NK,NB,&P);
		UpdatePETA(&P,P1,P2,Villages);
	}

	CurrentPlayer = &P1;
	IndeksUnit = 2;

	clrscr();
	PrintPETA(P);

	do{
		PrintPlayerStatus(*CurrentPlayer,Now);
		printf("Your Input: ");
		scanf("%s",Str);
		pitaa = fopen("pitakar.txt","w");
		fprintf(pitaa,"%s .",Str);
		fclose(pitaa);
		memset(&CKata.TabKata[0], 0, sizeof(CKata.TabKata));
		STARTKATA();
		printf("%s\n",CKata.TabKata);

		if(!strcmp(CKata.TabKata,"MOVE")){
			//menulis history untuk undo
			history.Pt = Lokasi_Unit(Now);
			history.mp = Movement_Point(Now);
			PushPoint(&SP,history);
			//pop current unit from list of unit
			if(Movement_Point(Now) != 0){
				Del_Unit(CurrentPlayer, Now);
				Move(P, &Now);
				//push moved current unit to list of unit

				if(BP(P, Absis(Lokasi_Unit(Now)), Ordinat(Lokasi_Unit(Now))) == 'V'){
					if(KBP(P,Absis(Lokasi_Unit(Now)), Ordinat(Lokasi_Unit(Now))) == 0){
						Movement_Point(Now) = 0;
						addressVillage V = SearchKoordinatVil(Villages, Lokasi_Unit(Now));
						Add_Village(CurrentPlayer, InfoVillage(V));
						ClearStack(&SP);
					}
					else{
						if(CurrentPlayer == &P1){
							if(KBP(P,Absis(Lokasi_Unit(Now)), Ordinat(Lokasi_Unit(Now))) == 2){
								Movement_Point(Now) = 0;
								addressVillage V = SearchKoordinatVil(Villages, Lokasi_Unit(Now));
								Add_Village(CurrentPlayer, InfoVillage(V));
								Del_Village(&P2, InfoVillage(V));
							}
						}
						else if (CurrentPlayer == &P2){
							if(KBP(P,Absis(Lokasi_Unit(Now)), Ordinat(Lokasi_Unit(Now))) == 1){
								Movement_Point(Now) = 0;
								addressVillage V = SearchKoordinatVil(Villages, Lokasi_Unit(Now));
								Add_Village(CurrentPlayer, InfoVillage(V));
								Del_Village(&P1, InfoVillage(V));
							}
						}
					}
				}

				if(!strcmp(Jenis_Unit(Now),"King"))
					Add_Unit_First(CurrentPlayer, Now);
				else
					Add_Unit_Last(CurrentPlayer, Now);
				UpdatePETA(&P,P1,P2,Villages);
				clrscr();
				PrintPETA(P);
			}
			else {
				printf("You can't move, your movement point is 0\n");
			}

		}

		else if(!strcmp(CKata.TabKata,"UNDO")){
			if(!IsEmptyPointStack(SP)){
				infotypeU old;
				PopPoint(&SP,&old);
				Del_Unit(CurrentPlayer,Now);
				Unit oldUnit = CreateUnit(Jenis_Unit(Now),old.Pt);
				Movement_Point(oldUnit) = old.mp;
				InsUnitLast(&UnitList(*CurrentPlayer),oldUnit);
				Now = oldUnit;
				clrscr();
				UpdatePETA(&P,P1,P2,Villages);
				PrintPETA(P);
			}else{
				clrscr();
				UpdatePETA(&P,P1,P2,Villages);
				PrintPETA(P);
				printf("You cannot undo!\n");
			}
		}

		else if(!strcmp(CKata.TabKata,"CHANGE_UNIT")){
			int nomor;
			printf("============= YOUR UNITS =============\n");
			PrintListUnit(UnitList(*CurrentPlayer));
			printf("Choose unit number : ");
			scanf("%d",&nomor);
			IndeksUnit = nomor+1;
			Now = SearchNomor(UnitList(*CurrentPlayer),nomor);
			printf("Your current unit is %s\n",Jenis_Unit(Now));

		}

		else if(!strcmp(CKata.TabKata,"NEXT_UNIT")){
			boolean ada = false;
			Next_Unit(*CurrentPlayer, &IndeksUnit, &Now, &ada);
			if(!ada){
				clrscr();
				PrintPETA(P);
				printf("Your current unit is %s at ",Jenis_Unit(Now));
				TulisPOINT(Lokasi_Unit(Now)); printf("\n");
				IndeksUnit++;
			}
		}

		else if(!strcmp(CKata.TabKata,"RECRUIT")){
			//Cek unit yang mencoba rekrut
		 //Cek unit yang mencoba rekrut
		   if (!strcmp(Jenis_Unit(Now),"King"))
		   {
		    ClearStack(&SP);
		    RekrutUnit();
		   } else {
		    printf("Rekrut unit hanya dapat dilakukan oleh king!\n");
		   }
		}

		else if(!strcmp(CKata.TabKata,"ATTACK")){
			ClearStack(&SP);
			//pop current unit from list of unit
			DelKoordinatUnit(&UnitList(*CurrentPlayer), Lokasi_Unit(Now), &Now);
			if(CurrentPlayer == &P1){
				Attack(&Now, &P2);
			}
			else {
				Attack(&Now, &P1);
			}


			//push moved current unit to list of unit
			if(Health(Now) != 0){
				if(!strcmp(Jenis_Unit(Now), "King")){
					InsUnitFirst(&UnitList(*CurrentPlayer), Now);
				}
				else {
					InsUnitLast(&UnitList(*CurrentPlayer), Now);
				}
			}
			else {
				Update_Upkeep(CurrentPlayer, -1*UpkeepUnit(Now));
				Now = InfoUnit(FirstUnit(UnitList(*CurrentPlayer)));
			}

			if(IsKingDead(UnitList(P1))){
				printf("Player 2 Win!\n");
				endgame=true;
				break;
			}
			else if(IsKingDead(UnitList(P2))) {
				printf("Player 1 Win!\n");
				endgame=true;
				break;
			}

			UpdatePETA(&P,P1,P2,Villages);

		}

		else if(!strcmp(CKata.TabKata,"MAP")){
			UpdatePETA(&P,P1,P2,Villages);
			PrintPETA(P);
		}

		else if(!strcmp(CKata.TabKata,"INFO")){
			int x , y;
			printf("Enter the coordinate of the cell you want to see : ");
			scanf("%d%d",&x,&y);
			POINT temp = MakePOINT(x,y);
			clrscr();
			PrintPETA(P);
			INFO(temp);
		}

		else if(!strcmp(CKata.TabKata,"END_TURN")){
			ClearStack(&SP);
			Update_Turn(CurrentPlayer);
			if(turn%2){
				CurrentPlayer = &P2;
				ResetMovementPoint(&UnitList(*CurrentPlayer));
				Now = InfoUnit(FirstUnit(UnitList(*CurrentPlayer)));
				turn++;
			} else {
				CurrentPlayer = &P1;
				ResetMovementPoint(&UnitList(*CurrentPlayer));
				Now = InfoUnit(FirstUnit(UnitList(*CurrentPlayer)));
				turn++;
			}
			ResetAttackChance(&UnitList(P1));
			ResetAttackChance(&UnitList(P2));
			IndeksUnit = 2;
			clrscr();
			PrintPETA(P);
			HealWhiteMage(&P1, P);
			HealWhiteMage(&P2, P);
			HealVillage(&P, &P1, &P2, Villages);

		}

		else if(!strcmp(Str,"SAVE")){
			ClearStack(&SP);
			clrscr();
			Save(NK, NB, P1, P2, Villages);
		}
		else{
			if(strcmp(Str,"EXIT")){
				clrscr();
				PrintPETA(P);
				printf("No command found!\n");
			}
		}

	}while(strcmp(Str,"EXIT"));
	if(!endgame){
		printf("Do you want to save your game ? (y/n)\n");
		char c;
		scanf(" %c", &c);
		if(c == 'y'){
			clrscr();
			Save(NK, NB, P1, P2, Villages);
		}
	}
	ClearStack(&SP);
}


void RekrutUnit(void){
	//Cek castle tidak penuh!
	boolean kondisiRekrutUnitBisa= true;
	if (Warna(*CurrentPlayer) == 1 )
	{
		//printf("GOBLOK TEST\n");
		if (UP(P,KolMin+1,NBrsEff(P)-2)=='K')
		{
			if((UP(P,KolMin+1,NBrsEff(P)-3)=='N') ){

			} else {

				if((UP(P,KolMin,NBrsEff(P)-2)=='N')){

				} else {

					if((UP(P,KolMin+1,NBrsEff(P)-1)=='N')){

					} else {

						if((UP(P,KolMin+2,NBrsEff(P)-2)=='N')){

						} else {
							printf("Castle anda penuh semua!\n");
							kondisiRekrutUnitBisa=false;
						}
					}

				}
			}
		}else {
			printf("King anda harus berada di tower!\n");
			kondisiRekrutUnitBisa=false;
		}


	} else {

		if (UP(P,NKolEff(P)-2,BrsMin+1) =='K')
		{

			if((UP(P,NKolEff(P)-2,BrsMin)=='N')  ){

			} else {

				if((UP(P,NKolEff(P)-3,BrsMin+1)=='N')){

				} else {

					if((UP(P,NKolEff(P)-2,BrsMin+2)=='N')){

					} else {

						if((UP(P,NKolEff(P)-1,BrsMin+1)=='N')){

						} else {
							printf("Castle anda penuh semua!\n");
							kondisiRekrutUnitBisa=false;
						}
					}

				}
			}
		}else {
			printf("King anda harus berada di tower!\n");
			kondisiRekrutUnitBisa=false;
		}

	}




	if (kondisiRekrutUnitBisa)
	{
		printf("Masukan jenis unit yang ingin di rekrut.\n");
		printf("1. Swordsman (200G)\n");
		printf("2. Archer (200G)\n");
		printf("3. White Mage (500G)\n");
		printf("Masukan pilihan(integer):\n");

		char jenisUnitRekrut[200];
		int pilihanUnit;
		scanf("%d", &pilihanUnit);

		while (pilihanUnit<1 || pilihanUnit>3 )
		{
			printf("Masukan jenis unit anda masukan salah.\n");
			printf("Masukan kembali jenis unit yang ingin di rekrut.\n");
			printf("1. Swordsman (200G)\n");
			printf("2. Archer (200G)\n");
			printf("3. White Mage (500G)\n");
			printf("Masukan pilihan(integer):\n");
			scanf("%d", &pilihanUnit);
		}

		boolean GoldRekrutCukup = true;
		if (pilihanUnit==1)
		{
			strcpy(jenisUnitRekrut,"Swordsman");
			if ( Gold(*CurrentPlayer) <200 ) {
				printf("Gold anda tidak cukup untuk melakukan rekrut unit ini!\n");
				GoldRekrutCukup = false;
			}
		} else if (pilihanUnit==2){
			strcpy(jenisUnitRekrut,"Archer");
			if ( Gold(*CurrentPlayer) <200 ) {
				printf("Gold anda tidak cukup untuk melakukan rekrut unit ini!\n");
				GoldRekrutCukup = false;
			}
		} else {
			strcpy(jenisUnitRekrut,"White Mage");
			if ( Gold(*CurrentPlayer) <500 ) {
				printf("Gold anda tidak cukup untuk melakukan rekrut unit ini!\n");
				GoldRekrutCukup = false;
			}
		}
		boolean bisaRekrutUnit = false;
		POINT lokasiUnitDirekrut; // tergantung player 1/2
		if (GoldRekrutCukup) {

			if (Warna(*CurrentPlayer) == 1 )
			{
				if (UP(P,KolMin+1,NBrsEff(P)-2)=='K')
				{
					boolean castleDipilih = false;
					while(castleDipilih == false){
						printf("Pilih castle di mana unit akan direkrut!\n");
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
										printf("Castle anda penuh!\n");
									}
								}
							}
						}
					}
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
								lokasiUnitDirekrut = MakePOINT(NKolEff(P)-3,BrsMin+1);
								bisaRekrutUnit = true;
								castleDipilih = true;
							} else {

								if((UP(P,NKolEff(P)-2,BrsMin+2)=='N')&& castleRekrut==3){
									lokasiUnitDirekrut = MakePOINT(NKolEff(P)-2,BrsMin+2);
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
				}
			}
		}

		if (bisaRekrutUnit){
			Unit RekrutUnit = CreateUnit(jenisUnitRekrut,lokasiUnitDirekrut);
			Add_Unit_Last(CurrentPlayer,RekrutUnit);
			int hargaUnit = -1*Harga_Unit(RekrutUnit);
			int upkeepUnit = UpkeepUnit(RekrutUnit);

			Update_Gold(CurrentPlayer, hargaUnit);
			Update_Upkeep(CurrentPlayer, upkeepUnit);
			UpdatePETA(&P,P1,P2,Villages);
			clrscr();
			PrintPETA(P);
			printf("Unit berhasil direkrut!\n");

		} else {
			printf("Unit tidak berhasil direkrut.\n");
		}
	}


}

void Move(PETA M, Unit* CurrentUnit){
	int X,Y;
	if(Movement_Point(*CurrentUnit) <= 0){
	}
	// print peta dengan posisi dimana unit bisa berpindah
	else{
		for(int i=0; i<NBrsEff(M); i++){
			for(int j=0; j<NKolEff(M); j++){
				POINT temp = MakePOINT(i,j);
				if(CanUnitMoveTo(*CurrentUnit, temp) && NoObstacle(*CurrentUnit, temp, M) && Panjang(temp, Lokasi_Unit(*CurrentUnit)) != 0){
					UP(M,i,j) = '#';
				}
			}
		}
		clrscr();
		PrintPETA(M);

		printf("Please enter coordinate x y : ");
		scanf("%d %d",&X,&Y);
		POINT p_after = MakePOINT(X,Y);
		while(!CanUnitMoveTo(*CurrentUnit, p_after) || !NoObstacle(*CurrentUnit, p_after, M)){
			printf("You can't move there!\n");
			printf("Please enter coordinate x y : ");
			scanf("%d %d",&X,&Y);
			p_after = MakePOINT(X,Y);
		}
		GeserUnit(CurrentUnit, p_after);
	}
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

infotypeU Undo(StackPoint SP){
	infotypeU Temp;
	PopPoint(&SP,&Temp);
	return Temp;
}

void ClearStack(StackPoint *SP){
	infotypeU temp;
	while(!IsEmptyPointStack(*SP))
		PopPoint(SP,&temp);
}

void clrscr()
{
    system("@cls||clear");
}

void Attack(Unit* Now, Player* Enemy){
	addressUnit P = FirstUnit(UnitList(*Enemy));
	Unit NearEnemyUnit[5];
	int N=0;
	boolean end = false;
	while(!end && P != Nil){
		if(Panjang(Lokasi_Unit(InfoUnit(P)), Lokasi_Unit(*Now)) == 1){
			N++;
			DelKoordinatUnit(&UnitList(*Enemy), Lokasi_Unit(InfoUnit(P)), &NearEnemyUnit[N]);
			P = NextUnit(P);
		}
		else {
			P = NextUnit(P);
		}
		if(P == FirstUnit(UnitList(*Enemy))){
			end = true;
		}
	}

	if(N != 0){
		// print enemy unit that ready to be attacked
		printf("Please select enemy you want to attack : \n");
		for(int i=1; i<=N; i++){
			if(!strcmp(Tipe_Serangan(NearEnemyUnit[i]), Tipe_Serangan(*Now)) || !strcmp(Jenis_Unit(NearEnemyUnit[i]), "King")){
				printf("%d. %s (%d,%d) | Health %d/%d (Retaliates)\n",
					i,
					Jenis_Unit(NearEnemyUnit[i]),
					Absis(Lokasi_Unit(NearEnemyUnit[i])), Ordinat(Lokasi_Unit(NearEnemyUnit[i])),
					Health(NearEnemyUnit[i]),
					Max_Health(NearEnemyUnit[i])
				);
			}
			else {
				printf("%d. %s (%d,%d) | Health %d/%d (Not Retaliates)\n",
					i,
					Jenis_Unit(NearEnemyUnit[i]),
					Absis(Lokasi_Unit(NearEnemyUnit[i])), Ordinat(Lokasi_Unit(NearEnemyUnit[i])),
					Health(NearEnemyUnit[i]),
					Max_Health(NearEnemyUnit[i])
				);
			}
		}
		printf("Select enemy you want to attack : ");
		int selected;
		scanf("%d", &selected);

		AttackUnit(Now, &NearEnemyUnit[selected]);

	}
	else{
		printf("There is no near enemy!\n");
	}
	for(int i=1; i<=N; i++){
		if(Health(NearEnemyUnit[i]) != 0){
			if(!strcmp(Jenis_Unit(NearEnemyUnit[i]), "King")){
				InsUnitFirst(&UnitList(*Enemy), NearEnemyUnit[i]);
			}
			else {
				InsUnitLast(&UnitList(*Enemy), NearEnemyUnit[i]);
			}
		}
		else {
			Update_Upkeep(Enemy, -1*UpkeepUnit(NearEnemyUnit[i]));
		}
	}
}

void INFO(POINT temp){
	printf("============ Cell Info ============\n");
	if(SearchKoordinatVil(VillageList(P1),temp) != Nil)
		printf("Village\nOwned by Player 1.\n\n");
	else if(SearchKoordinatVil(VillageList(P2),temp) != Nil)
		printf("Village\nOwned by Player 2.\n\n");
	else if(SearchKoordinatVil(Villages,temp) != Nil)
		printf("Village\nNobody owns it.\n\n");
	else printf("There is an empty land.\n\n");
	addressUnit U;
	if(SearchKoordinatUnit(UnitList(P1), temp) != Nil){
		printf("============ Unit Info ============\n");
		U = SearchKoordinatUnit(UnitList(P1), temp);
		printf("%s",Jenis_Unit(InfoUnit(U)));
		PrintUnit(InfoUnit(U));
		printf("Owned by Player 1.\n");
	}
	else if(SearchKoordinatUnit(UnitList(P2), temp) != Nil){
		U = SearchKoordinatUnit(UnitList(P1), temp);
		PrintUnit(InfoUnit(U));
		printf("Owned by Player 2.\n");
	}
	else
		printf("No unit there.\n");
	printf("\n");
}

void HealWhiteMage(Player* P, PETA M){
	for(int i=0; i<= NBrsEff(M); i++){
		for(int j=0; j<=NKolEff(M); j++){
			if(UP(M,i,j) == 'W'){
				addressUnit whiteMage = SearchKoordinatUnit(UnitList(*P), MakePOINT(i,j));
				// Looking for unit who will be healed
				if(whiteMage != Nil){
					for(int k = 0; k<=NBrsEff(M); k++){
						for(int l = 0; l<=NKolEff(M); l++){
							// checking whether exist adjacent unit or not
							addressUnit adjacentUnit = SearchKoordinatUnit(UnitList(*P), MakePOINT(k,l));
							if(adjacentUnit != Nil){
								if(Panjang(Lokasi_Unit(InfoUnit(adjacentUnit)), Lokasi_Unit(InfoUnit(whiteMage))) == 1){
									Unit temp = InfoUnit(adjacentUnit);
									// pop adjacent unit
									Del_Unit(P, temp);

									// Heal
									if(Health(temp)+7 > Max_Health(temp)){
										Health(temp) = Max_Health(temp);
									}
									else {
										Health(temp) += 7;
									}

									// Push adjacent unit back to player
									if(!strcmp(Jenis_Unit(temp),"King"))
										Add_Unit_First(P, temp);
									else
										Add_Unit_Last(P, temp);
								}
							}
						}
					}
				}
			}
		}
	}
}

void HealVillage(PETA *P, Player *P1, Player *P2, ListVil LV ){
 	int Baris = NBrsEff(*P);
	int Kolom = NKolEff(*P);
 	UpdatePETA(P,*P1,*P2,LV);
 	for (int j = 0; j < Baris; ++j)
 	{
		for (int i = 0; i < Kolom; ++i)
  		{
   			if (BP(*P,i,j)=='V')
   			{
    			if (UP(*P,i,j)!='N')
    			{
     				if (KUP(*P,i,j)==1)
     				{
      					addressUnit AdrUnitHeal = SearchKoordinatUnit (UnitList(*P1),MakePOINT(i,j));
      					if (AdrUnitHeal!=Nil)
      					{
       						Health(InfoUnit(AdrUnitHeal))+=7;
       						if (Health(InfoUnit(AdrUnitHeal)) > Max_Health(InfoUnit(AdrUnitHeal)))
       						{
        						Health(InfoUnit(AdrUnitHeal)) = Max_Health(InfoUnit(AdrUnitHeal));
       						}
      					}


     				} else {
      					addressUnit AdrUnitHeal = SearchKoordinatUnit (UnitList(*P2),MakePOINT(i,j));
      					if (AdrUnitHeal!=Nil)
      					{
       						Health(InfoUnit(AdrUnitHeal))+=7;
       						if (Health(InfoUnit(AdrUnitHeal)) > Max_Health(InfoUnit(AdrUnitHeal)))
       						{
        						Health(InfoUnit(AdrUnitHeal)) = Max_Health(InfoUnit(AdrUnitHeal));
       						}

      					}
     				}
    			}
   			}
  		}
 	}
}
