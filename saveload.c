#include "saveload.h"

void Save(int M, int N, Player P1, Player P2){
	FILE *fsave;
	fsave = fopen ("saved.txt","w");

	/* Save ukuran matriks */
	fprintf(fsave, "%d %d\n", M, N);

	/* Save Player 1 */
	fprintf(fsave, "PLAYER1\n");

	/* Properti umum */
	fprintf(fsave, "%d\n", Gold(P1));
	fprintf(fsave, "%d\n", Income(P1));
	fprintf(fsave, "%d\n", Upkeep(P1));
	fprintf(fsave, "%d\n", Warna(P1));

	/* Daftar village */
	fprintf(fsave, "VILLAGE(S)\n");
	if (!IsEmptyVil(VillageList(P1))) {
		addressVillage Pv = FirstVillage(VillageList(P1));
		fprintf(fsave, "---\n");
		fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
		fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		while(NextVillage(Pv) != FirstVillage(L)){
			P = NextVillage(Pv);
			fprintf(fsave, "---\n");
			fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
			fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		}
	}

	/* Daftar Unit */
	fprintf(fsave, "UNIT(S)\n");
	addressUnit Pu = FirstUnit(VillageList(P1));
	fprintf(fsave, "---\n");
	fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
	fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
	fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));;
	fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
	fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	while(NextUnit(Pu) != FirstUnit(Pu)){
		Pu = NextUnit(Pu);
		fprintf(fsave, "---\n");
		fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
		fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
		fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	}
	fprintf(fsave, "ENDOFP1\n");

	/* Save Player 2 */
	fprintf(fsave, "PLAYER2\n");

	/* Properti umum */
	fprintf(fsave, "%d\n", Gold(P2));
	fprintf(fsave, "%d\n", Income(P2));
	fprintf(fsave, "%d\n", Upkeep(P2));
	fprintf(fsave, "%d\n", Warna(P2));

	/* Daftar village */
	fprintf(fsave, "VILLAGE(S)\n");
	if (!IsEmptyVil(VillageList(P2))) {
		addressVillage Pv = FirstVillage(VillageList(P2));
		fprintf(fsave, "---\n");
		fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
		fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		while(NextVillage(Pv) != FirstVillage(L)){
			P = NextVillage(Pv);
			fprintf(fsave, "---\n");
			fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
			fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		}
	}

	/* Daftar Unit */
	fprintf(fsave, "UNIT(S)\n");
	addressUnit Pu = FirstUnit(VillageList(P2));
	fprintf(fsave, "---\n");
	fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
	fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
	fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));;
	fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
	fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	while(NextUnit(Pu) != FirstUnit(Pu)){
		Pu = NextUnit(Pu);
		fprintf(fsave, "---\n");
		fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
		fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
		fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	}
	fprintf(fsave, "ENDOFP2\n");
	fclose(fsave);
}

void Load(int *M, int *N, Player *P1, Player *P2){
	FILE *fsave;
	fsave = fopen ("saved.txt","r");
	char Temp[200];

	int gold, income, upkeep, warna;

	Village V;
	int x, y, inc;

	Unit U;
	char Jenis[100];
	int i, j;

	/* Load ukuran matriks */
	fscanf(fsave, "%d %d", &M, &N);

	/* LOAD PLAYER 1 */
	fscanf(fsave, "%s", &Temp);

	/* Properti umum */
	fscanf(fsave, "%d", &gold);
	fscanf(fsave, "%d", &income);
	fscanf(fsave, "%d", &upkeep);
	fscanf(fsave, "%d", &warna);

	Make_Player(P1, warna);
	Update_Gold(P1, gold);
	Update_Income(P1, income);
	Update_Upkeep(P1, upkeep);

	/* Daftar village */
	fscanf(fsave, "%s", &Temp);
	fscanf(fsave, "%s", &Temp);

	if (strcmp(Temp,"UNIT(S)"!=0)){
		fscanf(fsave, "%d %d", &x, &y);
		fscanf(fsave, "%d", &inc);
		MakeVillage(&V, x, y, inc);
		Add_Village(P1, V);
		fscanf(fsave, "%s", &Temp);
		while(strcmp(Temp,"UNIT(S)"!=0)){
			fscanf(fsave, "%d %d", &x, &y);
			fscanf(fsave, "%d", &inc);
			MakeVillage(&V, x, y, inc);
			Add_Village(P1, V);
			fscanf(fsave, "%s", &Temp);
		}
	}
	/* Daftar Unit */
	fscanf(fsave, "%s", &Temp);
	fscanf(fsave, "%s", &Jenis);
	fscanf(fsave, "%d %d", &i, &j);
	U = CreateUnit(Jenis,MakePOINT(i,j));
	fscanf(fsave, "%d", &Health(U));
	fscanf(fsave, "%d", &Movement_Point(U));
	fscanf(fsave, "%d", &Kesempatan_Serangan(U));
	Add_Unit(P1,U);
	fscanf(fsave, "%s", &Temp)
	while (strcmp(Temp,"ENDOFP1"!=0)){
		fscanf(fsave, "%s", &Temp);
		fscanf(fsave, "%s", &Jenis);
		fscanf(fsave, "%d %d", &i, &j);
		U = CreateUnit(Jenis,MakePOINT(i,j));
		fscanf(fsave, "%d", &Health(U));
		fscanf(fsave, "%d", &Movement_Point(U));
		fscanf(fsave, "%d", &Kesempatan_Serangan(U));
		Add_Unit(P1,U);
		fscanf(fsave, "%s", &Temp)
	}

	/* LOAD PLAYER 2 */
	fscanf(fsave, "%s", &Temp);

	/* Properti umum */
	fscanf(fsave, "%d", &gold);
	fscanf(fsave, "%d", &income);
	fscanf(fsave, "%d", &upkeep);
	fscanf(fsave, "%d", &warna);

	Make_Player(P2, warna);
	Update_Gold(P2, gold);
	Update_Income(P2, income);
	Update_Upkeep(P2, upkeep);

	/* Daftar village */
	fscanf(fsave, "%s", &Temp);
	fscanf(fsave, "%s", &Temp);

	if (strcmp(Temp,"UNIT(S)"!=0)){
		fscanf(fsave, "%d %d", &x, &y);
		fscanf(fsave, "%d", &inc);
		MakeVillage(&V, x, y, inc);
		Add_Village(P2, V);
		fscanf(fsave, "%s", &Temp);
		while(strcmp(Temp,"UNIT(S)"!=0)){
			fscanf(fsave, "%d %d", &x, &y);
			fscanf(fsave, "%d", &inc);
			MakeVillage(&V, x, y, inc);
			Add_Village(P2, V);
			fscanf(fsave, "%s", &Temp);
		}
	}
	/* Daftar Unit */
	fscanf(fsave, "%s", &Temp);
	fscanf(fsave, "%s", &Jenis);
	fscanf(fsave, "%d %d", &i, &j);
	U = CreateUnit(Jenis,MakePOINT(i,j));
	fscanf(fsave, "%d", &Health(U));
	fscanf(fsave, "%d", &Movement_Point(U));
	fscanf(fsave, "%d", &Kesempatan_Serangan(U));
	Add_Unit(P2,U);
	fscanf(fsave, "%s", &Temp)
	while (strcmp(Temp,"ENDOFP2"!=0)){
		fscanf(fsave, "%s", &Temp);
		fscanf(fsave, "%s", &Jenis);
		fscanf(fsave, "%d %d", &i, &j);
		U = CreateUnit(Jenis,MakePOINT(i,j));
		fscanf(fsave, "%d", &Health(U));
		fscanf(fsave, "%d", &Movement_Point(U));
		fscanf(fsave, "%d", &Kesempatan_Serangan(U));
		Add_Unit(P2,U);
		fscanf(fsave, "%s", &Temp)
	}
	fclose(fsave);
}