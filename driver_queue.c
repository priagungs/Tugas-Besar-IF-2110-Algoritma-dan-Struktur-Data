#include "queue.h"
#include <stdio.h>

Queue q;
int x,n;

int main(){
	printf("Masukkan banyak angka yang ingin anda masukkan ke queue : ");
	scanf("%d",&n);
	CreateEmptyQueue(&q,n);
	if(IsEmptyQueue(q))
		puts("Queue dalam keadaan kosong.");
	printf("\nMasukkan %d angka : \n",n);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);
		AddQueue(&q,x);
	}
	if(IsFullQueue(q))
		puts("Queue dalam keadaan terisi penuh.");
	puts("Berikut akan dikeluar semua elemen pada queue dan menghapus elemen yang sudah dikeluarkan.");
	for(int i=1;i<=n;i++){
		printf("%d\n",HeadQueue(q));
		x = HeadQueue(q);
		DelQueue(&q,&x);
	}
}