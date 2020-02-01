using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadanie2
{
    class Zad2
    {

        static void Main(string[] args)
        {
            Document dc = new Document("ANIA LUBI MASŁO");
            DocumentFormatter df = new DocumentFormatter();
            ReportPrinter2 rp = new ReportPrinter2();

            ReportComposer rc = new ReportComposer(dc, df, rp);
            rc.Cos();

            Console.ReadLine();
        }
    }

    public class ReportPrinter
    {
        private string data;

        public ReportPrinter(string _data)
        {
            this.data = _data;
        }
        public string GetData()
        {
            return data;
        }
        public void FormatDocument()
        {
            data = "Sformatowany";
        }

        public void PrintReport()
        {
            Console.WriteLine("Drukuję dokument {0}", data);
        }
    }
    //Zad 7
    public class ReportComposer
    {
        private IDocument document;
        private IDataFormater formater;
        private IReportPrinter printer;

        public ReportComposer(IDocument dc, IDataFormater df, IReportPrinter rp)
        {
            document = dc;
            formater = df;
            printer = rp;
        }

        public void Cos()
        {
            formater.FormatDocument(document);
            printer.PrintReport(document);
        }

    }

    //Zad 7
    public interface IDocument
    {
        string GetData();
        void SetData(string d);
    }

    public class Document: IDocument
    {
        private string data;

        public Document(string _data)
        {
            this.data = _data;
        }

        public string GetData()
        {
            return data;
        }

        public void SetData(string d)
        {
            data = d;
        }
    }

    //Zad 7
    public interface IDataFormater
    {
        void FormatDocument(IDocument document);
    }

    public class DocumentFormatter: IDataFormater
    {
        public void FormatDocument(IDocument document)
        {
            string d = document.GetData();
            d += " Sformatowany przez DocumentFormatter";
            document.SetData(d);
        }
    }

    //Zad 7
    public interface IReportPrinter
    {
        void PrintReport(IDocument report);
    }

    public class ReportPrinter2: IReportPrinter
    {
        public void PrintReport(IDocument report)
        {
            Console.WriteLine("ReportPrinter2 drukuje dokument {0}", report.GetData());
        }
    }

}
