#include "boolean.h"
#include "listvillage.h"
#include "village.h"
#include "listofunit.h"
#include "unit.h"
#include "player.h"

void Make_Player(Player *Pl, int warna){
	Gold(*Pl) = 500;
	Income(*Pl) = 100;
	Upkeep(*Pl) = 0;
	Warna(*Pl) = warna;
	CreateEmptyVil(&VillageList(*Pl));
	CreateEmptyUnit(&UnitList(*Pl));
}

void Update_Gold(Player *Pl, int Amount){
// gold bertambah sebanyak Amount
	Gold(*Pl) += Amount;
}

void Update_Income(Player *Pl, int Amount){
// income bertambah sebanyak Amount
	Income(*Pl) += Amount;
}

void Update_Upkeep(Player *Pl, int Amount){
// upkeep bertambah sebanyak Amount
	Upkeep(*Pl) += Amount;
}

void Update_Turn(Player *Pl){
	Gold(*Pl) += (Income(*Pl)-Upkeep(*Pl));
}

void Add_Unit_First(Player *Pl, Unit U){
// menambahkan U pada list of unit di player
	InsUnitFirst (&UnitList(*Pl), U);
	Update_Upkeep(Pl,UpkeepUnit(U));
}

void Add_Unit_Last(Player *Pl, Unit U){
	InsUnitLast (&UnitList(*Pl), U);
	Update_Upkeep(Pl,UpkeepUnit(U));
}

void Del_Unit(Player *Pl, Unit U){
// menghapus U pada list of unit di player
	Unit temp;
	DelKoordinatUnit (&UnitList(*Pl), Lokasi_Unit(U), &temp);
	Update_Upkeep(Pl,-1*UpkeepUnit(U));
}

void Add_Village (Player *Pl, Village V){
// menambahkan V pada list of village di player
	Update_Income(Pl, IncomeVil(V));
	InsVFirstVil (&VillageList(*Pl), V);
}

void Del_Village (Player *Pl, Village V){
// menghapus V pada list of village di player
	Update_Income(Pl, (-1)*IncomeVil(V));
	DelPVil(&VillageList(*Pl),V);
}

void Next_Unit(Player Pl,int *nomor, Unit *Now, boolean *ada){
	int NbUnit = 1;
	addressUnit P = FirstUnit(UnitList(Pl));
	while(NextUnit(P) != FirstUnit(UnitList(Pl))){
		NbUnit ++;
		P = NextUnit(P);
	}
	if(*nomor > NbUnit)
		*nomor -= NbUnit;
	int tmp = *nomor;
	Unit U = SearchNomor(UnitList(Pl),*nomor);
	while(Movement_Point(U) == 0 && !Kesempatan_Serangan(U)){
		(*nomor) ++;
		if(*nomor > NbUnit)
			*nomor -= NbUnit;
		if(*nomor == tmp){
			*ada = true;
			break;
		}
		U = SearchNomor(UnitList(Pl),*nomor);
	}
	if(*ada){
		printf("No more unit availlable.\n");
	}
	else{
		*Now = U;
	}
}
