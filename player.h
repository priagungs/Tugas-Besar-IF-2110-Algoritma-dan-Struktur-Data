/* File: player.h */
/* Tanggal: 11 November 2017 */
/* made by : rwk03 */

#ifndef PLAYER_H
#define PLAYER_H

#include "boolean.h"
#include "boolean.h"
#include "listvillage.h"
#include "village.h"
#include "listofunit.h"
#include "unit.h"
#include "player.h"

typedef struct
{
	int Gold;
	int Income;
	int Upkeep;
	int Warna;
	ListVil LVillage;
	ListUnit LUnit;
} Player;

#define Gold(P) (P).Gold
#define Income(P) (P).Income
#define Upkeep(P) (P).Upkeep
#define Warna(P) (P).Warna
#define UnitList(P) (P).LUnit
#define VillageList(P) (P).LVillage

void Update_Turn(Player *Pl);
void Make_Player(Player *Pl, int warna);
void Update_Gold(Player *Pl, int Amount);
void Update_Income(Player *Pl, int Amount);
void Update_Upkeep(Player *Pl, int Amount);
void Add_Unit_First(Player *Pl, Unit U);
void Add_Unit_Last(Player *Pl, Unit U);
void Del_Unit(Player *Pl, Unit U);
void Add_Village (Player *Pl, Village V);
void Del_Village (Player *Pl, Village V);
void Next_Unit(Player Pl,int *nomor, Unit *Now, boolean *ada);
#endif
