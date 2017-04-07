using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;

namespace z1
{
    class z1
    {
        static void Main(string[] args)
        {

        }
    }

    public class Singleton
    {
        private static Singleton instance;

        private Singleton()
        {
        }

        public static Singleton GetInstance()
        {
            if (instance == null)
            {
                instance = new Singleton();
            }
            
            return instance;
        }
    }

    public class ThreadSingleton
    {
        private static ThreadLocal<ThreadSingleton> localInstance = new ThreadLocal<ThreadSingleton>();
        private ThreadSingleton()
        {
        }

        public static ThreadSingleton GetInstance()
        {
            if (localInstance.Value == null)
            {
                localInstance.Value = new ThreadSingleton();
            }
            return localInstance.Value;
        }
    }

    public class FiveSecondSingleton
    {
        private static FiveSecondSingleton instance;
        private static DateTime timer;
        private FiveSecondSingleton()
        {
        }

        public static FiveSecondSingleton GetInstance()
        {
            if (instance == null)
            {
                instance = new FiveSecondSingleton();
                timer = DateTime.Now;
            }
            else
            {
                TimeSpan interval = DateTime.Now - timer;
                if (interval.Seconds >= 5)
                {
                    instance = new FiveSecondSingleton();
                    timer = DateTime.Now;
                    
                }
            }
            return instance;
        }
    }
}