#include <time.h>
#include <stdlib.h>
#include <stdio.h>

void random(){
    srand(time(NULL));
    printf("%d\n", rand()%100);
    printf("%d\n", rand()%100);
}

int main(){
    int n;   // should only be called once
    scanf("%d", &n);
    while(n == 1){
        random();
        scanf("%d", &n);
    }
}
