/* File : listofunit.c */
/* ADT List Of Unit */
/* 14 November 2017 */

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
/* Mengirimkan addressUnit hasil alokasi sebuah unit */
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

/****************** PENCARIAN SEBUAH unit LIST ******************/
addressUnit SearchKoordinatUnit (ListUnit L, POINT Koordinat){
/* Searching Unit X yang memiliki posisi di Koordinat */
/* Jika ketemu, makam mengirimkan addressUnit dari Unit X tsb */
/* Jika tidak, mengirimkan Nil */
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
/*** PENAMBAHAN UNIT ***/
void InsUnitFirst (ListUnit *L, Unit X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah unit dan */
/* menambahkan unit X sebagai unit pertama pada list jika alokasi berhasil */
	addressUnit P;
	P = AlokasiUnit(X);
	if (P != Nil) {
		InsertFirstUnit(L,P);
	}
}
void InsUnitLast (ListUnit *L, Unit X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah unit dan */
/* menambahkan unit X pada list di akhir: unit terakhir yang baru */
/* jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
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

/*** PENGHAPUSAN unit ***/
void DelUnitFirst (ListUnit *L, Unit * X){
/* I.S. List L tidak kosong  */
/* F.S. unit pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat unit pertama di-dealokasi */
	addressUnit P;
	DelFirstUnit(L,&P);
	*X = InfoUnit(P);
	DealokasiUnit(P);
}
void DelUnitLast (ListUnit *L, Unit * X){
/* I.S. list tidak kosong */
/* F.S. unit terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat unit terakhir di-dealokasi */
	addressUnit P;
	DelLastUnit(L,&P);
	*X = InfoUnit(P);
	DealokasiUnit(P);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN unit BERDASARKAN ALAMAT ***/
void InsertFirstUnit (ListUnit *L, addressUnit P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan unit ber-addressUnit P sebagai unit pertama */
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
/* F.S. P ditambahkan sebagai unit terakhir yang baru */
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
/* I.S. Prec pastilah unit list dan bukan unit terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai unit sesudah unit beralamat Prec */
	NextUnit(P) = NextUnit(Prec);
	NextUnit(Prec) = P;
}

/*** PENGHAPUSAN SEBUAH unit ***/
void DelFirstUnit (ListUnit *L, addressUnit *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat unit pertama list sebelum penghapusan */
/*      unit list berkurang satu (mungkin menjadi kosong) */
/* First unitt yg baru adalah suksesor unit pertama yang lama */
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
/* F.S. P adalah alamat unit terakhir list sebelum penghapusan  */
/*      unit list berkurang satu (mungkin menjadi kosong) */
/* Last unitt baru adalah predesesor unit pertama yg lama, */
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
/*      Pdel adalah alamat unit list yang dihapus  */
	*Pdel = NextUnit(Prec);
	NextUnit(Prec) = NextUnit(*Pdel);
	NextUnit(*Pdel) = Nil;
}
void DelKoordinatUnit (ListUnit *L, POINT Koordinat, Unit *X){
/* I.S. Sembarang */
/* F.S. Jika ada unit list beraddressUnit P, dengan lokasi Koordinat  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada unit list dengan lokasi Koordinat, maka list tetap */
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
/* Menuliskan ke layar daftar unit yang dimiliki L */
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
/* Mengirimkan Unit yang memiliki indeks nomor */
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
/* Mereset movement point seluruh unit pada ListUnit L menjadi Max */
	addressUnit P = FirstUnit(*L);
	if(P != Nil){
		do {
			Movement_Point(InfoUnit(P)) = Max_Movement_Point(InfoUnit(P));
			P = NextUnit(P);
		} while(P != FirstUnit(*L));

	}
}

boolean IsKingDead(ListUnit L){
/* Mengirimkan nilai true jika Unit King
   yang berada pada ListUnit L sudah tidak ada/mati */
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
/* Mereset attack chance seluruh unit pada ListUnit L nenjadi true */
	addressUnit P = FirstUnit(*L);
	if(P != Nil){
		do{
			Kesempatan_Serangan(InfoUnit(P)) = true;
		}while(P != FirstUnit(*L));
	}
}
