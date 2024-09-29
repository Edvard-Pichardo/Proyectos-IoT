//Definimos los pines a ocupar, en este caso LEDs
#define LED1 14
#define LED2 27

void setup() {
  //Declaramos los pines como salida
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
}

void loop() {
  //Para encontrar la frecuencia del ojo humano debemos variar el delay de encendido y apagado
  //Comenzaré con 200 y de ahí iré bajando hnasta dejar de ver el parpadeo

  //Esta primer parte enciende los LEDs
  digitalWrite(LED1, HIGH);
  digitalWrite(LED2, LOW);
  delay(9);

  //Esta segunda parte apaga los LEDs
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, HIGH);
  delay(9);

  //Yo dejo de ver el parpadeo con 18 ms en el prgrama.
  //Si T=18 ms=18x10^-3 s es el periodo entonces la frecuencia a la que mis ojos dejan de ver el parpadeo es f=55.55 Hz
}
