using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    public class CreateFileCommand : ICommand
    {
        String path;
        IFileMenager _fm = new FileMenager();

        public CreateFileCommand(String path)
        {
            this.path = path;
        }

        public void Execute()
        {
            _fm.CreateFileCommand(path);
        }
    }
}
