//Definimos los pines a ocupar 
#define led1 14
#define led2 27
#define led3 26
#define led4 25
#define led5 33

//Definimos los leds que se usarán en un arreglo
const int leds[5] = {led1, led2, led3, led4, led5};

void setup() {
  //Definimos los pines como salida dentro de un ciclo for
  for (int i = 0; i < 5 ; i++) {
    pinMode(leds[i], OUTPUT);
  }

  //Encendemos y apagamos el primer LED solo una vez
  digitalWrite(led1, HIGH);
  delay(50);
  digitalWrite(led1, LOW);
  delay(50);
}

void loop() {
  //Creamos un ciclo for para encender y apagar los LEDs uno a uno de izquierda a derecha a partir del led2 hasta el led5
  for (int i = 1; i < 5; i++) {
    digitalWrite(leds[i], HIGH);
    delay(50);
    digitalWrite(leds[i], LOW);
    }

  //Esperamos un poco más en el último LED
  delay(50);

  //Creamos un ciclo for para encender y apagar los LEDs uno a uno de derecha a izquierda a partir del led4 hasta el led1
  for (int i = 3; i >= 0; i--) {
    digitalWrite(leds[i], HIGH);
    delay(50);
    digitalWrite(leds[i],LOW);
    //delay(50);
  }

  //Esperamos un poco más en el último LED antes de volver a completar el ciclo
  delay(50);
}
