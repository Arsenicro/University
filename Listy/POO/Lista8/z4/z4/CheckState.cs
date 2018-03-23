using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class CheckState : State
    {
        public override void Handle()
        {
            double price = Convert.ToDouble(Console.ReadLine());
            if (price < this.context.price)
            {
                Console.WriteLine("Error!");
                this.context.state = new EndState() { context = context };
                return;
            }

            this.context.change = price - this.context.price;

            if (this.context.change == 0)
            {
                this.context.state = new TransactionState() { context = context };
            }

            this.context.state = new GiveChangeState() { context = context };

        }
    }
}
