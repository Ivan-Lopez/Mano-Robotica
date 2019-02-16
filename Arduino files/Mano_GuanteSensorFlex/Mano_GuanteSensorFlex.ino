/*En este programa se recoge la información de flexión de los sensores del
guante a través de su cambio de resistencia. 

Una vez obtenido el valor de entrada que va de 0-1023, reducimos el rango
de 300 a 600 aprox donde 300 es el valor cuando el sensor está recto y
600 cuando el sensor está flexionado.

Para evitar cambios continuos, recogemos 1 dato por dedo cada 5 ms. Al 
llegar a 30 datos recogidos, hacemos la media.

Después gracias a map() convertimos el valor medio de este rango de
mínimo y máximo del sensor(300-600) al rango de posición de cada motor
(0-135, por ejemplo).

Finalmente, enviamos las pociciones resultantes a los motores 
con servo.write() e imprimimos estos datos por el puerto serie para 
poder visualizarlos en el ordenador. Si se alimenta el guante y la mano 
mediante una batería y no por USB, esa parte se puede comentar 
*/

//variables para asignar a cada entrada analógica un nombre
const int FLEX_PIN1 = A0; // Pin connected to voltage divider output
const int FLEX_PIN2 = A1;
const int FLEX_PIN3 = A2;
const int FLEX_PIN4 = A3;
const int FLEX_PIN5 = A4;
const int FLEX_PIN6 = A5;//este es el servo pequeñode la palma

#include <Servo.h>;
//incluimos la librería servo para después 
//crear los 6 servos y poder moverlos
Servo servo2;
Servo servo1;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

const int intervalo = 500;
unsigned long previousMillis=0;

//Variables para realizar la media
int Lecturas1[30];
int Lecturas2[30];
int Lecturas3[30];
int Lecturas4[30];
int Lecturas5[30];
int Lecturas6[30];
int Total1=0;
int Total2=0;
int Total3=0;
int Total4=0;
int Total5=0;
int Total6=0;
int i=0;
int media1=0;
int media2=0;
int media3=0;
int media4=0;
int media5=0;
int media6=0;

//posiciones resultantes que serán enviadas a cada motor
int pos1=0;
int pos2=0;
int pos3=155;
int pos4=155;
int pos5=0;
int pos6=80;
void setup() 
{ //enlazamos cada servo a una salida para poder controlarnos
  servo1.attach(5);
  servo2.attach(6);
  servo3.attach(9);
  servo4.attach(3);
  servo5.attach(10);
  servo6.attach(11);

  //enviamos una orden de posición a los servos 
  //para que los dedos vuelvan a estar derechos
  servo1.write(0);
  servo2.write(0);
  servo3.write(155);
  servo4.write(155);
  servo5.write(0);
  servo6.write(80);
  
  Serial.begin(9600); //inicializamos el puerto serie  
                      //para ver los datos resultantes
  
  pinMode(FLEX_PIN1, INPUT); //Establecemos 
  pinMode(FLEX_PIN2, INPUT); //las entradas para
  pinMode(FLEX_PIN3, INPUT); //los sensores
  pinMode(FLEX_PIN4, INPUT);
  pinMode(FLEX_PIN5, INPUT);
  pinMode(FLEX_PIN6, INPUT);

 //Reseteamos a 0 todas las posiciones de los arrays
  for(i=0;i<30;i++){
    Lecturas1[i]=0;
    }
    i=0;
  for(i=0;i<30;i++){
    Lecturas2[i]=0;
    }
    i=0;
  for(i=0;i<30;i++){
    Lecturas3[i]=0;
    }
    i=0;
  for(i=0;i<30;i++){
    Lecturas4[i]=0;
    }
    i=0;
  for(i=50;i<30;i++){
    Lecturas5[i]=0;
    }
    i=0;
  for(i=0;i<30;i++){
    Lecturas6[i]=0;
    } 
    i=0; 
    
    previousMillis=millis(); // 5/8/18 a las 21:01
}

void loop() 
{ //Realizamos una lectura cada5ms, por lo que el servo se mueve cada 150ms
  if(millis()-previousMillis>=5){   
  //Restamos los valores guardados anteriormente
  Total1=Total1-Lecturas1[i];
  Total2=Total2-Lecturas2[i];
  Total3=Total3-Lecturas3[i];
  Total4=Total4-Lecturas4[i];
  Total5=Total5-Lecturas5[i];
  Total6=Total6-Lecturas6[i];
  //Agregamos la nueva lectura
  Lecturas1[i] = analogRead(FLEX_PIN1);
  Lecturas2[i] = analogRead(FLEX_PIN2);
  Lecturas3[i] = analogRead(FLEX_PIN3);
  Lecturas4[i] = analogRead(FLEX_PIN4);
  Lecturas5[i] = analogRead(FLEX_PIN5);
  Lecturas6[i] = analogRead(FLEX_PIN6);
  //Sumamos la nueva lectura al total
  Total1=Total1+Lecturas1[i];
  Total2=Total2+Lecturas2[i];
  Total3=Total3+Lecturas3[i];
  Total4=Total4+Lecturas4[i];
  Total5=Total5+Lecturas5[i];
  Total6=Total6+Lecturas6[i];
  i++;
  //Calcula la media si el array está completo, y la envía al servo 
  if(i>=30){
    i=0;
    media1=Total1/30;
    media2=Total2/30;
    media3=Total3/30;
    media4=Total4/30;
    media5=Total5/30;
    media6=Total6/30;
    pos1=map(media1,532,311,0,135);
               //estos valores vienen dados del analogRead()
               //que hemos establecido tras probar previamente
               //los sensores para crear un máximo y un mínimo de flexión
    pos2=map(media2,542,358,0,135);
    pos3=map(media3,618,389,155,20);
    pos4=map(media4,624,400,155,20);
    pos5=map(media5,620,460,100,160);
    pos6=map(media6,660,580,80,175);
   
    //añadimos condicionales de control para no dañar los servos
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
      if(pos5>160){
        pos5=160;
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
    //Envía los datos al Serial Plotter
    Serial.print(pos1);
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
    }
   previousMillis=millis();
  }
  
}

