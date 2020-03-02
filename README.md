# Transmisor
 Aqui se encuentra el codigo del sistema de telemetria para el rover challenge.
 Este dispositivo es el encargado de recolectar todos los datos del viaje, para que así estos 
 Se tendra una revision tanto más **técnica** como detalles acerca de la programación.
 
 - Configuración de Pines y e Interfaces de Comunicación
 - Inicializacion de Componentes
 

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
Este GPS nos da
