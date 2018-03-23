using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;

namespace z2
{
    class XMLDataAccessHandler : DataAccessHandler
    {
        private XmlTextReader file;

        protected override void CloseConnection()
        {
            file.Close();
        }

        protected override void Connect()
        {
            string filename = "../../XMLFile1.xml";
            file = new XmlTextReader(filename);
        }
    
        protected override void GetData()
        {
        }

        protected override void ProcessData()
        {
            int maxLen = 0;
            while (file.Read())
            {
                switch (file.NodeType)
                {
                    case XmlNodeType.Element:
                        maxLen = maxLen < file.Name.Length ? file.Name.Length : maxLen;
                        break;
                }
            }
            Console.WriteLine($"Najdłuższy węzeł miał długość " + maxLen + " znaków.");
        }
    }
}
