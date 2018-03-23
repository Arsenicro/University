using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z2
{
    class z2
    {

        public static void Main(string[] args)
        {

        }
    }


    public interface IShape
    {
       
    }
    public class Triangle: IShape
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
            return new Triangle() { a = (int)parameters[0], b = (int)parameters[1], c=(int)parameters[2]  };
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
                if (worker.Parameter(type,parameters))
                {
                    IShape newShape = worker.Create(parameters);
                    return newShape;
                }

            }
            return null;
        }
    }


}
