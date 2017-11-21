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
ListVil Villages;
StackPlayer SP;
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

void Move(PETA M,Player P){
	int X,Y,x1,y1;
	do{
		printf("Please enter cell’s coordinate x y: \n");
		scanf("%d %d",X,Y);
		scanf
	}

	GeserUnit(&)
}

Player Undo(StackPlayer SP){
	Player Temp;
	Pop(&SP,&Temp);
	return Temp;
}

void ClearStack(StackPlayer *SP){
	infotype temp;

	while(!IsEmpty(*SP)){
		Pop(&SP,&temp);
	}
}


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

	RandomVillage(&Villages,10,NB,NK,&P);
	PrintListVillage(Villages);
	do{
		UpdatePETA(&P,P1,P2,Villages);
		PrintPETA(P);

		PrintPlayerStatus(P2,Now);
		printf("Your Input: ");
		scanf("%s",Str);
		
		if(!strcmp(Str,"MOVE")){
			Push(&SP,Pl);
			
		}else if(!strcmp(Str,"UNDO")){
			if(!IsEmpty(SP)){
				Pl = Undo(SP);
			}else{
				printf("You cannot undo!\n");
			}
		}else if(!strcmp(Str,"CHANGE_UNIT")){

		}else if(!strcmp(Str,"NEXT_UNIT")){
			Now = InfoUnit(NextUnit(FirstUnit(UnitList(P1))));
		}else if(!strcmp(Str,"RECRUIT")){
			ClearStack(&SP);
		}else if(!strcmp(Str,"ATTACK")){
			ClearStack(&SP);
		}else if(!strcmp(Str,"MAP")){
			UpdatePETA(&P,P1,P2,Villages);
			PrintPETA(P);
		}else if(!strcmp(Str,"INFO")){
			
		}else if(!strcmp(Str,"END_TURN")){
			ClearStack(&SP);
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
