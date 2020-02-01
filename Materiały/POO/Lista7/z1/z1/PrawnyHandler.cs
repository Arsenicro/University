using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class PrawnyHandler : Handler
    {
        public override bool ProcessRequest(string email)
        {
            if (email.Substring(0, 6) == "Skarga")
            {
                Console.WriteLine("Skarga przekazana do działu prawnego");
                return true;
            }
            return false;
        }
    }
}
