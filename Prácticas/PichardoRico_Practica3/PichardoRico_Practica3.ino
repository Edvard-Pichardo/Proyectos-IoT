//Práctica 3: MQTT
//Pichardo Rico Cristian Eduardo

//Biblioteca para MQTT
#include <EspMQTTClient.h>
#include <DHT.h>

#define PinBotton_PullUp 4  //Boton 1
#define PinBotton_PullDown 15 //Boton 2
#define luz 34  // LDR
#define pot 35       // Potenciómetro
#define led1 14      // LED 1
#define led2 27      // LED 2
#define led3 26      // LED 3
#define led4 25      // LED 4 
#define led5 33      // LED 5
#define pinDHT 32    // Pin para DHT11
#define DHTTYPE DHT11

//Definimos los leds que se usarán en un arreglo
const int leds[5] = {led1, led2, led3, led4, led5};

//Variables de configuración del objeto MQTT cliente
//const char* ssid = "Clase_IoT";
//const char* password = "0123456789";
const char* ssid = "Totalplay-B6AA";
const char* password = "B6AA8A65m6RwkHvj";
const char* broker = "test.mosquitto.org";  // Dirección del broker
const char* nameClient = "ESP32_Pichardo";    // Nombre del dispositivo
const int port = 1883;                       // Puerto

//Tópicos
String topicSubLed = "ClaseIoT/Pichardo/Led";
String topicPubLuz = "ClaseIoT/Pichardo/Fotoresistencia";
String topicPubPot = "ClaseIoT/Pichardo/Potenciometro";
String topicPubHum = "ClaseIoT/Pichardo/DHT/Humedad";
String topicPubTemp = "ClaseIoT/Pichardo/DHT/Temperatura";

//Definimos 3 variables para el contador
long timeCounter = 0; //Variable que almacenará la función del millis; comienza en cero
const int timeThreshold = 350; //Contador umbral
long timeDHT = 0; //tiempo auxiliar para publicación de DHT

//Inicializamos el sensor DHT
DHT dht(pinDHT, DHTTYPE);

//Objeto cliente
EspMQTTClient client(ssid, password, broker, nameClient, port);

void setup() {
  Serial.begin(115200); //Comunicación Serial
  dht.begin(); // Inicializa el DHT
  pinMode(luz, INPUT); 
  pinMode(pot, INPUT);
  pinMode(PinBotton_PullUp, INPUT); //Declaramos botón pullup
  pinMode(PinBotton_PullDown, INPUT); //Declaramos el botón pulldown
  
  //Definimos los leds como salida dentro de un ciclo for
  for (int i = 0; i < 5 ; i++) {
    pinMode(leds[i], OUTPUT);
  }  

  //Conexión con el broker
  if (!client.isConnected()) {
    Serial.println("¡Conectado con el broker!");
  }
  else {
    Serial.println("No Conectado, revise su conexión");
  }
  delay(5000);
}

void onConnectionEstablished(){
  // Suscripción al tópico para encender LEDs
  client.subscribe(topicSubLed, [](const String & payload) {
    handleLedControl(payload);
  });
}

void handleLedControl(const String & payload) {
  int ledValue = payload.toInt();
  
  // Control de los LEDs basado en el valor recibido
  if (ledValue == 1) {
    digitalWrite(led1, HIGH);
    Serial.println("Led 1 encendido");
  } 
  else if (ledValue == 2) {
    digitalWrite(led2, HIGH);
    Serial.println("Led 2 encendido");
  } 
  else if (ledValue == 3) {
    digitalWrite(led3, HIGH);
    Serial.println("Led 3 encendido");
  } 
  else if (ledValue == 4) {
    digitalWrite(led4, HIGH);
    Serial.println("Led 4 encendido");
  } 
  else if (ledValue == 5) {
    digitalWrite(led5, HIGH);
    Serial.println("Led 5 encendido");
  } 
  else if (ledValue == 0) {
    for (int i = 0; i < 5 ; i++) {
      digitalWrite(leds[i], LOW);
    }  
    Serial.println("Todos los leds se han apagado");
  }
  else if(ledValue == 6){
    for (int i = 0; i < 5 ; i++) {
      digitalWrite(leds[i], LOW);
    }  
    for (int i = 0; i < 5 ; i=i+2) {
      digitalWrite(leds[i], HIGH);
    } 
    Serial.println("Leds impares encendidos");
  }
  else if(ledValue == 7){
    for (int i = 0; i < 5 ; i++) {
      digitalWrite(leds[i], LOW);
    }  
    for (int i = 1; i < 5 ; i=i+2) {
      digitalWrite(leds[i], HIGH);
    } 
    Serial.println("Leds pares encendidos");
  }
  else if(ledValue == 8){
    Serial.println("Tren encendido");
    for (int i = 0; i < 5 ; i++) {
      digitalWrite(leds[i], LOW);
    }  
    for (int i = 0; i < 5 ; i++) {
      digitalWrite(leds[i], HIGH);
      delay(800);
    } 
  }
  else if(ledValue == 9){
    Serial.println("Tren apagado");
    for (int i = 0; i < 5 ; i++) {
      digitalWrite(leds[i], HIGH);
    }  
    for (int i = 4; i>=0 ; i--) {
      digitalWrite(leds[i], LOW);
      delay(800);
    } 
  }
  else{
    Serial.println("Valor no válido");
    }
}

void loop() {
  client.loop(); // Manejador del cliente MQTT

  //Estados de los botones
  int in_up = digitalRead(PinBotton_PullUp); 
  int in_down = digitalRead(PinBotton_PullDown); 

  //Fotoresistencia
  if(in_up == LOW){ //Si el botón pullup es presionado entonces entrará a este if
    if(millis() > timeCounter + timeThreshold){ //Si el tiempo de ejecución es mayor al tiempo umbral más el tiempo de conteo entonces entra a este if
      int sensorLuz = analogRead(luz);
      client.publish(topicPubLuz, String(sensorLuz)); //Publica el valor del LDR
      Serial.print("El valor de la fotoresistencia es: ");
      Serial.println(sensorLuz);
      
      timeCounter = millis(); //Se almacena timeCounter en la función millis()    
      }
  }

  //Potenciometro
  if(in_down == HIGH){ //Si se pulsa el botón pulldown entonces entra a este if
    if (millis() > timeCounter + timeThreshold){
      int sensorPot = analogRead(pot);
      client.publish(topicPubPot, String(sensorPot)); //Publica el valor del potenciómetro
      Serial.print("El valor del potenciometro es: ");
      Serial.println(sensorPot);
      
      timeCounter = millis(); //Se almacena time counter en la función millis()
    }
  }
 

  //DHT: temperatura y humedad (cada 5 segundos)
  if (millis() - timeDHT > 5000){
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    
    if (isnan(h) || isnan(t)){
      Serial.println("Error al leer el sensor DHT");
      return;
    }

    //Publica la humedad y temperatura
    client.publish(topicPubTemp, String(t));
    client.publish(topicPubHum, String(h));
    Serial.print("Humedad: ");
    Serial.print(h);
    Serial.print(" % -- Temperatura: ");
    Serial.print(t);
    Serial.println(" °C");

    timeDHT = millis();
  }
}
