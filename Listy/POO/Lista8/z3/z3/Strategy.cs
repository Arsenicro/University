using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z3
{
    public abstract class Strategy
    {
        public abstract void Connect();
        public abstract void GetData();
        public abstract void ProcessData();
        public abstract void CloseConnection();
    }
}
