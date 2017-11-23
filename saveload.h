#include "player.h"
#include <stdio.h>
#include <string.h>

int M, N;
Player P1, P2;
ListVil LVill;

void Save(int M, int N, Player P1, Player P2, ListVil LVill);

void Load(int *M, int *N, Player *P1, Player *P2, ListVil *LVill);

void LoadWMesinKata(int *M, int *N, Player *P1, Player *P2, ListVil *LVill);