using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z3
{
    public class DataAccessHandler
    {
        Strategy strategy;

        public DataAccessHandler(Strategy strategy)
        {
            this.strategy = strategy;
        }
            
        public void Execute()
        {
            strategy.Connect();
            strategy.GetData();
            strategy.ProcessData();
            strategy.CloseConnection();
        }
    }
}
