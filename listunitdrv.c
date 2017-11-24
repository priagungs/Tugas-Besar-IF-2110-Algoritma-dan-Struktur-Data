/* Driver listofunit */

#include "listofunit.h"
#include <stdio.h>

int main(){
	Unit U;
	ListUnit LUnit;
	POINT Loc;
	CreateEmptyUnit(&LUnit);
	BacaPOINT(&Loc);
	TulisPOINT(Loc);
	U = CreateUnit("Archer",Loc);
	TulisPOINT(Lokasi_Unit(U));
	InsUnitFirst(&LUnit,U);
	TulisPOINT(Lokasi_Unit(InfoUnit(FirstUnit(LUnit))));
	PrintListUnit(LUnit);
	return 0;
}