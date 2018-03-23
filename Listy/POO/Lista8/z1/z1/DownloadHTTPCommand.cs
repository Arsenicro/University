using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    public class DownloadHTTPCommand : ICommand
    {
        string address;
        private IFileMenager _fm = new FileMenager();

        public DownloadHTTPCommand(String address)
        {
            this.address = address;
        }

        public void Execute()
        {
            _fm.DownloadHTTPCommand(address);
        }
    }
}

