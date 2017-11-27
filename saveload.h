#include "player.h"
#include <time.h>
#include <stdio.h>
#include <string.h>

/* KAMUS */
int M, N;
Player P1, P2;
ListVil LVill;

void Save(int M, int N, Player P1, Player P2, ListVil LVill);
/* Menyimpan data game pada file "saved.txt" */

void Load(int *M, int *N, Player *P1, Player *P2, ListVil *LVill);
/* Meload data game yang sudah pernah tersimpa dari file "saved.txt" */