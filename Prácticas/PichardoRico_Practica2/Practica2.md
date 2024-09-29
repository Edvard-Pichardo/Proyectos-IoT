# Seminario de Ciencias de la Computación A: Introducción al Internet de las Cosas
**Facultad de Ciencias, UNAM**

# Práctica 2: Servidor Web

**Objetivos**:

Desarrolle un servidor web local utilizando el ESP32. Diseñe una interfaz de usuario que
permita monitorear los valores en tiempo real del potenciómetro y la fotoresistencia.
Además, habilite la capacidad de ajustar el brillo de los LEDs 4 y 5 mediante PWM, así
como de encender y apagar los LEDs 1, 2 y 3 de manera interactiva.

# Importante:

**Librerías necesarias**:

1. ESPAsyncWebServer:

Esta librería permite implementar el servidor web asíncrono. Para instalarla:
- **Repositorio GitHub**: https://github.com/me-no-dev/ESPAsyncWebServer

2. AsyncTCP:

Es necesaria para que funcione ESPAsyncWebServer en el ESP32. Para instalarla:
- **Repositorio GitHub**: https://github.com/me-no-dev/AsyncTCP

3. SPIFFS:
Esta librería viene incluida con el core de ESP32, que permite el uso de SPIFFS (sistema de archivos).
- **Repositorio GitHub**: https://github.com/me-no-dev/arduino-esp32fs-plugin/releases/
- Después de descargarlo descomprímelo en la dirección C:\Program Files (x86)\Arduino\tools.
- Si tenías Arduino IDE abierto ciérralo y vuélvelo a abrir. Ve al menú herramientas y busca ESP32 Sketch Data Upload para verificar que cuentas con la herramienta.

Más información: https://todomaker.com/blog/esp32-spiffs/
