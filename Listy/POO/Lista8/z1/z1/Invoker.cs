using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace z1
{

    public class Invoker
    {
        public int queueSize = 5;
        private Queue<ICommand> queue = new Queue<ICommand> ();
        private const int minGeneratorSleepTime = 500;
        private const int maxGeneratorSleepTime = 1000;

        private const int minDispatcherSleepTime = 2000;
        private const int maxDispatcherSleepTime = 3500;

        public void Run()
        {
            Thread generator = new Thread(new ThreadStart(Generate));
            Thread dis1 = new Thread(new ThreadStart(Dispatch));
            Thread dis2 = new Thread(new ThreadStart(Dispatch));

           int result = 0;

            try
            {
                generator.Start();
                dis1.Start();
                dis2.Start();

                generator.Join();
                dis1.Join();
                dis2.Join();

            }
            catch (ThreadStateException e)
            {
                Console.WriteLine(e);  
                result = 1;           
            }
            catch (ThreadInterruptedException e)
            {
                Console.WriteLine(e);  
                result = 1;            
            }
            Environment.ExitCode = result;

        }

        private void Generate()
        {
            ICommand command;
            while (true)
            {
                Random rand = new Random(Guid.NewGuid().GetHashCode());
                switch (rand.Next() % 4)
                {
                    case 0:
                        command = new DownloadFTPCommand("FTP Address " + rand.Next());
                        break;
                    case 1:
                        command = new DownloadHTTPCommand("HTTP Address " + rand.Next());
                        break;
                    case 2:
                        command = new CreateFileCommand("PATH NUMBER " + rand.Next());
                        break;
                    default:
                        command = new CopyFileCommand(rand.Next().ToString(), rand.Next().ToString());
                        break;

                }
                AddCommand(command);
                Thread.Sleep(rand.Next(minGeneratorSleepTime,maxGeneratorSleepTime));
            }
        }

        public void Dispatch()
        {
            while (true)
            {
                Random rand = new Random(Guid.NewGuid().GetHashCode());
                ICommand command = GetCommand();
                command.Execute();
                Thread.Sleep(rand.Next(minDispatcherSleepTime, maxDispatcherSleepTime));
            }
   
        }

        private void AddCommand(ICommand command)
        {
            lock (this)
            {
                while (queue.Count() > queueSize)
                {
                    Monitor.Wait(this,500);
                }

                Console.WriteLine("Generuję!");
                queue.Enqueue(command);
            }

        }
        private ICommand GetCommand()
        {
            lock (this)
            {
                while (queue.Count == 0)
                {
                    Monitor.Wait(this,500);
                }
                return queue.Dequeue();
            }
        }

    }
}
