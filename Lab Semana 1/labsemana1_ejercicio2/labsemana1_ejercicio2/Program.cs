using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Mi número es el 7.\nIngresa tu número: ");
            double numero = int.Parse(Console.ReadLine());

            Console.WriteLine("\nSuma: 7 + " + numero + " = " + (7 + numero) + ".");
            Console.WriteLine("Resta: 7 - " + numero + " = " + (7 - numero) + ".");
            Console.WriteLine("Multiplicación: 7 * " + numero + " = " + (7 * numero) + ".");
            Console.WriteLine("División: 7 / " + numero + " = " + (7 / numero) + ".\n");
        }
    }
}
