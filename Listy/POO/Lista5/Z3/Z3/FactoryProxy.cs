using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Z3
{
    public class FactoryTimeProxy : IShapeFactory
    {
        private int open = 8;
        private int close = 22;

        IShapeFactory sf;

        private void Time()
        {
            DateTime now = DateTime.Now.ToLocalTime();

            if (!(now.Hour > open && now.Hour < close))
            {
                throw new UnauthorizedAccessException("Używanie po godzinach pracy");
            }
        }

        public FactoryTimeProxy(IShapeFactory sf)
        {
            this.sf = sf;
        }

        public void AddWorker(IFactoryWorker worker)
        {
            Time();
            sf.AddWorker(worker);
        }

        public IShape CreateShape(string ShapeName, params object[] parameters)
        {
            Time();
            return sf.CreateShape(ShapeName, parameters);
        }
    }

    public class FactoryLoggerProxy : IShapeFactory
    {
        private IShapeFactory sf;

        public FactoryLoggerProxy(IShapeFactory sf)
        {
            this.sf = sf;
        }

        public void AddWorker(IFactoryWorker worker)
        {
            Console.WriteLine("Start: {0}, Parametry: {1}", DateTime.Now, worker.ToString());
            sf.AddWorker(worker);
            Console.WriteLine("Koniec: {0}", DateTime.Now);
        }

        public IShape CreateShape(string ShapeName, params object[] parameters)
        {
            Console.Write("Start: {0}, Nazwa: {1}, Parametry: ", DateTime.Now, ShapeName);
            foreach (var param in parameters)
            {
                Console.Write("{0} ", param.ToString());
            }
            Console.Write("\n");

            //System.Threading.Thread.Sleep(5000);

            IShape shape = sf.CreateShape(ShapeName, parameters);

            Console.WriteLine("Koniec: {0}, Zwraca: {1}", DateTime.Now, shape.ToString());
            return shape;
        }
    }

    /* 
    
        L4

    */

    public interface IShape
    {

    }
    public class Triangle : IShape
    {
        public int a { get; set; }
        public int b { get; set; }
        public int c { get; set; }
    }
    public class Square : IShape
    {
        public int Side { get; set; }
    }
    public interface IFactoryWorker
    {
        bool Parameter(string name, params object[] parameters);

        IShape Create(params object[] parameters);
    }

    public class TriangleWorker : IFactoryWorker
    {
        public bool Parameter(string name, params object[] parameters)
        {
            return name.Equals("Triangle") && parameters.Length == 3;
        }
        public IShape Create(params object[] parameters)
        {
            return new Triangle() { a = (int)parameters[0], b = (int)parameters[1], c = (int)parameters[2] };
        }

    }

    public class SquareWorker : IFactoryWorker
    {
        public bool Parameter(string name, params object[] parameters)
        {
            return name.Equals("Square") && parameters.Length == 1;
        }
        public IShape Create(params object[] parameters)
        {
            return new Square() { Side = (int)parameters[0] };
        }

    }

    public interface IShapeFactory
    {
        void AddWorker(IFactoryWorker worker);
        IShape CreateShape(string ShapeName, params object[] parameters);
    }

    public class ShapeFactory : IShapeFactory
    {
        public List<IFactoryWorker> workers;

        public ShapeFactory()
        {
            workers = new List<IFactoryWorker>();
            workers.Add(new SquareWorker());
        }
        public void AddWorker(IFactoryWorker worker)
        {
            workers.Add(worker);
        }
        public IShape CreateShape(string type, params object[] parameters)
        {
            foreach (IFactoryWorker worker in workers)
            {
                if (worker.Parameter(type, parameters))
                {
                    IShape newShape = worker.Create(parameters);
                    return newShape;
                }

            }
            return null;
        }
    }


}
