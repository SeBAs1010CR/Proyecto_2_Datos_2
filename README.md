# Proyecto_2_Datos_2

## Configuración del entorno local

Para compilar correctamente el proyecto, necesitas la biblioteca **SFML 3.0**. Descárgala desde la página oficial y asegúrate de escoger la versión de **64 bits**; de lo contrario pueden aparecer incompatibilidades con el entorno de desarrollo.

Una vez descargada, abre Visual Studio y entra a las propiedades del proyecto. Allí tienes que indicar las rutas de las carpetas de cabeceras y bibliotecas. Ve a la configuración de **C/C++** para agregar la carpeta de inclusión, y en la sección del **Vinculador** añade la carpeta de bibliotecas adicionales. Con esto, el compilador localiza las funciones gráficas y del motor que el código fuente necesita durante la construcción.

## Colocación de dependencias para la ejecución

El proyecto incluye en su raíz una carpeta de dependencias que ya contiene todos los archivos **.dll** necesarios. Una vez generado el ejecutable, copia esos archivos .dll y pégalos en la misma carpeta donde está el ejecutable. De este modo, al abrir la aplicación, el sistema operativo encuentra inmediatamente los módulos y el juego se ejecuta sin problemas.

## Funcionamiento del juego

Al iniciar la aplicación entras a un entorno de batalla multijugador con un sistema estricto de turnos. Los turnos se alternan entre bandos, el jugador 1 tiene al tanque rojo y azul (siempre comienza) mientras que el jugador 2 tiene a los tanques celeste y amarillo.

El manejo se realiza con el ratón de forma gráfica e intuitiva. Para mover una unidad, haces clic en la casilla del tanque y luego de la cuadrícula que quieras alcanzar. El programa calcula automáticamente la ruta óptima usando **búsqueda en anchura** o el **algoritmo de Dijkstra**, dependiendo de la facción del tanque. En ciertos casos se activa un sistema de línea de vista aleatorio que genera un movimiento evasivo dentro del escenario.

Para atacar, seleccionae el tanque que va a atacar con click izquierdo y con click derecho seleccionas un objetivo con el puntero (no una distancia mas de dos bloques alejada del tanque). El tanque gira sobre sí mismo hasta alcanzar el ángulo exacto determinado por trigonometría, luego dispara un proyectil. Este proyectil viaja rebotando en los obstáculos sólidos del laberinto hasta impactar a un tanque enemigo, reduciendo sus indicadores visuales de salud.

Si presionas shift en vez de disparar o mover un tanque, entonces en tu inventario se almacenará un power-up aleatorio, hay cuatro opciones.
Doble turno (aplica al siguiente turno).
Poder de ataque: la siguiente bala destruye automáticamente al tanque que impacta.
Precisión de ataque: la siguiente bala va en A* esquivando todos los obstáculos y ya no tiene límite para escoger la distancia del objetivo.
Precisión de movimiento: el porcentaje de probabilidad de usar linea vista en el movimiento se reduce a un 10%.
Al final siempre despues de adquirir un power_up tu turno acaba y sigue el rival.
