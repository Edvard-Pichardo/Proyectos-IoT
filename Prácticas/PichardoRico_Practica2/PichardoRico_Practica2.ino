#include "WiFi.h"
#include "ESPAsyncWebServer.h"
#include "SPIFFS.h"

// Pines para los LEDs
const int led1 = 14;
const int led2 = 27;
const int led3 = 26;
const int led4 = 25;
const int led5 = 33;

String sliderValue = "0";
String sliderValue2 = "0";
const char* PARAM_INPUT_1 = "output"; //Variable de led
const char* PARAM_INPUT_2 = "state"; //Variable de estado

// Pines para el potenciómetro y la fotoresistencia
const int potPin = 35;
const int photoResistorPin = 34;

// Variables para almacenar el estado de los LEDs y los valores analógicos
int led1State = LOW;
int led2State = LOW;
int led3State = LOW;
//int led4Brightness = 0;
//int led5Brightness = 0;
int potValue = 0;
int photoValue = 0;

//PWM propiedades------------------------------
const int freq = 1000;
const int ledChannel = 0;
const int resolution = 8;
const char* PARAM_INPUT = "value";

const int freq2 = 1000;
const int ledChannel2 = 1;
const int resolution2 = 8;
const char* PARAM_INPUT2 = "value5";

// Objeto AsyncWebServer, puerto 80
AsyncWebServer server(80);

//Credenciales Red-----------------------------
//const char* ssid = "Clase_IoT";
//const char* password = "0123456789";

const char* ssid = "Totalplay-B6AA";
const char* password = "B6AA8A65m6RwkHvj";

// Conexión WiFi
void setup_wifi() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  Serial.println("WiFi en modo estación establecido");
  
  delay(10);
  Serial.println();
  Serial.print("Conectando a: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());
  delay(2000);
}

String processor(const String& var) {
  //Encender o apagar los leds, usando HTML
  if (var == "BUTTONPLACEHOLDER") {
    String buttons = "";
    buttons += "<h4>LED 1</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"1\" " + outputState(led1) + "><span class=\"slider1\"></span></label>";
    buttons += "<h4>LED 2</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"2\" " + outputState(led2) + "><span class=\"slider2\"></span></label>";
    buttons += "<h4>LED 3</h4><label class=\"switch\"><input type=\"checkbox\" onchange=\"toggleCheckbox(this)\" id=\"3\" " + outputState(led3) + "><span class=\"slider1\"></span></label>";

    return buttons;
  }
  // Replaces placeholder with LED state value
  if (var == "SLIDERVALUE") {
    return sliderValue;
  }
  return String();
}

//Estado del led-------------------------------
String outputState(int output) {
  if (digitalRead(output)) {
    return "checked";
  }
  else {
    return "";
  }
}

// Función para leer el valor del potenciómetro y la fotoresistencia
String readSensorData() {
  potValue = analogRead(potPin);
  photoValue = analogRead(photoResistorPin);
  String sensorData = String(potValue) + "," + String(photoValue);
  return sensorData;
}




void setup() {
  // Iniciar comunicación serial
  Serial.begin(115200);
  setup_wifi();

  // Configurar los pines como salida
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  digitalWrite(led5, LOW);

  //Activar PWM--------------------------------
  ledcAttachChannel(led4, freq, resolution, ledChannel);
  ledcWrite(led4, sliderValue.toInt());
  
  ledcAttachChannel(led5, freq2, resolution2, ledChannel2);
  ledcWrite(led5, sliderValue.toInt());
  

  // Confirmar archivos subidos a la memoria flash
  if (!SPIFFS.begin(true)) {
    Serial.println("Error al leer SPIFFS");
    return;
  }

  // Comenzar el servidor
  server.begin();

  // GET HTML
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });

  // Archivo CSS
  server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/style.css", "text/css");
  });

  // Archivo JS
  server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/script.js", "text/js");
  });

  // Ruta para obtener los datos de los sensores
  server.on("/sensorData", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(200, "text/plain", readSensorData());
  });

  //Petición a "/update" con el método GET
  server.on("/update", HTTP_GET, [] (AsyncWebServerRequest * request) {
    String inputMessage1;
    String inputMessage2;
    
    //Se obtienen los parámetros de <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
    if (request->hasParam(PARAM_INPUT_1) && request->hasParam(PARAM_INPUT_2)) {
      inputMessage1 = request->getParam(PARAM_INPUT_1)->value();
      inputMessage2 = request->getParam(PARAM_INPUT_2)->value();
      

    // Actualizar el estado de los LEDs basándose en el ID
    if (inputMessage1 == "led1") {
        digitalWrite(led1, inputMessage2.toInt());
        Serial.print(inputMessage1);
        Serial.print(": ");
        Serial.println(inputMessage2);
      } else if (inputMessage1 == "led2") {
        digitalWrite(led2, inputMessage2.toInt());
        Serial.print(inputMessage1);
        Serial.print(": ");
        Serial.println(inputMessage2);
      } else if (inputMessage1 == "led3") {
        digitalWrite(led3, inputMessage2.toInt());
        Serial.print(inputMessage1);
        Serial.print(": ");
        Serial.println(inputMessage2);
      }
    }

    //Responder a la solicitud con un código de estado 200 (OK) y un mensaje en texto plano
    request->send(200, "text/plain", "OK");
  });
  

  server.on("/slider", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      sliderValue = inputMessage;
      ledcWrite(led4, sliderValue.toInt());
    }
    else {
      inputMessage = "Mensaje no enviado";
    }
    Serial.print("led4");
    Serial.print(": ");
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

  server.on("/slider2", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    if (request->hasParam(PARAM_INPUT2)) {
      inputMessage = request->getParam(PARAM_INPUT2)->value();
      sliderValue2 = inputMessage;
      ledcWrite(led5, sliderValue2.toInt());
    }
    else {
      inputMessage = "Mensaje no enviado";
    }
    Serial.print("led5");
    Serial.print(": ");
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");
  });

  // Función para error 404
  server.onNotFound([](AsyncWebServerRequest *request) {
    request->send(404, "text/plain", "Error 404");
  });
}

void loop() {
  
}
