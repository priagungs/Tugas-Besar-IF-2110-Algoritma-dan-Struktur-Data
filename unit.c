#include "unit.h"
#include "point.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// PROTOTIPE PRIMITIF
Unit CreateUnit(char* jenis, POINT Lokasi)
// menghasilkan sebuah Unit dengan jenis = 'jenis'
{
  Unit U;
  if(!strcmp(jenis,"King")){
    Jenis_Unit(U) = "King";
    // Dibawah ini bisa disesuaikan angka angka nya
    Max_Health(U) = 100;
    Attack_Damage(U) = 40;
    Max_Movement_Point(U) = 10;
    Harga_Unit(U) = 10;
    UpkeepUnit(U) = 0;
    Health(U) = Max_Health(U);
    Movement_Point(U) = Max_Movement_Point(U);
    Tipe_Serangan(U) = "Melee";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  if(!strcmp(jenis,"Archer")){
    Jenis_Unit(U) = "Archer";
    // Dibawah ini bisa disesuaikan angka angka nya
    Max_Health(U) = 40;
    Attack_Damage(U) = 30;
    Max_Movement_Point(U) = 10;
    Harga_Unit(U) = 30;
    UpkeepUnit(U) = 5;
    Health(U) = Max_Health(U);
    Movement_Point(U) = Max_Movement_Point(U);
    Tipe_Serangan(U) = "Ranged";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  if(!strcmp(jenis,"Swordsman")){
    Jenis_Unit(U) = "Swordsman";
    // Dibawah ini bisa disesuaikan angka angka nya
    Max_Health(U) = 80;
    Attack_Damage(U) = 40;
    Max_Movement_Point(U) = 10;
    Harga_Unit(U) = 30;
    UpkeepUnit(U) = 10;
    Health(U) = Max_Health(U);
    Movement_Point(U) = Max_Movement_Point(U);
    Tipe_Serangan(U) = "Melee";
    Kesempatan_Serangan(U) = true;
    Lokasi_Unit(U) = Lokasi;
  }
  if(!strcmp(jenis,"White Mage")){
    Jenis_Unit(U) = "White Mage";
    Max_Health(U) = 60;
    Attack_Damage(U) = 20;
    Max_Movement_Point(U) = 10;
    Harga_Unit(U) = 50;
    UpkeepUnit(U) = 20;
    Health(U) = Max_Health(U);
    Movement_Point(U) = Max_Movement_Point(U);
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

void Attack(Unit *U1, Unit *U2)
// Prekondisi, jarak U1 dan U2 harus sudah memungkinkan untuk attack
// U1 menyerang U2, tipe serangan diperhatikan
{
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
    if(!IsUnitDead(*U2) && (Jenis_Unit(*U1) == Jenis_Unit(*U2) || Jenis_Unit(*U2) == "King")){
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
// prekondisi pada point P tidak ada unit apapun
{
  if(Absis(P) - Absis(Lokasi_Unit(U)) == Ordinat(P) - Ordinat(Lokasi_Unit(U))){
    return Movement_Point(U) >= abs(Absis(P)-Absis(Lokasi_Unit(U))) + abs(Ordinat(P)-Ordinat(Lokasi_Unit(U)));
  }
  else{
    if(Absis(P) != Absis(Lokasi_Unit(U)) && Ordinat(P)!=Ordinat(Lokasi_Unit(U))){
      return false;
    }
    else {
      //return Movement_Point(U) >= Panjang(Lokasi_Unit(U), P);
    }
  }
}

boolean CanUnitAttack(Unit U1, Unit U2)
// true jika unit U1 dapat menyerang unit U2
{
  POINT P1 = Lokasi_Unit(U1), P2 = Lokasi_Unit(U2);

  if(Absis(P1) != Absis(P2) && Ordinat(P1) != Ordinat(P2) || !Kesempatan_Serangan(U1)){
    return false;
  }
  else {
    return true;
  }
}
