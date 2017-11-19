#include <stdio.h>
#include <stdlib.h>
#include "boolean.h"
#include "peta.h"
#include "pcolor.h"

int main(){
	PETA test;
	MakePETA(8,8,&test);
	PrintPETA(test);
}