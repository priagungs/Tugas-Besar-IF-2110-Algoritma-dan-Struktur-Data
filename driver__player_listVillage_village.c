#include <stdio.h>
#include "player.h"
#include <string.h>

Player P;
Village V;
POINT Pt;
Unit U;
char s[100];
int x = 1,y = 1,uang,xx,yy;

// cara compile : gcc .\driver__player_listVillage.c .\listvillage.c .\player.c .\village.c .\unit.c .\point.c .\listofunit.c -o a
// run : ./a
int main(){
	//Driver atribut player
	Make_Player(&P,x);
	printf("Anda bermain sebagai player %d.\n",x);
	printf("Informasi player default :\n");
	printf("Gold : %d | Income : %d | Upkeep : %d\n",Gold(P),Income(P),Upkeep(P));
	printf("\nMasukkan jumlah gold yang ingin anda tambahkan : ");
	scanf("%d",&x);
	printf("Gold sebelum : %d\n",Gold(P) );
	Update_Gold(&P,x);
	printf("Gold sesudah : %d\n",Gold(P) );
	printf("\nMasukkan jumlah Income yang ingin anda tambahkan : ");
	scanf("%d",&x);
	printf("Income sebelum : %d\n",Income(P) );
	Update_Income(&P,x);
	printf("Income sesudah : %d\n",Income(P) );
	printf("\nMasukkan jumlah Upkeep yang ingin anda tambahkan : ");
	scanf("%d",&x);
	printf("Upkeep sebelum : %d\n",Upkeep(P) );
	Update_Upkeep(&P,x);
	printf("Upkeep sesudah : %d\n",Upkeep(P) );
	
	//Driver listVillage dan village
	
	printf("\nMasukkan koordinat village pertama yang ingin anda buat : ");
	scanf("%d%d",&x,&y);
	printf("Masukkan jumlah income village : ");
	scanf("%d",&uang);
	MakeVillage(&V,x,y,uang);
	Add_Village(&P,V);

	printf("Masukkan koordinat village kedua yang ingin anda buat : ");
	scanf("%d%d",&x,&y);
	printf("Masukkan jumlah income village : ");
	scanf("%d",&uang);
	MakeVillage(&V,x,y,uang);
	Add_Village(&P,V);
	
	printf("\nDaftar villages yang anda punya : \n");
	PrintListVillage(VillageList(P));

	printf("\nMasukkan koordinat village yang ingin anda hapus dari list : ");
	scanf("%d%d",&xx,&yy);
	if(xx == x && yy == y){
		Del_Village(&P,V);
	}
	else{
		V = InfoVillage(NextVillage(FirstVillage(VillageList(P))));
		Del_Village(&P,V);
	}
	printf("\nDaftar villages yang anda punya setelah penghapusan : \n");
	PrintListVillage(VillageList(P));

	// listUnit di player
	printf("\nMasukkan koordinat Unit pertama yang ingin anda buat : ");
	scanf("%d%d",&x,&y);
	printf("Masukkan jenis unit : ");
	scanf("%s",s);
	Pt = MakePOINT(x,y);
	U = CreateUnit(s,Pt);
	if(!strcmp(s,"King"))
		Add_Unit_Last(&P,U);
	else
		Add_Unit_First(&P,U);
	printf("\nMasukkan koordinat Unit kedua yang ingin anda buat : ");
	scanf("%d%d",&x,&y);
	printf("Masukkan jenis unit : ");
	scanf("%s",s);
	Pt = MakePOINT(x,y);
	U = CreateUnit(s,Pt);
	if(!strcmp(s,"King"))
		Add_Unit_Last(&P,U);
	else
		Add_Unit_First(&P,U);
	printf("\nDaftar unit yang anda punya : \n");
	PrintListUnit(UnitList(P));
	printf("\nMasukkan koordinat unit yang ingin anda hapus dari list : ");
	scanf("%d%d",&xx,&yy);
	Pt = MakePOINT(xx,yy);
	if(xx == x && y == yy )
		Del_Unit(&P,U);
	else{
		U = InfoUnit(NextUnit(FirstUnit(UnitList(P))));
		Del_Unit(&P,U);
	}
	printf("Daftar unit yang anda punya setelah penghapusan : \n");
	PrintListUnit(UnitList(P));
}