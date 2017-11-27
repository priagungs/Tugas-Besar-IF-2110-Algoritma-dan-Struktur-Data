#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackofpoint.h"

infotypeU S;	//sebelum undo
infotypeU temp;	//setelah undo
StackPoint SP;


int main(){
	//init stack
	CreateEmptyPointStack(&SP);

	//init point
	Absis(S.Pt) = 1;
	Ordinat(S.Pt) = 2;
	S.mp = 10;

	//init point setelah move
	Absis(temp.Pt) = 3;
	Ordinat(temp.Pt) = 4;
	temp.mp = 5;

	//push ke stack
	PushPoint(&SP,S);

	//cek apakah stack empty atau tidak
	if(!IsEmptyPointStack(SP)){
		//print point sebelum undo
		printf("sebelum undo\n\n");
		printf("absis : %d\n", Absis(temp.Pt));
		printf("ordinat : %d\n", Ordinat(temp.Pt));
		printf("movepts : %d\n\n", temp.mp);

		//undo
		PopPoint(&SP,&temp);

		//print point setelah undo
		printf("setelah undo\n\n");
		printf("absis : %d\n", Absis(temp.Pt));
		printf("ordinat : %d\n", Ordinat(temp.Pt));
		printf("movepts : %d\n", temp.mp);
	}
	return 0;
}