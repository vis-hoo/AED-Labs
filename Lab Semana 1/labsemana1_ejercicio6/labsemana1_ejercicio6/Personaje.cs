using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio6
{

    enum Clasificacion { Mago, Guerrero, Medico, Monstruo }
    enum TipoPoder { MateriaOscura, EspadaVengadora, OndaVital, FlechaAcida }

    internal class Personaje
    {
        Clasificacion Tipo;
        string Nombre;
        int VidaMaxima;
        TipoPoder Poder;
        int VelocidadMovimiento;

        public Personaje(Clasificacion tipo, string nombre, int vidaMaxima, TipoPoder poder, int velocidadMovimiento)
        {
            Tipo = tipo;
            Nombre = nombre;
            VidaMaxima = vidaMaxima;
            Poder = poder;
            VelocidadMovimiento = velocidadMovimiento;
        }

        public void MostrarDatos()
        {
            Console.Clear();
            Console.WriteLine("\n\n\t" + Nombre + ".\n\t" + Tipo + ".\n\tPoder: " + Poder + ".\n\tVida: " + 
                VidaMaxima + ".\n\tVelocidad: " + VelocidadMovimiento + ".");
        }

        public void Descansar()
        {
            Console.Clear();
            VidaMaxima += 5;
            Console.WriteLine("\n\n\tHas descansado. La vida de tu personaje aumentó en 5." +
                "\n\tVida: " + VidaMaxima + ".");
        }

        public void Atacar()
        {
            Console.Clear();
            Console.WriteLine("\n\n\t Has atacado.");
        }

        public void CargarPoder()
        {
            Console.Clear();
            Console.WriteLine("\n\n\t Has cargado tu poder.");
        }
    }
}
