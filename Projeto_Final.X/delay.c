/* 
 * File:   delay.c
 * Author: Maria Eduarda de Souza Béco
 * Matricula: 2020000431
 * Turma: 01
 */

#include "delay.h"

void delay(int x){            //x = tempo a ser gasto em ms
    while(x>0){                         //enquanto não der x ms, não sai do loop
        volatile unsigned char j, k;
        for(j = 0; j < 41; j++) {       //delay de aproximadamente 1ms
            for(k = 0; k < 3; k++); 
        }
        x--;
    }
}
