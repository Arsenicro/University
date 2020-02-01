using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class WaitState : State
    {
        public override void Handle()
        {
            Console.WriteLine("Wybierz rodzaj biletu:");
            Console.WriteLine("1. Ulogwy");
            Console.WriteLine("2. Normalny");

            while (true)
            {
                char type = Console.ReadKey().KeyChar;
                if (type == '1' || type == '2')
                {
                    this.context.type = type;
                    this.context.state = new InfoState() { context = context };
                    Console.WriteLine();
                    return;
                }
                

            }

        }
    }
}
