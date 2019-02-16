/*
En este programa se mide el valor del sensor muscular que va de 0 a 1023
y este dato se convierte al rango de cada motor. De esta manera conseguimos
las 6 posiciones a partir de un solo valor. 
Cuando se flexione la muñeca, el valor medido aumentará y, por tanto,
la mano impresa en 3D se cerrará.

*/
const int muscle_sensor = A5; // Pin connected to voltage divider output

#include <Servo.h>;
Servo servo2;
Servo servo1;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

unsigned long previousMillis=0;
int pos1=0;
int pos2=0;
int pos3=155;
int pos4=155;
int pos5=0;
int pos6=80;
int sensor=0; //Valor del sensor
void setup() 
{
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(9);
  servo4.attach(3);
  servo5.attach(10);
  servo6.attach(11);
  
  servo1.write(0);
  servo2.write(0);
  servo3.write(155); //al estar colocados de un lado opuesto 
  servo4.write(155); //a los otros dos su giro está invertido
  servo5.write(0);
  servo6.write(80);
  
  Serial.begin(9600);
  
  pinMode(muscle_sensor, INPUT);
    
    previousMillis=millis(); // 5/8/18 a las 21:01
}

void loop() 
{  if( millis()-previousMillis >= 30){
    sensor = analogRead(muscle_sensor);

pos1=map(sensor,14,1023,0,135); 
    pos2=map(sensor,14,1023,0,135);
    pos3=map(sensor,14,1023,155,20);
    pos4=map(sensor,14,1023,155,20); //el índice tiene problemas paar moverse 
                                    //totalmente por lo que aumento el rango
    pos5=map(sensor,14,1023,100,140);
    pos6=map(sensor,14,1023,80,175);
   
    //añadimos condicionales de contraol para no dañar los servos
    if(pos1>140){
      pos1=140;
      }else if(pos1<0){
        pos1=0;
        }
     if(pos2>140){
      pos2=140;
      }else if(pos2<0){
        pos2=0;
        }
     if(pos3>160){
      pos3=160;
      }else if(pos3<15){
        pos3=15;
        }
      if(pos4>160){
      pos4=160;
      }else if(pos4<10){
        pos4=10;
        }    
      if(pos5>140){
        pos5=140;
        }else if(pos5<100){
          pos5=100;
          }
      if(pos6>175){
        pos6=175;
        }else if(pos6<80){
          pos6=80;
          }
          
    servo1.write(pos1);             
    servo2.write(pos2);
    servo3.write(pos3);
    servo4.write(pos4);
    servo5.write(pos5);
    servo6.write(pos6);
    //Envía los datos al Serial Plotter[Desactivado]
    Serial.println(sensor);
 /*   Serial.print(pos1);
    Serial.print(' ');
    Serial.print(pos2);
    Serial.print(' ');
    Serial.print(pos3);
    Serial.print(' ');
    Serial.print(pos4);
    Serial.print(' ');
    Serial.print(pos5);
    Serial.print(' ');
    Serial.println(pos6);  
    }*/
   previousMillis=millis();
  }

}

