/* 
 * File:   ej2guia11.c
 * Author: augustovb
 *
 * Created on June 10, 2014, 8:19 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
/*
 * 
 */
#define PANTALLA_ANCHO  640
#define PANTALLA_LARGO  480     //definiciones necesarias
#define FPS             60
#define CUADRADO        40
#define BITS            8   

/*
 * Enumero los botones a usar
 */

enum BOTONES{
    CERO,UNO,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,ESC,C,S,B
};

/*
 * 
 */
int main(int argc, char** argv) {
    
    ALLEGRO_DISPLAY     * display=NULL;     //MI DISPLAY
    ALLEGRO_EVENT_QUEUE * miseventos=NULL;  //DONDE REGISTRARE EVENTOS
    ALLEGRO_TIMER * timer=NULL;        //para ocasionalmente tomar tiempo
    
    ALLEGRO_BITMAP * ledon=NULL;
    ALLEGRO_BITMAP * ledoff=NULL;       //son cuadrados que simularan los leds siendo bitmaps
    
    printf("Este programa simulara un puerto de 8 bits.\nApretando del 0 al 7 prende el led respectivo.\nc apagará todos y s los prendera.\nManteniendo B apretado, parpadearan.\nTecla esc para cerrar.\n");
    printf("NEGRO=LED APAGADO.\tBLANCO=LED PRENDIDO\nOrden visual:bit7|6|5|4|3|2|1|0\n");
    al_rest(10.0);      //descanso 10 segundos para que el usuario pueda modificar 
    
    
    if(!al_init()){
        fprintf(stderr,"Error al inicializar allegro\n");   //instalo allegro y teclado
        return -1;
    }
    
    if(!al_install_keyboard()){
        fprintf(stderr,"Error al instalar el teclado");
        return -1;
    }
    
    //De aqui en adelante se realizara el adjudicamiento de los elementos a cada puntero
    
    timer=al_create_timer(1.0/FPS);     //creo timer
    if(!timer){
        fprintf(stderr,"Error al crear timer\n");    //a partir de ahora los errores tambien destruiran este timer
        return -1;
    }
    
    
    display=al_create_display(PANTALLA_ANCHO,PANTALLA_LARGO);    //Creo display con aancho y largo de la pantalla
    if(!display){
        fprintf(stderr,"Error al crear el display\n");
        al_destroy_timer(timer);        //si fallo el display, destruyo el timer
        return -1;
    }
    
    unsigned int i=0;
    while(i<256)
    {
        al_clear_to_color(al_map_rgb(0,0,i));       //pequeña fucnion para darle color azul al fondo
        al_flip_display();
        al_rest(0.0000002);
        ++i;
    }
    
    ledon=al_create_bitmap(CUADRADO,CUADRADO);
      if(!ledon){
          fprintf(stderr,"No se pudo crear el bitmap\n");       //creo los bitmaps
          al_destroy_display(display);
          al_destroy_timer(timer);
          return -1;
      }
    ledoff=al_create_bitmap(CUADRADO,CUADRADO);
      if(!ledoff){
          fprintf(stderr,"No se pudo crear el bitmap2\n");
          al_destroy_display(display);
          al_destroy_timer(timer);
          al_destroy_bitmap(ledon);
          return -1;
      }
    
    al_set_target_bitmap(ledon);    //los cambios que voy a hacer se los hago a bouncer1
    al_clear_to_color(al_map_rgb(255,255,255)); //el led ON es blanco
    al_set_target_bitmap(ledoff);         //y el off negro
    al_clear_to_color(al_map_rgb(0,0,0));
      
    al_set_target_bitmap(al_get_backbuffer(display));     //vuelvo a dibujar sobre el display
    
    //dibujo los bits:
    
    i=0;    //reseteo el i a 0
    while(i<BITS){
    
        al_draw_bitmap(ledoff,(CUADRADO/2.0)+i*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
       
        ++i;        
                
    }  
    
    al_flip_display();      //mando el dibujo al display
    
    // antes de manejar el teclado, seteo mi cola de eventos
    miseventos=al_create_event_queue();
    if(!miseventos){
          fprintf(stderr,"Fallo al crear el evento\n");
          al_destroy_bitmap(ledon);
          al_destroy_bitmap(ledoff);
          al_destroy_display(display);
          al_destroy_timer(timer);
          return -1;
    } // al igual que siempre creo y chequeo que no haya habido errores

    al_register_event_source(miseventos,al_get_display_event_source(display));
    al_register_event_source(miseventos,al_get_keyboard_event_source());          //regstro los eventos
    al_register_event_source(miseventos,al_get_timer_event_source(timer));
      
    al_start_timer(timer);        //corro el timer
    

    
    //me voy a encargar ahora del teclado
    
    bool tecla[12]={false,false,false,false,false,false,false,false,false,false,false,false};
    bool dibujar=true;
    bool terminar=false;        //creo variables de tipo bool (1 o 0), para manejar situaicones de si o no
    
    bool bit0on=false;
    bool bit1on=false;
    bool bit2on=false;
    bool bit3on=false;
    bool bit4on=false;
    bool bit5on=false;          //variables para cequear estado del bit (prendido o apagado)
    bool bit6on=false;
    bool bit7on=false;
    
    
    
    while(!terminar){
          ALLEGRO_EVENT eventolocal;     //creo variable para regular eventos dentro del while
          
          
          
          al_wait_for_event(miseventos,&eventolocal);   //espero recibir un evento (sin polling)
          
          
          if(eventolocal.type==ALLEGRO_EVENT_TIMER){         //si hay un evento del timer
              if(tecla[ESC]){
                  break;            // SI SE APRETO, SALGO, ES LA UNICA VARIABLE QUE QUIERO
              }
              if(tecla[B]){ //Parpadeara
                                //Si aprete el 0
                                        if(bit0on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+7*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit0on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+7*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit0on=true;
                                        }
                                        if(bit1on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+6*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit1on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+6*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit1on=true;
                                        }
                                        if(bit2on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+5*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit2on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+5*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit2on=true;
                                        }
                                        if(bit3on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+4*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit3on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+4*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit3on=true;
                                        }
                                        if(bit4on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+3*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit4on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+3*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit4on=true;
                                        }
                                        if(bit5on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+2*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit5on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+2*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit5on=true;
                                        }
                                        if(bit6on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+1*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit6on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+1*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit6on=true;
                                        }
                                        if(bit7on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+0*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit7on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+0*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit7on=true;
                                        }
                                        al_flip_display();
                                        

                  
              }
              
              //ACA PONGO LO DE SI B ESTA APRETADO
              
          } 
          if(eventolocal.type==ALLEGRO_EVENT_KEY_DOWN){
              switch(eventolocal.keyboard.keycode){
                  case ALLEGRO_KEY_0:   tecla[CERO]=true;                       //Si aprete el 0
                                        if(bit0on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+7*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit0on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+7*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit0on=true;
                                        }
                                        al_flip_display();     
                                        break;
                  
                  case ALLEGRO_KEY_1:   tecla[UNO]=true;
                                        if(bit1on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+6*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit1on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+6*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit1on=true;
                                        }
                                        al_flip_display();    
                                        break;
                  case ALLEGRO_KEY_2:   tecla[DOS]=true;
                                        if(bit2on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+5*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit2on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+5*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit2on=true;
                                        }
                                        al_flip_display();  
                                        break;
                                         
                  case ALLEGRO_KEY_3:   tecla[TRES]=true;
                                        if(bit3on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+4*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit3on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+4*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit3on=true;
                                        }
                                        al_flip_display();    
                                        break;
                  case ALLEGRO_KEY_4:   tecla[CUATRO]=true;
                                        if(bit4on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+3*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit4on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+3*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit4on=true;
                                        }
                                        al_flip_display();    
                                        break; 
                  case ALLEGRO_KEY_5:   tecla[CINCO]=true;
                                        if(bit5on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+2*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit5on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+2*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit5on=true;
                                        }
                                        al_flip_display();    
                                        break;
                  case ALLEGRO_KEY_6:   tecla[SEIS]=true;
                                        if(bit6on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+1*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit6on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+1*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit6on=true;
                                        }
                                        al_flip_display();    
                                        break;
                  case ALLEGRO_KEY_7:   tecla[SIETE]=true;
                                        if(bit7on){
                                        al_draw_bitmap(ledoff,(CUADRADO/2.0)+0*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit7on=false;
                                        }
                                        else{
                                        al_draw_bitmap(ledon,(CUADRADO/2.0)+0*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
                                        bit7on=true;
                                        }
                                        al_flip_display();   
                                        break;
                  case ALLEGRO_KEY_C:   i=0;
                                        while(i<BITS){
    
                                            al_draw_bitmap(ledoff,(CUADRADO/2.0)+i*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
       
                                            ++i;        
                
                                        }
                                        al_flip_display();
                                        bit0on=false;
                                        bit1on=false;
                                        bit2on=false;
                                        bit3on=false;
                                        bit4on=false;
                                        bit5on=false;         
                                        bit6on=false;
                                        bit7on=false;
                                        break;
                  case ALLEGRO_KEY_S:   i=0;
                                        while(i<BITS){
    
                                            al_draw_bitmap(ledon,(CUADRADO/2.0)+i*(PANTALLA_ANCHO/BITS),PANTALLA_LARGO/2-(CUADRADO/2.0),0);
       
                                            ++i;        
                
                                        }
                                        al_flip_display();
                                        bit0on=true;
                                        bit1on=true;
                                        bit2on=true;
                                        bit3on=true;
                                        bit4on=true;
                                        bit5on=true;         
                                        bit6on=true;
                                        bit7on=true;
                                        break;
                  case ALLEGRO_KEY_B: tecla[B]=true;
                                      break;  
                                        
                                        
                      
                      
                  default: break;                //el que escapa lo hago cuando suelta la tecla 
              }
          }
          if(eventolocal.type==ALLEGRO_EVENT_KEY_UP){
              switch(eventolocal.keyboard.keycode){
                  case ALLEGRO_KEY_ESCAPE: tecla[ESC]=true; //en realidad pongo doexit = true pero esto es para aca nomas
                                           break;
                  case ALLEGRO_KEY_B:      tecla[B]=false;
                                           break;       //Esto hace que mientras presiono B, parpadee
                                          
                  default:break;
              }
          }
              
                  
        
        
        
        
    }        //mientras terminar sea falso, continuara en este loop
        
    
    
    

    return 0;
}

