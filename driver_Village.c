#include <stdio.h>
#include "village.h"

Village V1, V2;
int x,y,money;

int main(){
	printf("Masukkan koordinat village pertama : ");
	scanf("%d%d",&x,&y);
	printf("Masukkan nilai income village pertama : ");
	scanf("%d",&money);
	MakeVillage(&V1,x,y,money);

	printf("Masukkan koordinat village kedua : ");
	scanf("%d%d",&x,&y);
	printf("Masukkan nilai income village kedua : ");
	scanf("%d",&money);
	MakeVillage(&V2,x,y,money);

	printf("\nData village 1\n");
	PrintVillage(V1);
	printf("\nData village 2\n");
	PrintVillage(V2);

}	