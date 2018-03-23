using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class Program
    {
        static void Main(string[] args)
        {
            Invoker invoker = new Invoker();
            Console.WriteLine("Uruchamiam invoker");
            invoker.Run();
        }
    }
}
