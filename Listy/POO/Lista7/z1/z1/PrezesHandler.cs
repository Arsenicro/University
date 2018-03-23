using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class PrezesHandler : Handler
    {
        public override bool ProcessRequest(string email)
        {
            if (email.Substring(0, 8) == "Pochwała")
            {
                Console.WriteLine("Pochwalna wiadomość przekazana prezesowi.");
                return true;
            }
            return false;
        }
    }
}
