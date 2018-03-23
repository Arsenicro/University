using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Z2
{
    class Z2
    {
        static void Main(string[] args)
        {
            FileStream fileToWrite = File.Create("zad2");
            CaesarStream caeToWrite = new CaesarStream(fileToWrite, 10);

            string input = "Zapisuje plik z przesunieciem";

            Console.WriteLine("Wypisano do pliku: {0}", input);
            byte[] toBeWritten = Encoding.ASCII.GetBytes(input);
            caeToWrite.Write(toBeWritten, 0, toBeWritten.Length);
            caeToWrite.Close();

            FileStream fileToRead = File.Open("zad2", FileMode.Open);
            CaesarStream caeToRead = new CaesarStream(fileToRead, -10);
            const int bufferLength = 128;
            byte[] toBeRead = new byte[bufferLength];

            int bytesRead = caeToRead.Read(toBeRead, 0, bufferLength);
            Console.WriteLine("Wczytano {0}", Encoding.ASCII.GetString(toBeRead));
            caeToRead.Close();

            Console.ReadLine();
        }
    }
}
