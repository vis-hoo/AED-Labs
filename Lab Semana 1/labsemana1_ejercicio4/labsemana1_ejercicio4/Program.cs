using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio4
{
    internal class Program
    {
        static void Main(string[] args)
        {
            int[,] tablero = new int[3, 3];

            //0 = vacío. 1 = jugador 1. 2 = j2.
            tablero[0, 0] = 0;
            tablero[0, 1] = 0;
            tablero[0, 2] = 2;

            tablero[1, 0] = 0;
            tablero[1, 1] = 1;
            tablero[1, 2] = 2;

            tablero[2, 0] = 1;
            tablero[2, 1] = 0;
            tablero[2, 2] = 1;

            for (int i = 0; i < 3; i++)
                for (int j = 0; j < 3; j++)
                {
                    if (j == 0) Console.Write("\n\t[");
                    if (j == 2) ImprimirTablero(tablero, i, j, "]");
                    else ImprimirTablero(tablero, i, j, "][");
                }

            Console.WriteLine("\n");
        }

        static void ImprimirTablero(int[,] tablero, int i, int j, string texto)
        {
            if (tablero[i, j] == 0) Console.Write("-" + texto);
            else if (tablero[i, j] == 1) Console.Write("X" + texto);
            else if (tablero[i, j] == 2) Console.Write("O" + texto);
        }
    }
}
