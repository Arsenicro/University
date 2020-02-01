using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class InfoState : State
    {
        public override void Handle()
        {
            if (this.context.type == '1')
            {
                Console.WriteLine("Wybrano bilet ulgowy.");
                Console.WriteLine("Cena: 1.50 zł");
                this.context.price = 1.50;
                this.context.state = new CheckState() { context = context };
            }
            if (this.context.type == '2')
            {
                Console.WriteLine("Wybrano bilet normalny.");
                Console.WriteLine("Cena: 3 zł");
                this.context.price = 3.0;
                this.context.state = new CheckState() { context = context };
            }
        }
    }
}
