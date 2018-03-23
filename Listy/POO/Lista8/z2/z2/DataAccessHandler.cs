using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z2
{
    public abstract class DataAccessHandler
    {
        protected abstract void Connect();
        protected abstract void GetData();
        protected abstract void ProcessData();
        protected abstract void CloseConnection();

        public void Execute()
        {
            Connect();
            GetData();
            ProcessData();
            CloseConnection();
        }
    }
}
