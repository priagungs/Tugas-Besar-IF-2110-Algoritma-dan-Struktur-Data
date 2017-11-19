#include "unit.h"
#include <stdio.h>
#include <string.h>
#include "boolean.h"

int main(){
  printf("Masukan posisi Unit 1 : ");
  float x,y;
  scanf("%f %f", &x, &y);
  POINT P1 = MakePOINT(x,y);

  printf("Masukan jenis Unit 1 : ");
  char s[100];
  scanf("%s", s);
  printf("%s", s);
  Unit U1 = CreateUnit(s, P1);

  printf("Masukan posisi P2 : ");
  scanf("%f %f", &x, &y);
  POINT P2 = MakePOINT(x,y);

  printf("Masukan jenis Unit 2 : ");
  scanf("%s", s);
  Unit U2 = CreateUnit(s, P1);

  printf("Geser Unit 1 ke : ");
  scanf("%f %f", &x, &y);
  GeserUnit(&U1, MakePOINT(x,y));

  printf("Serang Unit 2...!!\n");
  Attack(&U1, &U2);
}
