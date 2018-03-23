using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Z2
{
    class CaesarStream : Stream
    {
        private Stream stream;
        private int shift;

        //Modulo nie działa dla liczb ujemnych, funkcja pomocnicza
        private int Mod(int dividend, int divisor)
        {
            int remainder = dividend % divisor;
            return remainder < 0 ? remainder + divisor : remainder;
        }

        
        public CaesarStream(Stream stream, int shift)
        {
            this.stream = stream;
            this.shift = shift;
        }


        public override void Close()
        {
            stream.Close();
            base.Close();
        }


        public override void Write(byte[] buffer, int offset, int count)
        {
            string temp = Encoding.ASCII.GetString(buffer);
            string output = "";
            for (int j = 0; j < count; j++)
            {
                if (char.IsLetter(temp[j]))
                {
                    char d = char.IsUpper(temp[j]) ? 'A' : 'a';
                    output += (char)(Mod(((temp[j] + shift) - d), 26) + d);
                }
                else
                {
                    output += temp[j];
                }
            }
            stream.Write(Encoding.ASCII.GetBytes(output), 0, count);
        }

        public override int Read(byte[] buffer, int offset, int count)
        {
            byte[] tmpbuf = new byte[count];
            int bytesRead = stream.Read(tmpbuf, 0, count);
            string temp = Encoding.ASCII.GetString(tmpbuf);
            string output = "";
            for (int j = 0; j < bytesRead; j++)
            {
                if (char.IsLetter(temp[j]))
                {
                    char d = char.IsUpper(temp[j]) ? 'A' : 'a';
                    output += (char)(Mod(((temp[j] + shift) - d), 26) + d);
                }
                else
                {
                    output += temp[j];
                }
            }
            tmpbuf = Encoding.ASCII.GetBytes(output);

            for (int j = 0; j < bytesRead; j++)
            {
                buffer[offset + j] = tmpbuf[j];
            }

            return bytesRead;

        }


        //NOT IMPLEMENTED
        public override bool CanRead
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public override bool CanSeek
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public override bool CanWrite
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public override long Length
        {
            get
            {
                throw new NotImplementedException();
            }
        }

        public override long Position
        {
            get
            {
                throw new NotImplementedException();
            }

            set
            {
                throw new NotImplementedException();
            }
        }

        public override void Flush()
        {
            throw new NotImplementedException();
        }

        public override long Seek(long offset, SeekOrigin origin)
        {
            throw new NotImplementedException();
        }

        public override void SetLength(long value)
        {
            throw new NotImplementedException();
        }


    }
}
