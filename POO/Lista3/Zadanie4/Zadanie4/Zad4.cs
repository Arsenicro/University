using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadanie4
{
    class Zad4
    {
        static void Main(string[] args)
        {
            int w = 4, h = 5;
            Rectangle rec = new Rectangle() { Width = w, Height = h };
            AreaCalculator ac = new AreaCalculator();
            Console.WriteLine("Prostokąt o wymiarach {0}x{1} ma pole {2}",
                w, h, ac.CalculateArea(rec));

            Console.ReadLine();
        }

        public abstract class Polygon
        {
            public abstract int Area();
        }

        public class Rectangle : Polygon
        {
            public int Width { get; set; }
            public int Height { get; set; }

            public override int Area()
            {
                return Width * Height;
            }


        }
        public class Square : Polygon
        {
            public int Side { get; set; }

            public override int Area()
            {
                return Side * Side;
            }

        }

        public class AreaCalculator
        {
            public int CalculateArea(Polygon polygon)
            {
                return polygon.Area();
            }
        }


    }
}
