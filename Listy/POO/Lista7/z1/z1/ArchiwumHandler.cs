using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class ArchiwumHandler : Handler
    {
        public override bool ProcessRequest(string email)
        {
            Console.WriteLine("Wiadomość zarchiwizowana");
            return true;
        }
    }
}
