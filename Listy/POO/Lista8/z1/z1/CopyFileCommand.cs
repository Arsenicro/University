using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    public class CopyFileCommand : ICommand
    {
        string from, to;
        IFileMenager _fm = new FileMenager();

        public CopyFileCommand(string from, string to)
        {
            this.from = from;
            this.to = to;
        }

        public void Execute()
        {
            _fm.CopyFileCommand(from, to);
        }
    }
}
