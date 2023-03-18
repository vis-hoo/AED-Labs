using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio7
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Auto auto1 = new Auto("Volkswagen", "Voyage VW", 2020, 75, 80);
            Auto auto2 = new Auto("Toyota", "RAV4", 2019, 65, 95);
            Auto auto3 = new Auto("Nissan", "Qashqai", 2021, 90, 70);

            auto1.ImprimirInfo();
            auto2.ImprimirInfo();
            auto3.ImprimirInfo();
        }
    }
}
