#include "unit.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Unit CreateUnit(char* jenis, POINT Lokasi)
// menghasilkan sebuah Unit dengan jenis = 'jenis'
{
  Unit U;
  if(!strcmp(jenis,"King")){
    Jenis_Unit(U) = "King";
    // Dibawah ini bisa disesuaikan angka angka nya
    Max_Health(U) = 100;
    Attack_Damage(U) = 40;
    Max_Movement_Point(U) = 4;
    Harga_Unit(U) = 0;
    UpkeepUnit(U) = 0;
    Health(U) = Max_Health(U);
    Movement_Point(U) = 4;
    Tipe_Serangan(U) = "Melee";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  else if(!strcmp(jenis,"Archer")){
    Jenis_Unit(U) = "Archer";
    // Dibawah ini bisa disesuaikan angka angka nya
    Max_Health(U) = 40;
    Attack_Damage(U) = 10;
    Max_Movement_Point(U) = 5;
    Harga_Unit(U) = 200;
    UpkeepUnit(U) = 15;
    Health(U) = Max_Health(U);
    Movement_Point(U) = 0;
    Tipe_Serangan(U) = "Ranged";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  else if(!strcmp(jenis,"Swordsman")){
    Jenis_Unit(U) = "Swordsman";
    // Dibawah ini bisa disesuaikan angka angka nya
    Max_Health(U) = 55;
    Attack_Damage(U) = 15;
    Max_Movement_Point(U) = 3;
    Harga_Unit(U) = 200;
    UpkeepUnit(U) = 15;
    Health(U) = Max_Health(U);
    Movement_Point(U) = 0;
    Tipe_Serangan(U) = "Melee";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  else if(!strcmp(jenis,"White Mage")){
    Jenis_Unit(U) = "White Mage";
    Max_Health(U) = 60;
    Attack_Damage(U) = 15;
    Max_Movement_Point(U) = 5;
    Harga_Unit(U) = 500;
    UpkeepUnit(U) = 20;
    Health(U) = Max_Health(U);
    Movement_Point(U) = 0;
    Tipe_Serangan(U) = "Melee";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  return U;
}

void GeserUnit(Unit *U, POINT P)
// menggeser unit ke titik P
{
  if(!IsUnitDead(*U)){
    if(CanUnitMoveTo(*U, P)){
      Movement_Point(*U) -= abs(Absis(P)-Absis(Lokasi_Unit(*U))) + abs(Ordinat(P)-Ordinat(Lokasi_Unit(*U)));
      Absis(Lokasi_Unit(*U)) = Absis(P);
      Ordinat(Lokasi_Unit(*U)) = Ordinat(P);
      printf("You have successfully moved to (%d, %d)\n", Absis(P), Ordinat(P));
    }
    else {
      printf("You can't move there!\n");
    }
  }
}

void AttackUnit(Unit *U1, Unit *U2)
// Prekondisi, jarak U1 dan U2 harus sudah memungkinkan untuk attack
// U1 menyerang U2, tipe serangan diperhatikan
{
  srand(time(NULL));   // should only be called once
  const int prob = 70; //U1 will hit U2 if probAttack more than prob
  if(!Kesempatan_Serangan(*U1)){
    printf("You don't have a chance to attack anyone!\n");
  }
  else {
    Kesempatan_Serangan(*U1) = false;
    Movement_Point(*U1) = 0;

    int probAttack = rand()%100; //generate probAttack
    // attack
    if(probAttack <= prob){
      if(Health(*U2) > Attack_Damage(*U1)){
        Health(*U2) -= Attack_Damage(*U1);
        printf("Enemy's %s is damaged by %d\n", Jenis_Unit(*U2), Attack_Damage(*U1));
      }
      else {
        int damage = Health(*U2);
        Health(*U2) = 0;
        printf("Enemy's %s is damaged by %d\n", Jenis_Unit(*U2), damage);
        printf("Enemy's %s is dead\n", Jenis_Unit(*U2));
      }
    }
    else {
      printf("Oh damn, it missed!\n");
    }

    // retaliates

    if(!IsUnitDead(*U2) && ( (Jenis_Unit(*U1) == Jenis_Unit(*U2)) || !strcmp(Jenis_Unit(*U2),"King") )){
      printf("Enemy's %s retaliates\n", Jenis_Unit(*U2));
      int probRetaliates = rand()%100; //generate Retaliates
      if(probRetaliates <= prob){
        if(Health(*U1) > Attack_Damage(*U2)){
          Health(*U1) -= Attack_Damage(*U2);
          printf("Your %s is damaged by %d\n", Jenis_Unit(*U1), Attack_Damage(*U2));
        }
        else {
          int damage = Health(*U1);
          Health(*U1) = 0;
          printf("Your %s is damaged by %d\n", Jenis_Unit(*U1), damage);
          printf("Your %s is dead\n", Jenis_Unit(*U1));
        }
      }
      else {
        printf("Lucky, your enemy's retaliation missed\n");
      }
    }
  }
}

boolean IsUnitDead(Unit U)
// true jika unit habis nyawa
{
  return Health(U) == 0;
}

boolean CanUnitMoveTo(Unit U, POINT P)
// true jika unit U dapat bergerak ke P
{
  // combine noObstacle with movement_point provision
  // if(Absis(P) - Absis(Lokasi_Unit(U)) == Ordinat(P) - Ordinat(Lokasi_Unit(U))){
  //   // return Movement_Point(U) >= abs(Absis(P)-Absis(Lokasi_Unit(U))) + abs(Ordinat(P)-Ordinat(Lokasi_Unit(U)));
  // }
  // else{

    return Movement_Point(U) >= Panjang(Lokasi_Unit(U), P);
}

boolean CanUnitAttack(Unit U1, Unit U2)
// true jika unit U1 dapat menyerang unit U2
{
  if(Kesempatan_Serangan(U1) && Panjang(Lokasi_Unit(U1), Lokasi_Unit(U2)) == 1){
      return true;
  }
  else {
      return false;
  }
}

void PrintUnit( Unit U){
  printf("  Position : (%d,%d)  |",Absis(Lokasi_Unit(U)),Ordinat(Lokasi_Unit(U)));
  printf("  Health : %d/%d  |", Health(U), Max_Health(U));
  printf("  Damage : %d  |",Attack_Damage(U));
  printf("  Movement Point: %d  |",Movement_Point(U));
  printf("  Chance of Attack : ");
  if(Kesempatan_Serangan(U)){
    printf("Yes\n");
  }else{
    printf("No\n");
  }
}
