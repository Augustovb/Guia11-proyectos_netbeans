/* 
 * File:   Ej1.c
 * Author: augustovb
 *
 * Created on June 8, 2014, 1:14 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ej1.h"


int main(int argc, char** argv) {

    int estado=0;
    int *pestado;
    pestado=&estado;
    int IO=INPUT;
    
    int * pIO=&IO;
    
    PUERTOS inputport, outputport;      //creo dos, uno para tratarlo como entrada y el otro para salida
    inputport.single.portA.byte=255;   //para chequear
    
    unsigned char * pportA;
    pportA=&(inputport.single.portA.byte);
    
    
    return 0;
}

void bitToggle(unsigned char *byte, unsigned char bit,int *pstate,int * pio)
{
    if(bit>7)
    {
        printf("No hay mas de 7 bits.\n");
        *pstate=ERROR;
        return ;
    }
    
    *byte=(*byte)^(pow2(bit));
    
}

unsigned int bitGet (unsigned char *byte,unsigned char bit, int *pstate,int * pio)    //devuelve el numero o 0 o 1
{
    if(bit>7)
    {
        printf("No hay mas de 7 bits.\n");
        *pstate=ERROR;
        return ;
    }
    int result;
    result=((*byte)&(pow2(bit)))>>bit;
    return result;
}





void bitSet (unsigned char * byte, unsigned char bit,int * pstate)   //esta funcion recibe un puntero al byte de una estructura de ese tipo, el byte a cambiar (n) y si vendra un 1 o un 0 alli
{
    if(bit>7)
    {
        printf("Recuerde que son bytes, el n no puede ser mayor a 7 (van del 0 al 7 los bits)\n");
        *pstate=ERROR;
        return ;
    }

    

        unsigned char masktoset;
        masktoset=pow2(bit);
        *byte=(*byte)|masktoset;
       
}

void bitClear (unsigned char * byte, unsigned char bit, int * pstate)
{

    if(bit>7)
    {
        printf("Recuerde que son bytes, el n no puede ser mayor a 7 (van del 0 al 7 los bits)\n");
        *pstate=ERROR;
        return ;
    }
    
    
        unsigned char masktoset;
        masktoset=pow2(bit);
        masktoset=~masktoset;           //la mascara tendra un 0 en el bit indicado al comienzo
        *byte=(*byte)&masktoset;
  
}


unsigned char pow2 (unsigned char ala)      //hace potencias enteras de numeros de dos positivas retornando del 1 al 128
{
    unsigned char result=1;
    unsigned char contador=0;
    if (ala==0)
    {
        return 1;
    }
    for( contador=0 ;   contador<ala    ;   ++contador)
    {
        result*=2;
    }
    return (result);
}