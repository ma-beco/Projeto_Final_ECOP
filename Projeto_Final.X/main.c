/*
 * File:   main.c
 * Author: Maria Béco
 *
 * Created on 15 de Dezembro de 2021, 13:36
 */


#include <pic18f4520.h>
#include "config.h"
#include "adc.h"
#include "io.h"
#include "keypad.h"
#include "lcd.h"
#include "so.h"
#include "ssd.h"
#include "bits.h"
#include "delay.h"
#include "pwm.h"

void main(void) {
unsigned char tecla, old, s1 = '0', s2 = '0', s3 = '0';
unsigned char t1 = '0', t2 = '0', t3 = '0'; //tentativas senha
int enter, moed, muda, meta;
float tempo;
lcdInit();
adcInit();
kpInit();
pwmInit();
for (;;) {
    switch (muda) {
        case 0:
            lcdPosition(0, 0);
            lcdString("SENHA       ");
            lcdPosition(1, 0);
            lcdChar(s1);
            lcdChar(s2);
            lcdChar(s3);
            kpDebounce();
            old = tecla;
            tecla = kpRead();
            if (old != tecla) {
                if ((bitTst(tecla, 0)) && enter == 0) s1++; //definição de senha
                if ((bitTst(tecla, 0)) && enter == 1) s2++;
                if ((bitTst(tecla, 0)) && enter == 2) s3++;
                if (bitTst(tecla, 6)) { //enter
                    enter++;
                    if (enter == 3) {
                        muda = 1;
                    }
                }
            }
        break;
        case 1:
            lcdPosition(0, 0);
            lcdString("Defina meta");
            lcdPosition(1, 0);
            lcdNumber(meta);
            kpDebounce();
            old = tecla;
            tecla = kpRead();
            if (old != tecla) {
                if ((bitTst(tecla, 0)) && enter == 3) meta += 5; //definição de meta
                if (bitTst(tecla, 6)) { //enter
                    enter++;
                    if (enter == 4) {
                        lcdPosition(0, 0);
                        lcdString("Sua meta:  ");
                        muda = 2;
                    }
                }
            }
        break;
        case 2:
            kpDebounce();
            old = tecla;
            tecla = kpRead();
            if (old != tecla) {
                if (bitTst(tecla, 1)) moed += 100;  //R$1,00
                if (bitTst(tecla, 2)) moed += 50;   //R$0,50
                if (bitTst(tecla, 3)) moed += 25;   //R$0,25
                if (bitTst(tecla, 4)) moed += 10;   //R$0,10
                if (bitTst(tecla, 5)) moed += 5;    //R$0,05
            }//end if moedas
            ssdInit();
            ssdDigit(((moed / 1000) % 10), 0); //R$10,00
            ssdDigit(((moed / 100) % 10), 1);  //R$01,00
            ssdDigit(((moed / 10) % 10), 2);   //R$00,10
            ssdDigit(((moed / 1) % 10), 3);    //R$00,01
            ssdUpdate();
            for (tempo = 0; tempo < 50; tempo++); //tempo para corrigir flicker
            if (moed >= meta) { //caso a meta seja batida vai para proxima parte
                muda = 3;
                enter = 4;
            }
        break;
        case 3:
            lcdPosition(0, 0);
            lcdString("Senha?   ");
            lcdPosition(1, 0);
            lcdChar(t1);
            lcdChar(t2);
            lcdChar(t3);
            lcdChar(' ');
            lcdChar(' ');
            kpDebounce();
            old = tecla;
            tecla = kpRead();
            if (old != tecla) {
                if ((bitTst(tecla, 0)) && enter == 4) t1++; //tentaiva 1 digito senha
                if ((bitTst(tecla, 0)) && enter == 5) t2++; //tentaiva 1 digito senha
                if ((bitTst(tecla, 0)) && enter == 6) t3++; //tentaiva 1 digito senha
                if (bitTst(tecla, 6)) { //enter
                    enter++;
                    if (enter == 7 && t1 == s1 && t2 == s2 && t3 == s3) { //abertura do cofre se senhas corretas
                        lcdPosition(0, 0);
                        lcdString("Cofre aberto");
                        pwmSet(100);
                        delay(1500);
                        pwmSet(0);
                        muda = 0;
                        enter = 0;
                        s1 = '0';
                        s2 = '0';
                        s3 = '0';
                        t1 = '0';
                        t2 = '0';
                        t3 = '0';
                        moed = 0;
                        meta = 0;
                    }
                    if (enter == 7 && (t1 != s1 || t2 != s2 || t3 != s3)) { //repete a tentativa de senhas se errar
                        t1 = '0';
                        t2 = '0';
                        t3 = '0';
                        enter = 4;
                        pwmSet(100);
                        delay(250);
                        pwmSet(0);
                    }
                }
            }
        break;
    }//end switch
} //end for(;;)
} //end void main