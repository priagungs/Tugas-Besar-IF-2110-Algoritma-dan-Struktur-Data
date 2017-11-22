#ifndef UNIT_H
#define UNIT_H

#include "boolean.h"
#include "point.h"

typedef struct {
  char* JenisUnit;
  int MaxHealth;
  int Nyawa;
  int Attack;
  int MaxMovPoint;
  int MovPoint;
  int Upkeep;;
  char* TipeSerangan;
  boolean AttackChance;
  POINT Lokasi;
  int Harga;
} Unit;

// Selektor
#define Jenis_Unit(M) (M).JenisUnit
#define Max_Health(M) (M).MaxHealth
#define Health(M) (M).Nyawa
#define UpkeepUnit(M) (M).Upkeep
#define Attack_Damage(M) (M).Attack
#define Max_Movement_Point(M) (M).MaxMovPoint
#define Movement_Point(M) (M).MovPoint
#define Tipe_Serangan(M) (M).TipeSerangan
#define Kesempatan_Serangan(M) (M).AttackChance
#define Lokasi_Unit(M) (M).Lokasi
#define Harga_Unit(M) (M).Harga

// PROTOTIPE PRIMITIF
Unit CreateUnit(char* jenis, POINT Lokasi);
// menghasilkan sebuah Unit dengan jenis = 'jenis'

void GeserUnit(Unit *U, POINT P);
// menggeser unit ke arah "sumbu" sebanyak "langkah"

void AttackUnit(Unit *U1, Unit *U2);
// U1 menyerang U2, tipe serangan diperhatikan

boolean IsUnitDead(Unit U);
// true jika unit habis nyawa nyawa

boolean CanUnitMoveTo(Unit U, POINT P);
// true jika unit U dapat bergerak ke P

boolean CanUnitAttack(Unit U1, Unit U2);
// true jika unit U1 dapat menyerang unit U2

void PrintUnit ( Unit U);
// menampilakan ke layar atribut atribut suatu unit

#endif
