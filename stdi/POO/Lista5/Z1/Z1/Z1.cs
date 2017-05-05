using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

/*
Jeśli po wysłaniu wiadomości na skrzynce pocztowej nadawcy pokazuje się komunikat o odrzuceniu wiadomości z kodem 5.0.0
należy wyłączyć antywirusa.
*/

namespace Z1
{
    class Z1
    {
        static void Main(string[] args)
        {
            SmtpFacade facade = new SmtpFacade("password");
            //FileStream Attachment = new FileStream("plik.txt",FileMode.OpenOrCreate, FileAccess.Read);
            facade.Send("juubi1337@gmail.com", "kamil.k.mat@gmail.com", "Testuje", "Czy działa?", null, "text/plain");
        }
    }
}
