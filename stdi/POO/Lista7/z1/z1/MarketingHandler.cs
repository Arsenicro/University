using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class MarketingHandler : Handler
    {
        public override bool ProcessRequest(string email)
        {
            Console.WriteLine("Przekazano do marketingu!");
            return true;
        }
    }
}
