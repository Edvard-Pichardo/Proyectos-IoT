//Mini práctica 3: Entradas digítales 

//Definimos el pin del botón Pullup y del PullDown
#define PinBotton_PullUp 4
#define PinBotton_PullDown 15

//Definimos los leds a ocupar
#define led1 14 
#define led2 27
#define led3 26
#define led4 25
#define led5 33

//Definimos 3 variables para el contador
int count = 0; //Variable contador
long timeCounter = 0; //Variable que almacenará la función del millis; comienza en cero
const int timeThreshold = 350; //Contador umbral

//Definimos los leds que se usarán en un arreglo
const int leds[5] = {led1, led2, led3, led4, led5};

void setup() {
  Serial.begin(115200); //Declaramos la Comunicación Serial para el ESP32
  pinMode(PinBotton_PullUp, INPUT); //Declaramos botón pullup
  pinMode(PinBotton_PullDown, INPUT); //Declaramos el botón pulldown

  //Definimos los leds como salida dentro de un ciclo for
  for (int i = 0; i < 5 ; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  int in_up = digitalRead(PinBotton_PullUp); //Almacenamos el estado del botón pullup en una variable
  int in_down = digitalRead(PinBotton_PullDown); //Almacenamos el estado del botón pulldown en una variable
  
  if(in_up == LOW){ //Si el botón pullup es presionado entonces entrará a este if
    if(millis() > timeCounter + timeThreshold){ //Si el tiempo de ejecución es mayor al tiempo umbral más el tiempo de conteo entonces entra a este if
      if(count<=5){
       digitalWrite(leds[count], HIGH); //Se enciende el led asociado al número del contador entre 0 y 4 
       count++; //Aumenta 1 al contador
      }

      if(count>5){ //Si el contador es mayor a 5 entra en este if
        for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds 
        digitalWrite(leds[i], LOW);
        } 
        count=0; //Se define el contador en cero nuevamente para reiniciar el ciclo
      }
      
      timeCounter = millis(); //Se almacena timeCounter en la función millis()
      Serial.println(count); //Esto lo usé como apoyo para ver la cantidad de pulsaciones en el monitor serie
    }
  }

  if(in_down == HIGH){ //Si se pulsa el botón pulldown entonces entra a este if
    if (millis() > timeCounter + timeThreshold){
      for (int i = 0; i < 5 ; i++){ //Este ciclo apaga todos los leds
        digitalWrite(leds[i], LOW);
      } 
      count=0; //Se define contador en cero nuevamente para reiniciar el ciclo
      timeCounter = millis(); //Se almacena time counter en la función millis()
      Serial.println(count);
    }
  }
}
