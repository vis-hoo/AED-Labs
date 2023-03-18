using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio7
{
    internal class Auto
    {
        string Fabricante;
        string Modelo;
        int Año;
        int Velocidad;
        int Maniobrabilidad;

        public Auto(string fabricante, string modelo, int año, int velocidad, int maniobrabilidad)
        {
            Fabricante = fabricante;
            Modelo = modelo;
            Año = año;
            Velocidad = velocidad;
            Maniobrabilidad = maniobrabilidad;
        }

        public void ImprimirInfo()
        {
            Console.Write("\n\tFabricante: " + Fabricante +
                ".\n\tModelo: " + Modelo +
                ".\n\tAño: " + Año +
                ".\n\tVelocidad: " + Velocidad +
                "%.\n\tManiobrabilidad: " + Maniobrabilidad + "%.\n\n");
        }
    }
}
