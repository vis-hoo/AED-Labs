using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace labsemana1_ejercicio6
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.Write("\n\t\tLord of Morfu");
            Console.Write("\n\n\tBienvenido a la creación de personaje." +
                "\n\tRellena los campos para crear tu avatar:");
            Personaje personaje = CreacionPersonaje();
            Console.Clear();

            int accion = 0;
            do {
                switch (Menu())
                {
                    case 1:
                        personaje.MostrarDatos();
                        accion = 1;
                        break;
                    case 2:
                        personaje.Descansar();
                        accion = 2;
                        break;
                    case 3:
                        personaje.Atacar();
                        accion = 3;
                        break;
                    case 4:
                        personaje.CargarPoder();
                        accion = 4;
                        break;
                    case 5:
                        accion = 5;
                        break;
                }
            } while (accion != 5);

            Console.WriteLine();
            Console.WriteLine();
            Environment.Exit(0);
        }

        static Personaje CreacionPersonaje()
        {
            Clasificacion Tipo;
            string Nombre;
            int VidaMaxima;
            TipoPoder Poder;
            int VelocidadMovimiento;

            //Nombre
            Console.Write("\n\n * Nombre: ");
            Nombre = Console.ReadLine();

            #region Clasificacion
            Console.Write(" * Tipo:" +
                "\n     1. Mago." +
                "\n     2. Guerrero." +
                "\n     3. Médico." +
                "\n     4. Monstruo." +
                "\n   Ingresa el número correspondiente a la clasificación: ");
            int tipo;
            do
            {
                tipo = int.Parse(Console.ReadLine());
                if (tipo < 1 || tipo > 4) Console.Write("   Ingresa el número correspondiente a la clasificación: ");
            } while (tipo < 1 || tipo > 4);
            Tipo = (Clasificacion)tipo;
            #endregion

            #region Poder
            Console.Write(" * Poder:" +
                "\n     1. Materia Oscura." +
                "\n     2. Espada Vengadora." +
                "\n     3. Onda Vital." +
                "\n     4. Flecha Ácida." +
                "\n   Ingresa el número correspondiente a la clasificación: ");
            int poder;
            do
            {
                poder = int.Parse(Console.ReadLine());
                if (poder < 1 || poder > 4) Console.Write("   Ingresa el número correspondiente a la clasificación: ");
            } while (poder < 1 || poder > 4);
            Poder = (TipoPoder)poder;
            #endregion

            //Vida
            do
            {
                Console.Write("* Vida (75 - 125): ");
                VidaMaxima = int.Parse(Console.ReadLine());
            } while (VidaMaxima < 75 || VidaMaxima > 125);

            //Velocidad
            do
            {
                Console.Write("* Velocidad (5 - 15): ");
                VelocidadMovimiento = int.Parse(Console.ReadLine());
            } while (VelocidadMovimiento < 5 || VelocidadMovimiento > 15);

            Personaje personaje = new Personaje(Tipo, Nombre, VidaMaxima, Poder, VelocidadMovimiento);
            return personaje;
        }

        static int Menu()
        {
            Console.Write("\n\n\t¿Qué acción deseas realizar a continuación?" +
                "\n\n 1. Mostrar datos del personaje." +
                "\n 2. Descansar (recuperar vida)." +
                "\n 3. Atacar." +
                "\n 4. Cargar tu poder." +
                "\n 5. Salir." +
                "\n   Ingresa el número de la acción: ");
            int accion;
            do
            {
                accion = int.Parse(Console.ReadLine());
                if (accion < 1 || accion > 5) Console.Write("   Ingresa el número de la acción: ");
            } while (accion < 1 || accion > 5);

            return accion;
        }
    }
}
