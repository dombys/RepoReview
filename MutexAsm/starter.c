#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
extern int withdrawing();


void *dowyplaty() {
    while(true){
      int account_balance_result = withdrawing();
      printf("%d\n", account_balance_result);
      return 0;
}
}
int main() {
    pthread_t thready1;
    pthread_t thready2;
    int result1 = pthread_create(&thready1, NULL, dowyplaty, NULL);
    if (result1 !=0){
     printf("Watek 1 nie zostal utworzony\n");
    } 
    int result2 = pthread_create(&thready2, NULL, dowyplaty, NULL);
    if (result2 !=0){
     printf("Watek 2 nie zostal utworzony\n");
    }
    pthread_join(thready2, NULL); //czekamy na zakonczenie pracy watku 2
    return 0; //exit
}

