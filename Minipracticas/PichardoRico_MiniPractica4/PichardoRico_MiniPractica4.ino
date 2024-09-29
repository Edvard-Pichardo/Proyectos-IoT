//Mini Práctica 4

//Definimos el pin de la fotoresistencia
#define PinADC 34 

//Definimos los leds a ocupar
#define led1 14 
#define led2 27
#define led3 26
#define led4 25
#define led5 33

//Definimos los leds que se usarán en un arreglo
const int leds[5] = {led1, led2, led3, led4, led5};

void setup() {
  Serial.begin(115200);     //Iniciamos la comunicación serial
  pinMode(PinADC, INPUT);   //Declaramos el pin como entrada

  //Definimos los leds como salida dentro de un ciclo for
  for (int i = 0; i < 5 ; i++) {
    pinMode(leds[i], OUTPUT);
  }  
}

void loop() {
  int sensor = analogRead(PinADC);  //Guardamos la lectura del pin en la variable sensor
  //int prom = media(1000, PinADC);   //Guardamos el resultado de la función media 

  if(sensor==0){
    for (int i = 0; i < 5 ; i++){ //Este ciclo prende todos los leds cuando no hay nada de luz
        digitalWrite(leds[i], HIGH);
        } 
  }
  else if(sensor>0 && sensor<1024){
    for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds
        digitalWrite(leds[i], LOW);
      } 
    for (int i = 0; i < 4 ; i++){ //Este ciclo enciende los leds 1-4
        digitalWrite(leds[i], HIGH);
      } 
  }
  else if(sensor>=1024 && sensor<2048){
    for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds
        digitalWrite(leds[i], LOW);
      } 
    for (int i = 0; i < 3 ; i++){ //Este ciclo enciende los leds 1-3
        digitalWrite(leds[i], HIGH);
      } 
  }
  else if(sensor>=2048 && sensor<3072){
    for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds
        digitalWrite(leds[i], LOW);
      } 
    for (int i = 0; i < 2 ; i++){ //Este ciclo enciende los leds 1-2
        digitalWrite(leds[i], HIGH);
      } 
  }
  else if(sensor>=3072 && sensor<4095){
    for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds
        digitalWrite(leds[i], LOW);
      } 
    digitalWrite(leds[0], HIGH); //Este solo enciende el led 1
  }
  else{
    for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds
        digitalWrite(leds[i], LOW);
      } 
  }

Serial.println(sensor);           //Imprimimos el valor de la variable "sensor"

}
