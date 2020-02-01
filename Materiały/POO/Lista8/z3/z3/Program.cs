using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z3
{
    class Program
    {
        static void Main(string[] args)
        {
            Strategy dbStrategy = new DbDataAccessHandler();
            Strategy xmlStrategy = new XMLDataAccessHandler();

            DataAccessHandler dbHandler = new DataAccessHandler(dbStrategy);
            dbHandler.Execute();


            DataAccessHandler xmlHandler = new DataAccessHandler(xmlStrategy);
            xmlHandler.Execute();

            Console.ReadLine();
        }
    }
}
