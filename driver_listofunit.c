/* Driver listofunit */

#include "listofunit.h"
#include <stdio.h>

int main(){
	/* KAMUS */
	Unit U;
	ListUnit LUnit;
	POINT Loc;
	int n;
	addressUnit P;

	/* ALGORITMA */
	CreateEmptyUnit(&LUnit);

	printf("Daftar unit saat ini:\n");
	if (!IsEmptyUnit(LUnit)) {
		PrintListUnit(LUnit);
	} else {
		printf("Tidak ada unit apapun\n");
	}

	printf("Masukkan lokasi unit King: \n");
	BacaPOINT(&Loc);
	U = CreateUnit("King",Loc);
	InsUnitFirst(&LUnit,U);

	printf("Masukkan lokasi unit Archer: \n");
	BacaPOINT(&Loc);
	U = CreateUnit("Archer",Loc);
	InsUnitLast(&LUnit,U);

	printf("Masukkan lokasi unit Swordsman: \n");
	BacaPOINT(&Loc);
	U = CreateUnit("Swordsman",Loc);
	InsUnitLast(&LUnit,U);

	printf("Masukkan lokasi unit Swordsman 2: \n");
	BacaPOINT(&Loc);
	U = CreateUnit("Swordsman",Loc);
	InsUnitLast(&LUnit,U);

	printf("Daftar unit saat ini:\n");
	if (!IsEmptyUnit(LUnit)) {
		PrintListUnit(LUnit);
	} else {
		printf("Tidak ada unit apapun\n");
	}

	printf("Hapus unit yang sedang berada di: \n");
	BacaPOINT(&Loc);
	printf("%s akan dihapus.\n", Jenis_Unit(InfoUnit(SearchKoordinatUnit(LUnit, Loc))));
	DelKoordinatUnit(&LUnit,Loc,&U);

	/*Mengubah nilai MP unit pertama dan attack chance unit berikutnya */
	P = FirstUnit(LUnit);
	Movement_Point(InfoUnit(P)) = 0;
	Kesempatan_Serangan(InfoUnit(NextUnit(P))) = false;

	printf("Daftar unit saat ini:\n");
	if (!IsEmptyUnit(LUnit)) {
		PrintListUnit(LUnit);
	} else {
		printf("Tidak ada unit apapun\n");
	}

	printf("Unit yang sedang ada di indeks ke- (masukkan integer)\n");
	scanf("%d",&n);
	PrintUnit(SearchNomor(LUnit,n));

	printf("Mereset movement point dan attack chance setiap unit.\n");
	ResetMovementPoint(&LUnit);
	ResetAttackChance(&LUnit);
	printf("Daftar unit saat ini:\n");
	if (!IsEmptyUnit(LUnit)) {
		PrintListUnit(LUnit);
	} else {
		printf("Tidak ada unit apapun\n");
	}

	printf("Menghapus unit terakhir.\n");
	DelUnitLast(&LUnit,&U);

	if (!IsEmptyUnit(LUnit)) {
		PrintListUnit(LUnit);
	} else {
		printf("Tidak ada unit apapun\n");
	}

	printf("Menghapus unit pertama (king).\n");
	DelUnitFirst(&LUnit,&U);

	if (!IsKingDead(LUnit)) {
		PrintListUnit(LUnit);
	} else {
		printf("Player sudah mati karena king sudah mati.\n");
	}
	return 0;
}