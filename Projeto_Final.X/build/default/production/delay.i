# 1 "delay.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "delay.c" 2







# 1 "./delay.h" 1
# 11 "./delay.h"
void delay(int x);
# 8 "delay.c" 2


void delay(int x){
    while(x>0){
        volatile unsigned char j, k;
        for(j = 0; j < 41; j++) {
            for(k = 0; k < 3; k++);
        }
        x--;
    }
}
