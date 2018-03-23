using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z2
{
    class Program
    {
        static void Main(string[] args)
        {
            DataAccessHandler dbHandler = new DbDataAccessHandler();
            dbHandler.Execute();
            

            DataAccessHandler xmlHandler = new XMLDataAccessHandler();
            xmlHandler.Execute();

            Console.ReadLine();
        }
    }
}
