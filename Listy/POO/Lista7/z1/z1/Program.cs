using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    class Program
    {
        static void Main(string[] args)
        {
            //Handler handler = new PrezesHandler(){
            //    next = new PrawnyHandler(){
            //    next = new HandelHandler(){ next = new MarketingHandler(){}}}
            //};
            Handler handler = new PrezesHandler();
            handler.AttachNext(new PrawnyHandler());
            handler.AttachNext(new HandelHandler());

            handler.ChainOfResponsybility("Skarga na Adama");
            handler.ChainOfResponsybility("Pochwała dla Wiktora");
            handler.ChainOfResponsybility("Zamówienie na system informatyczny");
            handler.ChainOfResponsybility("Cośtam Cośtam Cośtam");
            Console.ReadLine();
        }
    }
}
