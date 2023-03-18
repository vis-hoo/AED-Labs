using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace labsemana1_ejercicio3
{
    internal class Program
    {
        static void Main(string[] args)
        {
            string unicodeCaracter = "\u2588";

            Console.WriteLine("\n\tPresione Enter para comenzar a cargar.");
            Console.ReadLine();
            for (int i = 0; i < 37; i++)
            {
                Thread.Sleep(300);
                if (i == 0) Console.Write("\t" + unicodeCaracter);
                Console.Write(unicodeCaracter);
            }
            Console.WriteLine("\n\n");
        }
    }
}
