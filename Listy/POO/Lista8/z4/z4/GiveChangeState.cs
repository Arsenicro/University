using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class GiveChangeState : State
    {
        public override void Handle()
        {
            Console.WriteLine("Wydawanie " + this.context.change + " zł reszty!");
            this.context.state = new TransactionState() { context = context };
        }
    }
}
