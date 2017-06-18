using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class TransactionState : State
    {
        public override void Handle()
        {
            Console.WriteLine("Przygotowanie biletu...");
            this.context.state = new PrintState() { context = context };

        }
    }
}
