//Práctica 1: Bluetooth

//Incluimos la librería de bluetooth
#include "BluetoothSerial.h"
//Incluimos la librería para el sensor DHT
#include "DHT.h"


//Condición para habilitar el bluetooth
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


//Definimos los pines a utilizar 
#define LED1 14
#define LED2 27
#define LED3 26
#define LED4 25
#define LED5 33
#define SW1 15 //Pull Down
#define SW2 4 //Pull Up
#define DHTPIN 32 //Pin DHT
#define DHTTYPE DHT11  //DHT 11


//Definimos los leds que se usarán en un arreglo
const int leds[5] = {LED1, LED2, LED3, LED4, LED5};


BluetoothSerial BT; //Objeto Bluetooth
DHT dht(DHTPIN, DHTTYPE); //Objeto DHT


//Variables para el funcionamiento del botón
long timeCounter1 = 0;
long timeCounter2 = 0;
int timeThreshold = 250;



//Función de llamada haciendo referencia al objeto BT
void callback_function(esp_spp_cb_event_t event, esp_spp_cb_param_t *param) {
  switch (event) {
    case ESP_SPP_START_EVT:
      Serial.println("Inicializado SPP");
      break;
    case ESP_SPP_SRV_OPEN_EVT:
      Serial.println("Cliente conectado");
      break;
    case ESP_SPP_CLOSE_EVT:
      Serial.println("Cliente desconectado");
      break;
    case ESP_SPP_DATA_IND_EVT:
      while(BT.available()){ //Mientras haya datos por recibir
        int val = BT.read(); //Leemos un byte de los datos recibidos    
        if (val == '\n' || val == '\r') {
          continue; // Saltar a la siguiente iteración del bucle si es '\n' o '\r'
        }
        Serial.println(val);
        if(val == 49) { //1 en ASCII
          digitalWrite(LED1, HIGH);
        }
        else if(val == 50){ //2 en ASCII
          digitalWrite(LED2, HIGH);
        }
        else if(val == 51){ //3 en ASCII
          digitalWrite(LED3, HIGH);
        }
        else if(val == 52){ //4 en ASCII
          digitalWrite(LED4, HIGH);
        }
        else if(val == 53){ //5 en ASCII
          digitalWrite(LED5, HIGH);
        }
        else if(val == 48){ //0 en ASCII
          for (int i = 0; i < 5 ; i++) {
            digitalWrite(leds[i], LOW);
          }
        }
        else{
          BT.println("Error, ingrese un comando válido");
        }
      }
      break;
  }
}



void setup() {
  Serial.begin(115200); //Inicializar la comunicación serial
  
  //Definimos los pines como salida dentro de un ciclo for
  for (int i = 0; i < 5 ; i++) {
    pinMode(leds[i], OUTPUT);
  }
  //Declaramos los pines de los botones como entrada
  pinMode(SW1, INPUT); 
  pinMode(SW2, INPUT); 
  
  
  BT.begin("ESP32_EPichardo"); //Nombre de su dispositivo Bluetooth y en modo esclavo
  Serial.println("El dispositivo Bluetooth está listo para emparejarse");
  BT.register_callback(callback_function); //Devolución de la función callback

  Serial.println(F("DHTxx test!")); //Iniciamos la detección del DHT
  dht.begin();

  
}



void loop() {  
  if(digitalRead(SW1)==1){ //Si se aprieta el botón 1 leemos la temperatura
    if (millis() > timeCounter1 + timeThreshold) {
      float t=dht.readTemperature(); //Leemos el valor de la temperatura en C
      float f=dht.readTemperature(true); //Leemos el valor de la temperatura en F

      //Checamos si el sensor lee bien los datos de la temperatura
        if (isnan(t) || isnan(f)){
        BT.println(F("Error al leer la temperatura desde el sensor DHT"));
        return;
      }
      
      BT.print(F("Temperatura: "));
      BT.print(t);
      BT.print(F("°C "));
      BT.print(F("; "));
      BT.print(f);
      BT.println(F("°F"));
      timeCounter1 = millis();
    }
  }
  if(digitalRead(SW2)==0){ //Si se aprieta el botón 2 leemos la humedad
    if (millis() > timeCounter2 + timeThreshold) {
      float h = dht.readHumidity(); //Leemos el valor de la húmedad

      //Checamos si el sensor lee la humedad
      if(isnan(h)){
        BT.println(F("Error al leer la humedad desde el sensor DHT"));
        return;
      }
    
      BT.print(F("Humedad: "));
      BT.print(h);
      BT.println(F("%"));
      timeCounter2 = millis();
    }
  }
}
