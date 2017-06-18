using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class HandelHandler : Handler
    {
        public override bool ProcessRequest(string email)
        {
            if (email.Substring(0, 10) == "Zamówienie")
            {
                Console.WriteLine("Zamówienie przekazane do działu handlowego");
                return true;
            }
            return false;
        }
    }
}
