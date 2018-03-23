using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class PrintState : State
    {
        public override void Handle()
        {
            Console.WriteLine("Drukowanie biletu...");
            string type = (this.context.type == 1) ? "Ulgowy" : "Normalny";
            Console.WriteLine("Bilet " + type);

            this.context.state = new EndState() { context = context };
        }
    }
}
