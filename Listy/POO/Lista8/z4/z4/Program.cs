using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class Program
    {
        static void Main(string[] args)
        {
            var Biletomat = new Context(new WaitState());
            while (Biletomat.state != null)
            {
                Biletomat.Execute();
            }
            Console.ReadKey();
        }
    }
}
