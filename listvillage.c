/* File: listvillage.c */
/* Tanggal: 11 November 2017 */
/* made by : rwk03 */

#include "boolean.h"
#include "listvillage.h"
#include "stdlib.h"
#include "stdio.h"

/* PROTOTYPE */
/****************** TEST ListVil KOSONG ******************/
boolean IsEmptyVil (ListVil L)
{
	return FirstVillage(L) == Nil;
}

/****************** PEMBUATAN ListVil KOSONG ******************/
void CreateEmptyVil (ListVil *L)
{
	FirstVillage(*L) = Nil;
}
/****************** Manajemen Memori ******************/
addressVillage AlokasiVil (Village X)
{
	addressVillage P = (addressVillage) malloc(1*sizeof(ElmtListVil));
	if (P != Nil) {
    	InfoVillage(P) = X;
    	NextVillage(P) = Nil;
    	return P;
    }
    else
    	return Nil;
}

void DealokasiVil (addressVillage P)
{
	free(P);
}
/****************** PENCARIAN SEBUAH ELEMEN ListVil ******************/
addressVillage SearchVil (ListVil L, Village X)
{
	if (IsEmptyVil(L))
		return Nil;
	else{
		addressVillage P = FirstVillage(L);
		while ((NextVillage(P) != FirstVillage(L)) && (!IsVillageSame(InfoVillage(P),X)))
			P = NextVillage(P);  /* NextVil(P) = FirstVil(L) or InfoVil(P) = X */
		if (IsVillageSame(InfoVillage(P),X)) return P;
		else return Nil;
	}
}

addressVillage SearchKoordinatVil (ListVil L, POINT Koordinat){
	addressVillage P;
	boolean found = false;
	if (IsEmptyVil(L)) {
		return Nil;
	} else {
		P = FirstVillage(L);
		while (NextVillage(P) != FirstVillage(L) && !found) {
			if((PosX(InfoVillage(P))) == Absis(Koordinat) && PosY(InfoVillage(P)) == Ordinat(Koordinat)){
				return P;
			}
			else {
				P = NextVillage(P);
			}
		}
		if ((PosX(InfoVillage(P))) == Absis(Koordinat) && PosY(InfoVillage(P)) == Ordinat(Koordinat)){
			return P;
		} else {
			return Nil;
		}
	}
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirstVil (ListVil *L, Village X)
{
	addressVillage P = AlokasiVil(X);
	if(P != Nil)
		InsertFirstVil(L,P);
}

void InsVLastVil (ListVil *L, Village X)
{
	addressVillage P = AlokasiVil(X);
	if(P != Nil)
		InsertLastVil(L,P);
}


/*** PENGHAPUSAN ELEMEN ***/
void DelVFirstVil (ListVil *L, Village * X)
{
	addressVillage P;
	DelFirstVil(L,&P);
	*X = InfoVillage(P);
	DealokasiVil(P);
}

void DelVLastVil (ListVil *L, Village * X)
{
	addressVillage P;
	DelLastVil(L,&P);
	*X = InfoVillage(P);
	DealokasiVil(P);
}


/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirstVil (ListVil *L, addressVillage P)
{
	if (IsEmptyVil(*L))
 		NextVillage(P) = P;
	else{/* L tidak kosong */
		addressVillage last = FirstVillage(*L);
		while (NextVillage(last) != FirstVillage(*L))
			last = NextVillage(last);/* NextVil(last) = FirstVil(L) ==> elemen terakhir */
		NextVillage(P) = FirstVillage(*L);
		NextVillage(last) = P;
	}
	FirstVillage(*L) = P;
}

void InsertLastVil (ListVil *L, addressVillage P)
{
	if (IsEmptyVil(*L))
 		InsertFirstVil(L,P);
	else{
		addressVillage last = FirstVillage(*L);
		while (NextVillage(last) != FirstVillage(*L))
			last = NextVillage(last);
		NextVillage(last) = P;
		NextVillage(P) = FirstVillage(*L);
	}
}

void InsertAfterVil (ListVil *L, addressVillage P, addressVillage Prec)
{
	NextVillage(P) = NextVillage(Prec);
	NextVillage(Prec) = P;
}


/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirstVil (ListVil *L, addressVillage *P)
{
	*P = FirstVillage(*L);
	if (NextVillage(FirstVillage(*L)) == FirstVillage(*L))/* satu elemen */
		FirstVillage(*L) = Nil;
	else {
		addressVillage last = FirstVillage(*L);
		while (NextVillage(last) != FirstVillage(*L))
			last = NextVillage(last);
		/* NextVil(last) = FirstVil(L) */
		FirstVillage(*L) = NextVillage(FirstVillage(*L));
		NextVillage(last) = FirstVillage(*L);
	}
	NextVillage(*P) = Nil;
}

void DelLastVil (ListVil *L, addressVillage *P)
{
	if (NextVillage(FirstVillage(*L)) == FirstVillage(*L)) {
		*P = FirstVillage(*L);
		CreateEmptyVil(L);
	} else {
		addressVillage Last;
		addressVillage PrecLast;
		Last = FirstVillage(*L);
		while(NextVillage(Last) != FirstVillage(*L)) {
			PrecLast = Last;
			Last = NextVillage(Last);
		}
		*P = Last;
		NextVillage(PrecLast) = FirstVillage(*L);
	}
}

void DelAfterVil (ListVil *L, addressVillage *Pdel, addressVillage Prec)
{
	*Pdel = NextVillage(Prec);
	if(NextVillage(Prec) == FirstVillage(*L))
		FirstVillage(*L) = Nil;
	else NextVillage(Prec) = NextVillage(NextVillage(Prec));
	NextVillage(*Pdel) = Nil;
}

void DelPVil (ListVil *L, Village X)
{
	addressVillage P = FirstVillage(*L),Prec;
	if(!IsEmptyVil(*L)){
		if(IsVillageSame(InfoVillage(P),X)){
			DelFirstVil(L, &P);
		}
		else{
			while(NextVillage(P) != FirstVillage(*L) && (!IsVillageSame(InfoVillage(P),X))){
				Prec = P;
				P = NextVillage(P);
			}
			if(IsVillageSame(InfoVillage(P),X))
				DelAfterVil(L,&P,Prec);
		}
	}
}

void PrintListVillage (ListVil L)
{
	if(!IsEmptyVil(L)){
		addressVillage P = FirstVillage(L);
		while(NextVillage(P) != FirstVillage(L)){
			PrintVillage(InfoVillage(P));
			P = NextVillage(P);
		}
		PrintVillage(InfoVillage(P));
	}
}
