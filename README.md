# Transmisor
 Aqui se encuentra el codigo del sistema de telemetria para el rover challenge.
 Este dispositivo es el encargado de recolectar todos los datos del viaje, para que así estos 
 Se tendra una revision tanto más **técnica** como detalles acerca de la programación.
 
 - Configuración de Pines y e Interfaces de Comunicación
 - Inicializacion de Componentes
     - Antena de Comunicación NRF24L01
     - GPS neo 6m
     - Pantalla LCD
     - Acelerómetro MPU6050
     - Sensor BMP280
 - Programa principal
  
## Configuración de Pines e Interfaces de Comunicación
Para poder aclarar la distribucion de los pines, cabe mencionar que para este proyecto estamos usando una placa de STmicroelectronics, mas precisamente la placa **stm32 nucleo f767zi** y el microcontrolador que lleva dentro es el
STM32F767ZIT6, para mas detalles chekear el link https://os.mbed.com/platforms/ST-Nucleo-F767ZI/.

![D_NQ_NP_984911-MEC31657097566_082019-O](https://user-images.githubusercontent.com/47458067/75688224-80cbf280-5c75-11ea-8056-dca3b89d8adb.jpg)

La configuración de los pines del microcontrolador es importante, para poder saber a que pines van conectados cada componente que se utiliza y se comunica con el MCU.
Aqui tenemos las imagenes:

![Captura de Pantalla 2020-03-02 a la(s) 10 42 20](https://user-images.githubusercontent.com/47458067/75687280-efa84c00-5c73-11ea-9192-715d04c2c1db.png)

![Captura de Pantalla 2020-03-02 a la(s) 10 43 56](https://user-images.githubusercontent.com/47458067/75687329-06e73980-5c74-11ea-9154-d7a7739efd7b.png)

![Captura de Pantalla 2020-03-02 a la(s) 10 43 38](https://user-images.githubusercontent.com/47458067/75687377-1797af80-5c74-11ea-87a9-ff5eb6385fc6.png)

![Captura de Pantalla 2020-03-02 a la(s) 10 42 58](https://user-images.githubusercontent.com/47458067/75687423-28e0bc00-5c74-11ea-85eb-f80f47c5bd80.png)

## Inicializacion de Componentes
En este apartado se detallará cada inicializacion por componente, es importante saber que tipo de configuracion es tienen para poder aprovechar todas sus bondades al máximo.

### Antena de Comunicación NRF24L01
Este componente trabaja sobre los 2,4Ghz, tiene codificación por tubos de direcciones de hasta 5 bytes (0 - (2ˆ(40)-1) ) y  canales rf (0-124), también tenemos la opción de poder elegir la velocidad a la que trabaja. Nos da la posibilidad de comunicarnos con la central de tierra y transmitir todos los datos obtenidos.

![Captura de Pantalla 2020-03-02 a la(s) 11 16 12](https://user-images.githubusercontent.com/47458067/75689556-c4bff700-5c77-11ea-880e-24cf4e0d10b9.png)

### GPS neo 6m
Este GPS nos da la posibilidad de obtener datos como Latitud y Longitud, para poder asi saber en que parte del mundo nos encontramos, la altura, velocidad, hora, fecha,etc. Trabaja sobre el protocolo NMEA (National Marine Electronics Association).

![Captura de Pantalla 2020-03-02 a la(s) 11 27 19](https://user-images.githubusercontent.com/47458067/75690181-ca6a0c80-5c78-11ea-9bf2-fc089c6ed2f8.png)

### Pantalla LCD
Este componente simplemente nos ayudará a visualizar los datos obtenidos por todo el sistema.

![Captura de Pantalla 2020-03-02 a la(s) 11 32 27](https://user-images.githubusercontent.com/47458067/75690593-8297b500-5c79-11ea-94a3-f266489fd455.png)

### Acelerómetro MPU6050
Este pequeño acelerómetro nos ayudará a obtener los angulos de Euler para poder orientarnos (Pitch y Roll).

![Captura de Pantalla 2020-03-02 a la(s) 11 34 16](https://user-images.githubusercontent.com/47458067/75690751-c25e9c80-5c79-11ea-9947-fff552c1cd35.png)

### Sensor BMP280
Este sensor se encarga de obtener los datos de: Temperatura, Presión y Humedad. A su vez al tener el dato de presión, puede calcularse la altura a la que se encuentra, respecto al nivel del mar u otra altura relativa (suelo).

![Captura de Pantalla 2020-03-02 a la(s) 11 36 20](https://user-images.githubusercontent.com/47458067/75690935-0fdb0980-5c7a-11ea-86ea-cbab0720f7b4.png)

## Programa Principal
Se explicará acerca de lo que hace cada pedazo de código para asi tener un mejor entendimiento de cómo funciona 
(Divide y vencerás).

### Obtención de datos
Este pedazo de codigo se encarga de recolectar todos los datos, lee todos los sensores e interfaces de comunicación, lo hace cada milisegundo, en el caso del acelerómetro es necesario que las muestras se hagan con la mayor frecuencia posible, esto debido a que, para obtener los ángulos se está utilizando un filtro de complemento (ver Core/Src/mpu6050.c mpu_get_angles()) que va arreglando los errores debido al ruido que el acelerómetro produce.

![Captura de Pantalla 2020-03-02 a la(s) 11 53 47](https://user-images.githubusercontent.com/47458067/75692823-7b25db00-5c7c-11ea-924e-9df74315a0ec.png)

### Obtención de datos del sensor de pulso cardiaco
Este sensor se encuentra fuera de la anterior función debido a que se le puede dar distinto tiempo de actualizacion para su posterior muestreo en tiempo real por el puerto serial.

![Captura de Pantalla 2020-03-02 a la(s) 11 59 49](https://user-images.githubusercontent.com/47458067/75693446-53834280-5c7d-11ea-81ea-17dc155f67bd.png)

### Empaquetado y envío de datos
Dado que la antena solo puede transmitir 32 bytes por vez (aunque su data rate es elevado) es necesario acomodar los datos para su posterior envío, de esta manera la función de envío sera mucho más eficiente y se podrán enviar mas datos en menos tiempo. En nuestro caso, los datos excenden normalmente los 32 bytes, entonces es necesario contar con 2 tipos de mensajes y poder alternar entre ellos para cada envío.

![Captura de Pantalla 2020-03-02 a la(s) 12 04 04](https://user-images.githubusercontent.com/47458067/75693816-ec19c280-5c7d-11ea-957a-66fe1266b6da.png)

### Visualizacion de Datos por LCD y Bluetooth
Esta parte del codigo sirve para poder mostrar los datos a través de la pantalla LCD y envío por bluetooth, el envío por bluetooth se hace hacia una app en Android configurada para su muestreo.

#### Muestreo por LCD
![Captura de Pantalla 2020-03-02 a la(s) 12 10 14](https://user-images.githubusercontent.com/47458067/75694366-c93bde00-5c7e-11ea-9e3d-3eb8ff1dc54a.png)

#### Muestreo por Bluetooth
![Captura de Pantalla 2020-03-02 a la(s) 12 11 27](https://user-images.githubusercontent.com/47458067/75694467-f4263200-5c7e-11ea-8dc9-9b822fca1e00.png)

### Función de offset de acelerometro por botón.
Para poder ser más prácticos a la hora de calibrar el sistema de telemetría, se incluye una implementación de código para hacerle un offset, y así poderlo configurar rapidamente.

![Captura de Pantalla 2020-03-02 a la(s) 12 16 27](https://user-images.githubusercontent.com/47458067/75694917-a78f2680-5c7f-11ea-8c69-78fb06c9b267.png)


##
