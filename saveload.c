#include "saveload.h"

void Save(int M, int N, Player P1, Player P2, ListVil LVillages){
/* Menyimpan data game pada file "saved.txt" */
	/* KAMUS LOKAL */
	FILE *fsave;
	char filename[100];
	printf("File name : ");
	scanf("%s", filename);
	fsave = fopen (filename,"w");

	/* ALGORITMA */

	/* Save ukuran matriks */
	fprintf(fsave, "SIZE\n");
	fprintf(fsave, "%d %d\n", M, N);

	/* Save list villages */
	fprintf(fsave, "LISTOFVILLS\n");
	if (!IsEmptyVil(LVillages)) {
		addressVillage Pv = FirstVillage(LVillages);
		fprintf(fsave, "---\n");
		fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
		fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		while(NextVillage(Pv) != FirstVillage(LVillages)){
			Pv = NextVillage(Pv);
			fprintf(fsave, "---\n");
			fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
			fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		}
	}

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
		while(NextVillage(Pv) != FirstVillage(VillageList(P1))){
			Pv = NextVillage(Pv);
			fprintf(fsave, "---\n");
			fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
			fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		}
	}

	/* Daftar Unit */
	fprintf(fsave, "UNIT(S)\n");
	addressUnit Pu = FirstUnit(UnitList(P1));
	fprintf(fsave, "---\n");
	fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
	fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
	fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));;
	fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
	fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	while(NextUnit(Pu) != FirstUnit(UnitList(P1))) {
		Pu = NextUnit(Pu);
		fprintf(fsave, "---\n");
		fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
		fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
		fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	}

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
		while(NextVillage(Pv) != FirstVillage(VillageList(P2))){
			Pv = NextVillage(Pv);
			fprintf(fsave, "---\n");
			fprintf(fsave, "%d %d\n", PosX(InfoVillage(Pv)), PosY(InfoVillage(Pv)));
			fprintf(fsave, "%d\n", IncomeVil(InfoVillage(Pv)));
		}
	}

	/* Daftar Unit */
	fprintf(fsave, "UNIT(S)\n");
	Pu = FirstUnit(UnitList(P2));
	fprintf(fsave, "---\n");
	fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
	fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
	fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));
	fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
	fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	while(NextUnit(Pu) != FirstUnit(UnitList(P2))){
		Pu = NextUnit(Pu);
		fprintf(fsave, "---\n");
		fprintf(fsave, "%s\n", Jenis_Unit(InfoUnit(Pu)));
		fprintf(fsave, "%d %d\n", Absis(Lokasi_Unit(InfoUnit(Pu))), Ordinat(Lokasi_Unit(InfoUnit(Pu))));
		fprintf(fsave, "%d\n", Health(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Movement_Point(InfoUnit(Pu)));
		fprintf(fsave, "%d\n", Kesempatan_Serangan(InfoUnit(Pu)));
	}
	fprintf(fsave, "END\n");

	/* Save current time */
	time_t CurrTime;
	char* CTString;
	CurrTime = time(NULL);
	CTString = ctime(&CurrTime);
	fprintf(fsave, "Last saved on %s.\n", CTString);

	fclose(fsave);
	printf("The Game has been successfully saved.\n");
}

void Load(int *M, int *N, Player *P1, Player *P2, ListVil *LVillages){
/* Meload data game yang sudah pernah tersimpa dari file "saved.txt" */
	/* KAMUS LOKAL */


	FILE *fsave;
	char filename[100];
	printf("File name : ");
	scanf("%s", filename);
	fsave = fopen (filename,"r");
	char Temp[200];

	int gold, income, upkeep, warna;

	Village V;
	int x, y, inc;

	Unit U;
	char Jenis[100];
	int i, j;

	/* ALGORITMA */
	/* Abaikan baris paling atas */
	/*fscanf(fsave, "%s", &Temp);
	while (strcmp(Temp,"SIZE")!=0){
		fscanf(fsave, "%s", &Temp);
	}*/
	/* Load ukuran matriks */
	fscanf(fsave, "%s", Temp);
	fscanf(fsave, "%d %d", M, N);
	printf("Map size loaded.\n");

	/* Load Villages */
	fscanf(fsave, "%s", Temp);
	fscanf(fsave, "%s", Temp);
	CreateEmptyVil(LVillages);
	while (strcmp(Temp,"PLAYER1")!=0){
		fscanf(fsave, "%d %d", &x, &y);
		fscanf(fsave, "%d", &inc);
		MakeVillage(&V, x, y, inc);
		InsVLastVil(LVillages, V);
		fscanf(fsave, "%s", Temp);
	}
	printf("Bunch of villages loaded.\n");

	/* LOAD PLAYER 1 */
	/* Properti umum */
	fscanf(fsave, "%d", &gold);
	fscanf(fsave, "%d", &income);
	fscanf(fsave, "%d", &upkeep);
	fscanf(fsave, "%d", &warna);

	Gold(*P1) = gold;
	Income(*P1) = income;
	Upkeep(*P1) = upkeep;
	Warna(*P1) = warna;

	printf("General properties of Player 1 loaded.\n");
	/* Daftar village */
	fscanf(fsave, "%s", Temp);
	fscanf(fsave, "%s", Temp);
	CreateEmptyVil(&VillageList(*P1));
	while (strcmp(Temp,"UNIT(S)")!=0){
		fscanf(fsave, "%d %d", &x, &y);
		fscanf(fsave, "%d", &inc);
		MakeVillage(&V, x, y, inc);
		Add_Village(P1, V);
		fscanf(fsave, "%s", Temp);
	}
	printf("Villages of Player 1 loaded.\n");
	/* Daftar Unit */
	fscanf(fsave, "%s", Temp);
	CreateEmptyUnit(&UnitList(*P1));
	while (strcmp(Temp,"PLAYER2")!=0){
		fscanf(fsave, "%s", Jenis);
		fscanf(fsave, "%d %d", &i, &j);
		U = CreateUnit(Jenis,MakePOINT(i,j));
		fscanf(fsave, "%d", &Health(U));
		fscanf(fsave, "%d", &Movement_Point(U));
		fscanf(fsave, "%d", &Kesempatan_Serangan(U));
		Add_Unit_Last(P1,U);
		fscanf(fsave, "%s", Temp);
	}
	printf("Units of Player 1 loaded.\n");
	printf("Player 1 has been successfully loaded.\n");
	/* LOAD PLAYER 2 */
	/* Properti umum */
	fscanf(fsave, "%d", &gold);
	fscanf(fsave, "%d", &income);
	fscanf(fsave, "%d", &upkeep);
	fscanf(fsave, "%d", &warna);

	Gold(*P2) = gold;
	Income(*P2) = income;
	Upkeep(*P2) = upkeep;
	Warna(*P2) = warna;

	printf("General properties of Player 2 loaded.\n");
	/* Daftar village */
	fscanf(fsave, "%s", Temp);
	fscanf(fsave, "%s", Temp);
	CreateEmptyVil(&VillageList(*P2));
	while (strcmp(Temp,"UNIT(S)")!=0){
		fscanf(fsave, "%d %d", &x, &y);
		fscanf(fsave, "%d", &inc);
		MakeVillage(&V, x, y, inc);
		Add_Village(P2, V);
		fscanf(fsave, "%s", Temp);
	}
	printf("Villages of Player 2 loaded.\n");
	/* Daftar Unit */
	fscanf(fsave, "%s", Temp);
	CreateEmptyUnit(&UnitList(*P2));
	while (strcmp(Temp,"END")!=0){
		fscanf(fsave, "%s", Jenis);
		fscanf(fsave, "%d %d", &i, &j);
		U = CreateUnit(Jenis,MakePOINT(i,j));
		fscanf(fsave, "%d", &Health(U));
		fscanf(fsave, "%d", &Movement_Point(U));
		fscanf(fsave, "%d", &Kesempatan_Serangan(U));
		Add_Unit_Last(P2,U);
		fscanf(fsave, "%s", Temp);
	}
	printf("Units of Player 2 loaded.\n");
	printf("Player 2 has been successfully loaded.\n");
	printf("The game has been successfully loaded.\n");
	fclose(fsave);
}
