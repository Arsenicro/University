using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Net.Mail;
using System.Text;
using System.Threading.Tasks;

namespace Z1
{
    class SmtpFacade
    {

        private string passwd;

        public SmtpFacade(string pass) { passwd = pass; }

        public void Send(string From, string To, string Subject, string Body, Stream Attachment, string AttachmentMimeType)
        {

            SmtpClient smtpClient = new SmtpClient()
            {
                Host = "smtp.gmail.com",
                Port = 587,
                UseDefaultCredentials = false,
                Credentials = new NetworkCredential(From, passwd),
                EnableSsl = true,
                DeliveryMethod = SmtpDeliveryMethod.Network
            };
            MailMessage message = new MailMessage(From, To, Subject, Body);

            try
            {
                smtpClient.Send(message);
            }
            catch (Exception ex)
            {
                Console.WriteLine("Wyjątek przy wysyłaniu wiadomości: " + ex.ToString());
                Console.ReadLine();
            }
        }
    }
}
