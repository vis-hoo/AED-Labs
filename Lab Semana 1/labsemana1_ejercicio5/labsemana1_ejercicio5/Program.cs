using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio5
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Random rnd = new Random();
            int piezaActual;
            int piezaAnterior = 0;
            bool seRepite;

            Console.WriteLine("Generando 20 piezas al azar.");
            for (int i = 0; i < 20; i++)
            {
                do
                {
                    piezaActual = rnd.Next(1, 8);
                    if (piezaActual == piezaAnterior) seRepite = true;
                    else seRepite = false;
                } while (seRepite);
                piezaAnterior = piezaActual;
                Console.WriteLine(piezaActual);
            }
        }
    }
}
