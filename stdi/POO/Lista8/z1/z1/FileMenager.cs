using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    public class FileMenager : IFileMenager
    {
        public void CopyFileCommand(string from, string to)
        {
            Console.WriteLine("Kopiowanie pliku  " + from + " do " + to);
        }

        public void CreateFileCommand(string path)
        {
            Console.WriteLine("Tworzenie i wypełnianie pliku " + path);
        }

        public void DownloadFTPCommand(string address)
        {
            Console.WriteLine("Pobieranie pliku FTP: " + address);
        }

        public void DownloadHTTPCommand(string address)
        {
            Console.WriteLine("Pobieranie pliku HTTP: " + address);
        }
    }
}
