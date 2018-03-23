using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z4
{
    abstract class State
    {
        public Context context;
        public abstract void Handle();
    }
}
