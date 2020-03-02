# Transmisor
 Aqui se encuentra el codigo del sistema de telemetria para el rover challenge.
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
