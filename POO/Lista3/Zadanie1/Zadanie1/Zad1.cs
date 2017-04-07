using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
1. Creator - Shape Factory przechowuje i tworzy na zamówienie obiekty typu Shape
2. Information Expert - Figury same liczą swoje pola - zobowiązania są przydzielane tym obiektom
które mają informacje konieczne do ich realizacji.
3.Low Coupling - Pozwala na dodawanie pracowników, bo każdy pracownik wie, jakie figury
może tworzyć i posiada kod tworzący te figury. Dzięki temu zwiększamy możliwość reużywania kodu
4. Polymorphizm - Skoro dla różnych figur sposób liczenia pola/obwodu jest rózny, to każda figura dziedziczy 
z klasy bazowej i nadpisuje metody, by nie robić case'ów
5.Protected Variations - Stabilny interfejs IFactoryWorker dzięki któremu możemy zmieniać poszczególne sposoby
obliczania bądź dodawać/usuwać figury, i nie ma to wpływu na resztę figur. 

    
*/

namespace Zadanie1
{
    class Zad1
    {
        public static void Main(string[] args)
        {
            ShapeFactory factory = new ShapeFactory();
            TriangleWorker tworker = new TriangleWorker();
            SquareWorker sworker = new SquareWorker();

            factory.AddWorker(sworker);
            factory.AddWorker(tworker);
            Shape t = factory.CreateShape("Triangle", 10);
            Shape s = factory.CreateShape("Square", 10);

            t.PrintInfo();
            Console.WriteLine("Pole: {0}, Obwód: {1}", t.ComputeArea(), t.ComputePerimeter());
            s.PrintInfo();
            Console.WriteLine("Pole: {0}, Obwód: {1}", s.ComputeArea(), s.ComputePerimeter());
            Console.ReadLine();

        }
    }


    public abstract class Shape
    {
        public abstract double ComputeArea();
        public abstract double ComputePerimeter();

        public abstract void PrintInfo();
    }
    public class Triangle : Shape
    {
        public double Side { get; set; }

        public override double ComputeArea()
        {
            return (Side * Side * Math.Sqrt(3)) / 4;
        }   

        public override double ComputePerimeter()
        {
            return 3 * Side;
        }

        public override void PrintInfo()
        {
            Console.WriteLine("Trójkąt o boku {0}", Side);
        }
    }
    public class Square : Shape
    {
        public double Side { get; set; }

        public override double ComputeArea()
        {
            return Side * Side;
        }

        public override double ComputePerimeter()
        {
            return 4 * Side;
        }

        public override void PrintInfo()
        {
            Console.WriteLine("Kwadrat o boku {0}", Side);
        }
    }
    public interface IFactoryWorker
    {
        bool Parameter(string parameter);

        Shape Create(double Side);
    }

    public class TriangleWorker : IFactoryWorker
    {
        public bool Parameter(string parameter)
        {
            return parameter.Equals("Triangle");
        }
        public Shape Create(double Side)
        {
            return new Triangle() { Side = Side };
        }

    }

    public class SquareWorker : IFactoryWorker
    {
        public bool Parameter(string parameter)
        {
            return parameter.Equals("Square");
        }
        public Shape Create(double Side)
        {
            return new Square() { Side = Side };
        }

    }
    public class ShapeFactory
    {
        List<IFactoryWorker> workers;

        public ShapeFactory()
        {
            workers = new List<IFactoryWorker>();
        }
        public void AddWorker(IFactoryWorker worker)
        {
            workers.Add(worker);
        }
        public Shape CreateShape(string type, double Side)
        {
            foreach (IFactoryWorker worker in workers)
            {
                if (worker.Parameter(type))
                {
                    Shape newShape = worker.Create(Side);
                    return newShape;
                }

            }
            return null;
        }
    }


}
