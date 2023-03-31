using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana3_ejercicio4
{
    internal class Player
    {
        /* Atributos de los Jugadores.
         * Name: Nombre del jugador. Asignado por el usuario.
         * Health: Vida del jugador. Valor generado de manera aleatoria en un rango de 75 a 150.
         * Level = Nivel del jugador. Valor generado de manera aleatoria en un rango de 1 a 3. Funciona
         *      como un multiplicador del ataque. Es decir, si el ataque de un jugador es 10, y su nivel
         *      es 3, entonces el daño causado es 30.
         * Strength = Fuerza del jugador. Valor generado de manera aleatoria en un rango de 1 a 10.
         * Score = Puntaje del jugador. Inicia en 0. Al realizar un ataque exitoso, se suman 5 puntos. Sin
         *      embargo, si el ataque logra matar al enemigo,se suman 15 puntos.
         */
        public string Name { get; private set; }
        public int Health { get; private set; }
        public int Level { get; private set; }
        public int Strength { get; private set; }
        public int Score { get; private set; }

        public Player(string name, int health, int level, int strength, int score)
        {
            Name = name;
            Health = health;
            Level = level;
            Strength = strength;
            Score = score;
        }

        // Menú del jugador. Da las opciones de Atacar o Ver estadísticas.
        public void PlayerAction(Game g, Player[] team, int t)
        {
            if (Game.IntInput("\nSeleccione una opción.\n 1. Atacar.\n 2. Ver estadísticas.\nIngrese el número de la opción: ",
                1, 2) == 2)
            {
                Console.Write("\n  " + Name + "\n Vida: " + Health + "\n Nivel: " + Level + "\n Fuerza: " + Strength +
                    "\n Puntaje: " + Score + "\n\nPresiona cualquier tecla para continuar.");
                Console.ReadKey();
            }
            else Attack(g, team, t);
        }

        // Función que controla el ataque del jugador.
        private void Attack(Game g, Player[] team, int t)
        {
            Player enemy = Game.SelectPlayer(g, team, t);
            int multiplier = ThrowDie();
            int damage = Strength * Level * multiplier;
            Console.Write("\n\n\tHas lanzado el dado. Tu multiplicador es: " + multiplier + ".\n\tDaño = (Fuerza:" + Strength +
                ") * (Nivel:" + Level + ") * (Multiplicador:" + multiplier + ") = " + damage +
                ".\n\nPresiona cualquier tecla para continuar.");
            if (enemy.Health - damage < 0)
            {
                enemy.Health = 0;
                Score += 15;
            }
            else
            {
                enemy.Health -= damage;
                if (damage != 0) Score += 5;
            }
            Console.ReadKey();
        }

        /* Lanzamiento del Dado.
         * Esta función simula un dado de 10 caras, en el que existen los siguientes valores: 0, 1, 2 y 3.
         * El valor 0 tiene un 10% de probabilidades de salir.
         * El valor 1 tiene un 50% de probabilidades de salir.
         * El valor 2 tiene un 30% de probabilidades de salir.
         * El valor 3 tiene un 10% de probabilidades de salir.
         * El valor entregado por el dado funciona como un multiplicador extra del daño. Es decir, si el daño básico
         *      del jugador (Fuera * Nivel) es x, entonces el daño realizado puede ser 0x, 1x, 2x o 3x.
         * El daño 0x no se considera como un ataque exitoso, por lo que no suma puntos al jugador que lo realiza.
         */
        private int ThrowDie()
        {
            Random r = new Random();
            int n = r.Next(10);
            if (n == 0) return 0;
            if (n >= 1 && n <= 5) return 1;
            if (n >= 6 && n <= 8) return 2;
            return 3;
        }
    }
}
