/* 
 * File:   ej1.h
 * Author: augustovb
 *
 * Created on June 8, 2014, 2:39 PM
 */

#ifndef EJ1__H
#define	EJ1__H

/*
 * Definicion de constantes
 */

#define INPUT 5
#define OUTPUT 0

#define ERROR -1
#define BIT0    1
#define BIT1    2
#define BIT2    4
#define BIT3    8           //defino mascaras para las funciones
#define BIT4    16
#define BIT5    32
#define BIT6    64
#define BIT7    128

/*
 *Definicion de tipos
 */




typedef struct{
    unsigned char byte;
    
}T_BYTE;

typedef union{                  //defino una union de un word
    unsigned int word :16;  
    struct{
    unsigned char lobyte;       //es lo/hi porque es estructura intel
    unsigned char hibyte;       //Lo escribo de esta manera para asegurarme que ocupe 16 bits, porque el inte de mi pc es de 32 o 64.
    }part;
}T_WORD;

typedef union{
    T_WORD portD;   //en la union le asigno 16 bits al D (un int de hc11)
    struct {
        T_BYTE portB;
        T_BYTE portA;     //el portB es la parte lo, el portA, la hi
    }single;
}PUERTOS;

/*
 *Definicion de funciones
 */

void bitSet (unsigned char * byte, unsigned char bit,int * pstate);
void bitClear (unsigned char * byte, unsigned char bit,int * pstate);
unsigned char pow2 (unsigned char ala);
void bitToggle(unsigned char *byte, unsigned char bit,int *pstate);
unsigned int bitGet (unsigned char *byte,unsigned char bit, int *pstate);


#endif	/* EJ1_H */

