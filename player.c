#include "boolean.h"
#include "listvillage.h"
#include "village.h"
#include "listofunit.h"
#include "unit.h"
#include "player.h"	

void Make_Player(Player *Pl, int warna){
	Gold(*Pl) = 1000;
	Income(*Pl) = 100;
	Upkeep(*Pl) = 50;
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

void Add_Unit(Player *Pl, Unit U){
// menambahkan U pada list of unit di player
	InsUnitFirst (&UnitList(*Pl), U);
}

void Del_Unit(Player *Pl, Unit U){
// menghapus U pada list of unit di player	
	DelKoordinatUnit (&UnitList(*Pl), Lokasi_Unit(U));
}

void Add_Village (Player *Pl, Village V){
// menambahkan V pada list of village di player
	Update_Income(Pl, IncomeVil(V));
	InsVFirstVil (&VillageList(*Pl), V);
}

void Del_Village (Player *Pl, Village V){
// menghapus V pada list of village di player
	Update_Income(Pl, -1*IncomeVil(V));
	DelPVil(&VillageList(*Pl),V);
}

void PrintPlayerInfo(Player P){
// menampilkan atribut atribut yang dimiliki player
	printf("Gold = %d\n",Gold(P));
	printf("Income = %d\n",Income(P));
	printf("Upkeep = %d\n",Upkeep(P));
	printf("Warna = %d\n",Warna(P));
}