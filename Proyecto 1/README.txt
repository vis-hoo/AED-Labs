The Guardians Tournament - Proyecto Unidad 1
Vicente Falcón Arancibia

Se solicita la creación de un juego de batalla por turnos, entre un personaje (Guardián)
elegido por el jugador, y una determinada cantidad de enemigos seleccionados aleatoriamente.
El juego fue desarrollado en lenguaje C, utilizando structs, constantes define, punteros, listas,
colas, enum y cargado de datos desde un archivo de texto externo.

Problema: Estructura del Guardián.
      Se pide que los guardianes tengan nombre, tipo (mago, vikingo, nigromante o bestia),
     cantidad de vida, puntos de ataque y puntos de defensa.
Solución: Se crea un struct del tipo Guardián, con char name, enum guardianType type, float
     health, int attack, float defense y struct Guardian next.
     Para el tipo de Guardián se utilizó un enum para poder elegir 1 de 4 opciones posibles.
     Las variables del tipo float se pensaron como variable que luego, por algún tipo de
     descuento, podrían tener valores decimales.

Problema: Combate por turnos.
      Se solicita que el combate se realice por turnos, donde el jugador puede elegir si ataca
     o defiende, luego lanza un dado, y dependiendo de las decisiones elegidas, se realiza un
     cálculo de daño tanto para el jugador como para el enemigo. En este aspecto, no se especifica
     cómo debe atacar el enemigo.
Solución: Al realizar los cálculos de los daños, se consideran los valores solicitados en la pauta.
     Sin embargo, para el daño realizado por el enemigo hacia el jugador, se utiliza el 20% del valor
     de ataque original. La razón detrás de esto es que el juego se volvía muy complicado si el enemigo
     atacaba en todos los turnos con el 100% del valor de su ataque.
     Con este valor del 20% se vuelve difícil competir en torneo Intermedio y Avanzado, pero no imposible.

Problema: Historial del jugador.
      Se solicita que exista una opción para observar el historial de batallas del jugador.
Solución: En cada torneo que se inicia, creo un nodo en una lista de structs History. Cada uno de estos
     nodos tiene la siguiente información: int tournamentDifficulty, Guardian *player, bool won, int
     defeatedEnemies, struct history *next.
     Luego, al imprimirse el Historial del jugador, se muestra el personaje con el que jugó el usuario, la
     dificultad del torneo en el que participó, si ganó o perdió, y la cantidad de enemigos derrotados.

El resto de elementos se desarrollaron de forma bastante similar a la solicitada en la pauta.