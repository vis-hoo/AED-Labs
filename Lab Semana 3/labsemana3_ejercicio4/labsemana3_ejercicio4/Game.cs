using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace labsemana3_ejercicio4
{
    /* Las dos constantes utilizadas en este programa.
     * MAXPLAYERS: Cantidad máxima de jugadores por equipo.
     * TURNS: Cantidad máxima de turnos jugables antes de que termine el juego.
     */
    static class Constants { public const int MAXPLAYERS = 5; public const int TURNS = 20; }

    internal class Game
    {
        /* Atributos del Juego.
         * team1-team2: Los dos equipos de jugadores.
         * PPT: Jugadores por equipo, definido por el usuario.
         * CurrentTurn: Número del turno que se está jugando actualmente. 
         */
        private Player[] team1, team2;
        private int PPT, CurrentTurn;

        // Ejecuta el proceso del juego: Se inicializan los equipos, se juegan las partidas, y se decide el ganador.
        public Game()
        {
            InitTeams();
            GameLoop();
            Winner();
        }

        // Inicializa los equipos.
        private void InitTeams()
        {
            team1 = new Player[Constants.MAXPLAYERS];
            team2 = new Player[Constants.MAXPLAYERS];
            PPT = IntInput("\nIngrese la cantidad de jugadores por equipo (Mín 1 - Máx 5): ", 1, 5);
            for (int i = 0; i < 2; i++)
            {
                Console.WriteLine("\n\tEquipo " + (i + 1));
                for (int j = 0; j < PPT; j++)
                {
                    if (i == 0) team1[j] = InitPlayer(j + 1);
                    if (i == 1) team2[j] = InitPlayer(j + 1);
                }
            }
            PrintBothTeams();
        }

        // Inicializa al jugador especificado.
        private Player InitPlayer(int j)
        {
            Console.Write("Nombre Jugador " + j + ": ");
            string name = Console.ReadLine();
            Random r = new Random();
            return new Player(name, r.Next(75, 151), r.Next(1, 4), r.Next(1, 11), 0);
        }

        /*
         * Loop principal del juego. Se juegan las partidas hasta que se terminen los turnos, haya muerto todo
         * un equipo completo, o el usuario decida finalizar el programa.
         */
        private void GameLoop()
        {
            CurrentTurn = 0;
            bool firstTeamTurn = true;
            do
            {
                if (firstTeamTurn)
                {
                    if (CurrentTurn == Constants.TURNS || OneTeamDead()) break;
                    if (IntInput("\nSeleccione una opción.\n 1. Jugar.\n 2. Salir.\nIngrese el numero de la opción: ", 1, 2) == 2)
                        break;
                    SelectPlayer(this, team1, 1).PlayerAction(this, team2, 2);
                    firstTeamTurn = false;
                }
                else
                {
                    if (OneTeamDead()) break;
                    SelectPlayer(this, team2, 2).PlayerAction(this, team1, 1);
                    firstTeamTurn = true;
                    CurrentTurn++;
                    Console.Clear();
                    if (CurrentTurn != Constants.TURNS)Console.Write("TURNO: " + (CurrentTurn + 1) + "/" + Constants.TURNS);
                }
            } while (true);
        }

        // Comprueba si ha muerto todo un equipo completo.
        private bool OneTeamDead()
        {
            for (int i = 0; i < PPT; i++)
            {
                if (team1[i].Health > 0) break;
                else if (i == PPT - 1) return true;
            }
            for (int i = 0; i < PPT; i++) if (team2[i].Health > 0) return false;
            return true;
        }

        // Función que retorna el jugador elegido por el usuario.
        public static Player SelectPlayer(Game g, Player[] team, int t)
        {
            Thread.Sleep(200);
            Console.Clear();
            Console.Write("TURNO: " + (g.CurrentTurn + 1) + "/" + Constants.TURNS);
            Player p;
            Console.Write("\nSelecciona uno de los siguientes jugadores.");
            g.PrintOneTeam(team, t);
            do
            {
                p = team[IntInput("\n\nIngresa el numero del jugador: ", 1, g.PPT) - 1];
                if (p.Health == 0) Console.Write("Este jugador no tiene vida. Elige otro.");
            } while (p.Health == 0);
            return p;
        }

        // Determina al equipo ganador, basandose en el puntaje de los jugadores.
        private void Winner()
        {
            PrintBothTeams();
            int scoreTeam1 = 0, scoreTeam2 = 0;
            for (int i = 0; i < PPT; i++)
            {
                scoreTeam1 += team1[i].Score;
                scoreTeam2 += team2[i].Score;
            }
            if (scoreTeam1 > scoreTeam2) Console.WriteLine("\nHa ganado el equipo 1. Puntaje total: "+ scoreTeam1);
            else if (scoreTeam1 == scoreTeam2) Console.WriteLine("\nLos equipos han empatado con "+ scoreTeam1 + " puntos.");
            else Console.WriteLine("\nHa ganado el equipo 2. Puntaje total: "+ scoreTeam2);
            Console.WriteLine();
        }

        // Imprime la información de un equipo.
        private void PrintOneTeam(Player[] team, int t)
        {
            Console.Write("\n\n\tEquipo " + t);
            for (int i = 0; i < PPT; i++) {
                Console.Write("\n" + (i + 1) + ". " + team[i].Name + " - Vida: " + team[i].Health +
                    " - Nivel: " + team[i].Level + " - Fuerza: " + team[i].Strength + " - Puntaje: " +
                    team[i].Score);
                if (team[i].Health == 0) Console.Write(" --> *MUERTO*");
            }
        }

        // Imprime la información de ambos equipos.
        private void PrintBothTeams()
        {
            Thread.Sleep(200);
            Console.Clear();
            if (CurrentTurn != Constants.TURNS) Console.Write("TURNO: " + (CurrentTurn + 1) + "/" + Constants.TURNS);
            Console.Write("\n*******************************************************");
            PrintOneTeam(team1, 1);
            PrintOneTeam(team2, 2);
            Console.WriteLine("\n\n*******************************************************\n");
        }

        // Valida que el dato ingresado sea un número entero, y se encuentre dentro del rango especificado.
        public static int IntInput(string msg, int min, int max)
        {
            Console.Write(msg);
            int aux;
            while (true)
            {
                try
                {
                    aux = int.Parse(Console.ReadLine());
                    if (aux >= min && aux <= max) return aux;
                    else Console.Write("Ingresa un valor dentro del rango: ");
                }
                catch
                {
                    Console.Write("Debes ingresar un número entero: ");
                }
            }
        }
    }
}
