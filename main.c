/*#include "jam.h"*/
/*#include "stackofplayer.h"*/
#include "listvillage.h"
#include "matriks.h"
#include "player.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queuelist.h"
#include "stackofplayer.h"

int NB,NK;
char Str[15];
Player P1;
Player P2;
ListVil Villages;
/*StackPlayer SP;*/
/*
QueueP QP;
*/
PETA P;

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

void Move(PETA M, Player P, Unit* CurrentUnit){
	int X,Y,x1,y1;

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

	printf("Please enter cell’s coordinate x y : ");
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

/*
void Undo()
*/

/*boolean CheckKingAtTower(Player P,PETA P,int NB,int NK){

}*/

/*void Recruit(Player P){
	printf("1. Archer | Health 40 | ATK 30 | \n");
}*/

int main(){
	Make_Player(&P1,1);
	Make_Player(&P2,2);
	CreateEmptyVil(&Villages);

	printf("JUDUL\n");

	printf("Masukkan input besar peta (BARIS,KOLOM)\n");
	scanf("%d %d", &NB,&NK);

	MakePETA(NB,NK,&P);
	Unit Now = CreateUnit("King",MakePOINT(NB-2,KolMin+1));
	InsUnitFirst(&UnitList(P1),Now);
	Now = CreateUnit("King",MakePOINT(BrsMin+1,NK-2));
	InsUnitFirst(&UnitList(P2),Now);

	StackPlayer Stack;
	CreateEmpty(&Stack);

	Queue Q;
	CreateEmptyQueue(&Q);
	AddQueue(&Q, 1);
	AddQueue(&Q, 2);

	RandomVillage(&Villages,10,NB,NK,&P);
	PrintListVillage(Villages);
	do{
		UpdatePETA(&P,P1,P2,Villages);
		PrintPETA(P);

		PrintPlayerStatus(P2,Now);
		printf("Your Input: ");
		scanf("%s",Str);

		if(!strcmp(Str,"MOVE")){
			Move(P, P1, &Now);
		}else if(!strcmp(Str,"UNDO")){

		}else if(!strcmp(Str,"CHANGE_UNIT")){

		}else if(!strcmp(Str,"NEXT_UNIT")){
			//Now = InfoUnit(NextUnit(FirstUnit(UnitList(P1))));
		}else if(!strcmp(Str,"RECRUIT")){

		}else if(!strcmp(Str,"ATTACK")){

		}else if(!strcmp(Str,"MAP")){

		}else if(!strcmp(Str,"INFO")){

		}else if(!strcmp(Str,"END_TURN")){

		}else if(!strcmp(Str,"SAVE")){

		}else{
			if(strcmp(Str,"EXIT")){
				printf("No command found!\n");
			}
		}
	}while(strcmp(Str,"EXIT"));
}
