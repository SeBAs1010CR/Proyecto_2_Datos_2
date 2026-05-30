# Proyecto_2_Datos_2

## Configuración del entorno local

Para compilar correctamente el proyecto, necesitas la biblioteca **SFML 3.0**. Descárgala desde la página oficial y asegúrate de escoger la versión de **64 bits**; de lo contrario pueden aparecer incompatibilidades con el entorno de desarrollo.

Una vez descargada, abre Visual Studio y entra a las propiedades del proyecto. Allí tienes que indicar las rutas de las carpetas de cabeceras y bibliotecas. Ve a la configuración de **C/C++** para agregar la carpeta de inclusión, y en la sección del **Vinculador** añade la carpeta de bibliotecas adicionales. Con esto, el compilador localiza las funciones gráficas y del motor que el código fuente necesita durante la construcción.

## Colocación de dependencias para la ejecución

El proyecto incluye en su raíz una carpeta de dependencias que ya contiene todos los archivos **.dll** necesarios. Una vez generado el ejecutable, copia esos archivos .dll y pégalos en la misma carpeta donde está el ejecutable. De este modo, al abrir la aplicación, el sistema operativo encuentra inmediatamente los módulos y el juego se ejecuta sin problemas.

## Funcionamiento del juego

Al iniciar la aplicación entras a un entorno de batalla multijugador con un sistema estricto de turnos. Los turnos se alternan entre bandos, y en cada fase eliges uno de tus tanques activos para realizar una acción antes de ceder el control.

El manejo se realiza con el ratón de forma gráfica e intuitiva. Para mover una unidad, haces clic en la casilla de la cuadrícula que quieras alcanzar. El programa calcula automáticamente la ruta óptima usando **búsqueda en anchura** o el **algoritmo de Dijkstra**, dependiendo de la facción del tanque. En ciertos casos se activa un sistema de línea de vista aleatorio que genera un movimiento evasivo dentro del escenario.

Para atacar, seleccionas un objetivo con el puntero. El tanque gira sobre sí mismo hasta alcanzar el ángulo exacto determinado por trigonometría, luego dispara un proyectil. Este proyectil viaja rebotando en los obstáculos sólidos del laberinto hasta impactar a un tanque enemigo, reduciendo sus indicadores visuales de salud.

Justo antes de cada disparo, el sistema consulta la cola de habilidades especiales. Si el jugador tiene un modificador disponible, el ataque convencional se convierte en un **misil teledirigido** guiado por el **algoritmo A***, lo que asegura un impacto directo. Esto añade un nivel adicional de planificación táctica a las decisiones de cada turno.
