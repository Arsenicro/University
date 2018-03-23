using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Z3
{
    class Program
    {
        static void Main(string[] args)
        {
            IShapeFactory factory = new ShapeFactory();
            IShapeFactory timeProxy = new FactoryTimeProxy(factory);
            IShapeFactory loggerProxy = new FactoryLoggerProxy(factory);


            try
            {
                IShape square = timeProxy.CreateShape("Square", 2);
                Console.WriteLine("protection proxy nie wyrzuca wyjątku, zwraca {0}", square.ToString());
            }
            catch (UnauthorizedAccessException e)
            {
                Console.WriteLine("protection proxy wyrzuca wyjątek: {0}", e.Message);
            }
            
            IShape square1 = loggerProxy.CreateShape("Square", 2);


            Console.ReadLine(); 


        }
    }
}
