# Proyectos de IoT

Este repositorio contiene varios proyectos correspondientes al curso de **Internet de las Cosas** dentro del **Seminario de Ciencias de la Computación** impartida por la **Facultad de Ciencias** de la **Universidad Nacional Autónoma de México**, principalmente desarrollados con una placa **ESP32**, enfocados en el monitoreo y control de dispositivos a través de servidores web locales.

# Introducción
El Internet de las cosas (IoT por sus siglas en inglés) es una técnica que permite conectar objetos a la red de Internet; desde elementos básicos como bombillas e interruptores, pasando por electrónicos y electrodomésticos hasta dispositivos complejos dentro de la industria e investigación. 

# Objetivos

Desde la última década, la interacción entre los dispositivos cotidianos y las personas ha experimentado una transformación significativa, lo que ha dado lugar al surgimiento de nuevas disciplinas en las ciencias e ingenierías. Un claro ejemplo de esto es el Internet de las Cosas (IoT), un campo con un enorme potencial, impulsado por los conocimientos adquiridos en áreas como programación, arquitectura de computadoras y redes durante la carrera de Ciencias de la Computación.

Estos proyectos tienen como propósito introducir al estudiante tanto en los conceptos fundamentales como en la programación de dispositivos y el diseño de sistemas enfocados en el Internet de las Cosas, utilizando herramientas de software libre y hardware accesible. Al concluir, el estudiante estará capacitado para diseñar e implementar sistemas autónomos o semiautónomos basados en las tecnologías más actuales del ámbito IoT.

# Proyectos

- El uso del módulo ESP32
- Manejo básico de señales digitales y analógicas
- El uso de protocolos de comunicación y mensajería
- Aplicaciones con bots y asistentes virtuales 
- Teoría básica de control
- Ciberseguridad
- Bases de datos
- AWS

# PINOUT ESP32

![PinMapEsp32IoT](https://github.com/user-attachments/assets/0956ec95-8941-47c0-adce-bab23bf4ade9)

# Tarjeta electrónica utilizada

![image140](https://github.com/user-attachments/assets/0558bc0e-7961-4d4e-8cdf-a3dd446f7611)


# Instalación
**INSTALACIÓN DEL IDE ARDUINO:**

1. Enlace de descarga: https://www.arduino.cc/en/software. Instala la verisión Arduino IDE 1.8.19. Si ya cuentas con la versión 2.0, desinstala esta última antes de instalar la 1.8, Instala desde la opción win7 and never. 

  - **Para Windows**: https://docs.arduino.cc/software/ide-v1/tutorials/Windows/
  - No instalar desde la tienda de Microsoft. 

  - **Para Linux**: https://docs.arduino.cc/software/ide-v1/tutorials/Linux

  - **Para Mac**: https://docs.arduino.cc/software/ide-v1/tutorials/macOS/

2. Después de completar la instalación, introduce el siguiente enlace en el Gestor de URL de Arduino dentro del menú de preferencias del IDE. https://dl.espressif.com/dl/package_esp32_index.json

3. Ve al Gestor de tarjetas (Herramientas -> Placa -> Gestor de Tarjetas) e instala ESP32 de Espressif Systems.

4. Compila el ejemplo Blink, cambiando "LED_BUILTIN" por "2". Si se compila, entonces todo ok.

**PONER EN MARCHA EL ESP32:**

1. Subir el código al ESP32.

2. Si la computadora no reconoce la tarjeta del ESP32, entonces se instala el drive del siguiente enlace: https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers?tab=downloads.

3. Para windows: Da clic en "CP210x Universal Windows Driver" e instala el archivo .sys que se adapte a la arquitectura de tu computadora.

  - **Para Linux**: Da clic en "Linux 2.6.x VCP Revision History" y sigue las instrucciones.

  - **Para Mac**: Da clic en "CP210x VCP Mac OSX Driver" e instala el archivo .dmg.

**Posibles errores al subir el código al ESP32**:

  - "ModuleNotFoundError: No module named 'serial'": Instalar el módulo Pyserial de python.

  - "PermissionError: Permision denied: '/dev/XXX'": Revisar los permisos del puerto serie, en algunas ocasiones con ejecutar el IDE de Arduino con sudo, es suficiente. Generalmente este es un error en Linux.

  - "Connecting.....___... A fatal error occurred": Presionar el botón "boot" del ESP32 mientras aparece la leyenda Connecting.....
