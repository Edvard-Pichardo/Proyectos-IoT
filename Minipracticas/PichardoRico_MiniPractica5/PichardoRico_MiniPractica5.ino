//Mini Práctica 05
//Conectar PinPWM a PinADC y PinADCPWM a PinADCDAC

//Definimos pines
#define PinPWM 26
#define PinDAC 25
#define PinADCPWM 13
#define PinADCDAC 12

//Variables para definir el PWM
const int freq = 1000; //Frecuencia en Hz
const int ChanelPWM = 0; //Canal 0 - 15
const int resolution = 8; //Bits de resolución, hasta 8
const int timedelay = 10000; //delay microseconds
bool state = true; //Variable de estado

void setup() {
  Serial.begin(115200); //Iniciamos comunicación serial
  pinMode(PinPWM, OUTPUT);
  pinMode(PinDAC, OUTPUT);
  pinMode(PinADCPWM, INPUT);
  pinMode(PinADCDAC, INPUT);
  ledcAttachChannel(PinPWM, freq, resolution, ChanelPWM); //Configuración del PWM
  //Nota: Para apagar  el LED1 podemos mandar la instrucción por aquí
}

void loop() {
//Definimos un ciclo for para las funciones senoidales para el DAC y PWM 
   for (int i = 0; i < 360; i++) {
    float seno = (127*sin(i*M_PI/180)+127); //Definimos la función seno
    float umbral = 2.52/3.3*255;  //Definimos el umbral del led azul para el DAC (2.48V)
    float seno_DAC = seno*((255 - umbral)/255)+umbral;  //Ajustamos la función seno para el DAC

    dacWrite(PinDAC, seno_DAC); //Escribimos en el DAC
    ledcWrite(PinPWM, seno); //Escribimos en el PWM
    Serial.print("PWM:");
    Serial.print(analogRead(PinADCPWM));
    Serial.print(",");
    Serial.print("DAC:");
    Serial.println(analogRead(PinADCDAC));
    delayMicroseconds(timedelay); 
  }

}
