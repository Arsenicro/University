using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    public interface IFileMenager
    {
        void DownloadFTPCommand(string address);
        void DownloadHTTPCommand(string address);
        void CreateFileCommand(string path);
        void CopyFileCommand(string from, string to);
    }
}
