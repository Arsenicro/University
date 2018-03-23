using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class EndState : State
    {
        public override void Handle()
        {
            Console.WriteLine("Zakończenie transakcji!");
            this.context.state = null;
        }
    }
}
