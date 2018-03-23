using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    class Context
    {
        public State state;
        public int type;
        public double price;
        public double change = 0;

        public Context(State beginState)
        {
            state = beginState;
            state.context = this;
        }

        public void Execute()
        {
            state.Handle();
        }
    }
}
