/* File : listsirkuler.c */
/* 13516017
 * Muhammad Nurraihan Naufal
 * 25 Oktober 2017
 * ADT List Sirkuler */

#include "listofunit.h"
#include "unit.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyUnit (ListUnit L){
/* Mengirim true jika list kosong. Lihat definisi di atas. */
	return (FirstUnit(L) == Nil);
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyUnit (ListUnit *L){
/* I.S. L sembarang             */
/* F.S. Terbentuk list kosong. Lihat definisi di atas. */
	FirstUnit(*L) = Nil;
}

/****************** Manajemen Memori ******************/
addressUnit AlokasiUnit (Unit X){
/* Mengirimkan addressUnit hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addressUnit tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
	addressUnit P;
	P = (addressUnit) malloc (sizeof(ElmtListUnit));
	if (P == Nil) {
		return Nil;
	}
	else {
		Jenis_Unit(InfoUnit(P)) = Jenis_Unit(X);
		Max_Health(InfoUnit(P)) = Max_Health(X);
		Health(InfoUnit(P)) = Health(X);
		Attack_Damage(InfoUnit(P)) = Attack_Damage(X);
		Max_Movement_Point(InfoUnit(P)) = Max_Movement_Point(X);
		Movement_Point(InfoUnit(P)) = Movement_Point(X);
		Tipe_Serangan(InfoUnit(P)) = Tipe_Serangan(X);
		Kesempatan_Serangan(InfoUnit(P)) = Kesempatan_Serangan(X);
		Absis(Lokasi_Unit(InfoUnit(P))) = Absis(Lokasi_Unit(X));
		Ordinat(Lokasi_Unit(InfoUnit(P))) = Ordinat(Lokasi_Unit(X));
		Harga_Unit(InfoUnit(P)) = Harga_Unit(X);
		NextUnit(P) = Nil;
		return P;
	}
}

void DealokasiUnit (addressUnit P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addressUnit P */
	free(P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressUnit SearchKoordinatUnit (ListUnit L, POINT Koordinat){
	addressUnit P;
	P = FirstUnit(L);
	if(P != Nil){
		do{
			if(((Absis(Lokasi_Unit(InfoUnit(P))) == Absis(Koordinat)) && (Ordinat(Lokasi_Unit(InfoUnit(P))) == Ordinat(Koordinat)))){
				return P;
			}
			P = NextUnit(P);
		} while (P != FirstUnit(L));
	}
	return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsUnitFirst (ListUnit *L, Unit X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
	addressUnit P;
	P = AlokasiUnit(X);
	if (P != Nil) {
		InsertFirstUnit(L,P);
	}
}
void InsUnitLast (ListUnit *L, Unit X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
	addressUnit P;
	if (IsEmptyUnit(*L)){
		InsUnitFirst(L,X);
	} else {
		P = AlokasiUnit(X);
		if (P != Nil) {
			InsertLastUnit(L,P);
		}
	}
}

/*** PENGHAPUSAN ELEMEN ***/
void DelUnitFirst (ListUnit *L, Unit * X){
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-dealokasi */
	addressUnit P;
	DelFirstUnit(L,&P);
	*X = InfoUnit(P);
	DealokasiUnit(P);
}
void DelUnitLast (ListUnit *L, Unit * X){
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-dealokasi */
	addressUnit P;
	DelLastUnit(L,&P);
	*X = InfoUnit(P);
	DealokasiUnit(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstUnit (ListUnit *L, addressUnit P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addressUnit P sebagai elemen pertama */
	addressUnit Last;
	if (IsEmptyUnit(*L)){
		NextUnit(P) = P;
	} else {
		Last = FirstUnit(*L);
		while (NextUnit(Last) != FirstUnit(*L)) {
			Last = NextUnit(Last);
		}
		NextUnit(P) = FirstUnit(*L);
		NextUnit(Last) = P;
	}
	FirstUnit(*L) = P;
}
void InsertLastUnit (ListUnit *L, addressUnit P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
	addressUnit Last;
	if (IsEmptyUnit(*L)) {
		InsertFirstUnit(L,P);
	} else {
		Last = FirstUnit(*L);
		while (NextUnit(Last) != FirstUnit(*L)) {
			Last = NextUnit(Last);
		}
		InsertAfterUnit(L,P,Last);
	}
}
void InsertAfterUnit (ListUnit *L, addressUnit P, addressUnit Prec){
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
	NextUnit(P) = NextUnit(Prec);
	NextUnit(Prec) = P;
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstUnit (ListUnit *L, addressUnit *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	addressUnit Last;
	*P = FirstUnit(*L);
	if (NextUnit(*P) == FirstUnit(*L)){
		CreateEmptyUnit(L);
	} else {
		Last = FirstUnit(*L);
		while (NextUnit(Last) != FirstUnit(*L)) {
			Last = NextUnit(Last);
		}
		FirstUnit(*L) = NextUnit(FirstUnit(*L));
		NextUnit(Last) = FirstUnit(*L);
	}
	NextUnit(*P) = Nil;
}
void DelLastUnit (ListUnit *L, addressUnit *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen pertama yg lama, */
/* jika ada */
	addressUnit Last, PrecLast;
	Last = NextUnit(FirstUnit(*L));
	PrecLast = FirstUnit(*L);
	while (NextUnit(Last) != FirstUnit(*L)) {
		PrecLast = Last;
		Last = NextUnit(Last);
	}
	*P = Last;
	if (Last == PrecLast) {
		CreateEmptyUnit(L);
	} else {
		NextUnit(PrecLast) = FirstUnit(*L);
	}
}
void DelAfterUnit (ListUnit *L, addressUnit *Pdel, addressUnit Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
	*Pdel = NextUnit(Prec);
	NextUnit(Prec) = NextUnit(*Pdel);
	NextUnit(*Pdel) = Nil;
}
void DelKoordinatUnit (ListUnit *L, POINT Koordinat, Unit *X){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddressUnit P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
	addressUnit P, Prec;
	if (!IsEmptyUnit(*L)) {
		P = SearchKoordinatUnit(*L,Koordinat);
		if (P != Nil) {
			if (P == FirstUnit(*L)) {
				*X = InfoUnit(P);
				DelFirstUnit(L,&P);
			} else {
				Prec = FirstUnit(*L);
				while (NextUnit(Prec) != P) {
					Prec = NextUnit(Prec);
				}
				*X = InfoUnit(NextUnit(Prec));
				DelAfterUnit(L,&P,Prec);
				DealokasiUnit(P);
			}
		}
	}
}

void PrintListUnit(ListUnit L){
	int cnt = 1;
	if(!IsEmptyUnit(L)){
		addressUnit P = FirstUnit(L);
		while(NextUnit(P) != FirstUnit(L)){
			printf("%d. %s  |",cnt, Jenis_Unit(InfoUnit(P)));
			PrintUnit(InfoUnit(P));
			P = NextUnit(P);
			cnt++;
			printf("\n");
		}
		printf("%d. %s  |", cnt, Jenis_Unit(InfoUnit(P)));
		PrintUnit(InfoUnit(P));
		printf("\n");
	}
}


Unit SearchNomor( ListUnit L, int nomor){
	addressUnit P;
	P = FirstUnit(L);
	nomor --;
	while(nomor != 0){
		P = NextUnit(P);
		nomor--;
	}
	return InfoUnit(P);
}

void ResetMovementPoint(ListUnit *L){
	addressUnit P = FirstUnit(*L);
	if(P != Nil){
		do {
			Movement_Point(InfoUnit(P)) = Max_Movement_Point(InfoUnit(P));
			P = NextUnit(P);
		} while(P != FirstUnit(*L));

	}
}

boolean IsKingDead(ListUnit L){
	addressUnit P = FirstUnit(L);
	if(!IsEmptyUnit(L)){
		do{
			if(!strcmp(Jenis_Unit(InfoUnit(P)), "King")){
				return false;
			}
			P = NextUnit(P);
		}while(P != FirstUnit(L));
	}
	return true;
}

void ResetAttackChance(ListUnit *L){
	addressUnit P = FirstUnit(*L);
	if(P != Nil){
		do{
			Kesempatan_Serangan(InfoUnit(P)) = true;
		}while(P != FirstUnit(*L));
	}
}
