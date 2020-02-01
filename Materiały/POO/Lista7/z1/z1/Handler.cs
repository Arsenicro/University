using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z1
{
    abstract class Handler
    {
        public Handler next;

        public abstract bool ProcessRequest(string email);

        public void AttachNext( Handler handler )
        {
            if (next != null)
                next.AttachNext(handler);
            else
                next = handler;
        }

        public void ChainOfResponsybility(string email)
        {
            Handler current = this;
            while (current != null && !current.ProcessRequest(email)) { current = current.next; }

            Handler handler = new ArchiwumHandler();
            handler.ProcessRequest(email);


        }
    }
}
