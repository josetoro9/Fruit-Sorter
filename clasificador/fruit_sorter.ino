#include "HX711.h"
#include <Herkulex.h>
#include <SD.h>

int cargador=1; //definiendo nombre del motor 0xfe significa todos los motores generico
int clasificador=2; //definiendo nombre del motor 0xfe significa todos los motores generico
int sacador=3; //definiendo nombre del motor 0xfe significa todos los motores generico
int sensor_read = 2;  //lectura del sensor de proximidad
int val_pinia = 0;    // existenia de la pinia en sensor de proximidad

#define DOUT  A1
#define CLK  A0

HX711 balanza(DOUT, CLK);
float pesobalanaza;



void setup() {
  Serial.begin(115200);
  Herkulex.begin(115200,8,9); //Abiendo puertos de comunicacion rx=10 y tx=11 
  Herkulex.reboot(cargador); //reseteando motor 1
  Herkulex.reboot(clasificador); //reseteando motor 2
  Herkulex.reboot(sacador); //reseteando motor 3
  delay(500); 
  Herkulex.initialize(); //iniciando motores
  delay(200);   
  Herkulex.setLed(cargador,LED_GREEN2); //led indicando correcta disposicion
  Herkulex.setLed(clasificador,LED_CYAN); //led indicando correcta disposicion
  Herkulex.setLed(sacador,LED_WHITE); //led indicando correcta disposicion
  delay(1000);  
  // cliclo de limpieza de inicio
  Herkulex.torqueON(cargador);
  Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveAllAngle(cargador, 0, 1);
  Herkulex.moveAllAngle(clasificador, 0, 1);
  Herkulex.moveAllAngle(sacador, 0, 1); 
  Herkulex.actionAll(600);
  delay(620);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
  Herkulex.moveOneAngle(cargador, 60, 300, 2); 
  delay(310);    
  Herkulex.moveOneAngle(cargador, 0, 300, 2); 
  delay(310); 
  Herkulex.torqueOFF(cargador);
  Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, -150, 600, LED_GREEN2); 
  delay(610);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
  balanza.set_scale(200746.098); // Establecemos la escala
  balanza.tare(20);  //El peso actual es considerado Tara.
}
// Programa de clasificacion de pinias Elixir.
void loop() {
  val_pinia = digitalRead(sensor_read);
  // validala presecia de una pinia
  if (val_pinia == LOW)
  {
    //Abre la trampilla cargadora
    Herkulex.torqueON(cargador);
    Herkulex.moveOneAngle(cargador, 60, 300, LED_BLUE); 
    delay(310);    
    Herkulex.moveOneAngle(cargador, 00, 300, LED_BLUE);  
    delay(310); 
    Herkulex.torqueOFF(cargador);
    pesobalanaza= (balanza.get_units(10));
    //Clasificacion de la pinia segun peso
    if (pesobalanaza>=0.3 && pesobalanaza<=0.7)        //NOMBRE: HUEVO
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, -120, 600, LED_GREEN2); 
  delay(610);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
        /* en este punto lo que se hace es definir hasta donde girara el motor,  que espere
        un tiempo y luego volver a su posicion inicial, mas que todo seria sincronismo, como
        se puede observar para disminur tiempos el giro que recobra la posicion 0 se realiza al unisono */
      }
      else if (pesobalanaza>2.59 && pesobalanaza<=9)       //NOMBRE: #4
      /* Acá se deben definir los pesos donde se busque clasificar la fruta y el motor de debe mover, recordar
      incluir las librerias de servomotor para trabajar */
      {  
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, -90, 400, LED_GREEN2); 
  delay(410);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      }
      else if (pesobalanaza>2.19 && pesobalanaza<=2.59)       //NOMBRE: #5
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, -60, 210, LED_GREEN2); 
  delay(220);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      }  
      else if (pesobalanaza>1.79 && pesobalanaza<=2.19)       //NOMBRE: #6
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, -30, 210, LED_GREEN2); 
  delay(220);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      } 
      else if (pesobalanaza>1.58 && pesobalanaza<=1.79)      //NOMBRE: #7
      {
        // Este funciona diferente al ser lo mas alto de la campana de Gauss y no necesita el motor clasificador
  Herkulex.torqueON(sacador);   
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveOneAngle(sacador, 0, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.torqueOFF(sacador);
      }  
      else if (pesobalanaza>1.37 && pesobalanaza<=1.58)       //NOMBRE: #8
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, 30, 210, LED_GREEN2); 
  delay(220);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      } 
      else if (pesobalanaza>1.21 && pesobalanaza<=1.37)       //NOMBRE: #9
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, 60, 380, LED_GREEN2); 
  delay(390);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      } 
      else if (pesobalanaza>1.09 && pesobalanaza<=1.21)       //NOMBRE: #10
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, 90, 600, LED_GREEN2); 
  delay(610);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      } 
      else if (pesobalanaza>0.99 && pesobalanaza<=1.09)       //NOMBRE: BABY
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, 120, 600, LED_GREEN2); 
  delay(610);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      } 
      else if (pesobalanaza>0.7 && pesobalanaza<=0.99)       //NOMBRE: APROVECHAMIENTO
      {
        Herkulex.torqueON(clasificador);
  Herkulex.torqueON(sacador);
  Herkulex.moveOneAngle(clasificador, 150, 600, LED_GREEN2); 
  delay(610);      
  Herkulex.moveOneAngle(sacador, 150, 600, LED_GREEN2); 
  delay(610); 
  Herkulex.moveAllAngle(clasificador, 0, 2);
  Herkulex.moveAllAngle(sacador, 0, 2); 
  Herkulex.actionAll(600);
  delay(610);
  Herkulex.torqueOFF(clasificador);
  Herkulex.torqueOFF(sacador);
      } 
  }
  
}

