using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using z1;
using NUnit.Framework;

namespace UnitTestProject
{
    [TestFixture]
    class UnitTestProject1
    {
        [Test]
        public void TestSingleton1()
        {
            Singleton s1, s2;

            s1 = Singleton.GetInstance();
            s2 = Singleton.GetInstance();

            Assert.IsNotNull(s1);
            Assert.IsNotNull(s2);
            Assert.AreSame(s1, s2);
        }

        [Test]
        public void TestSingleton2()
        {
            Thread t1, t2;
            ThreadSingleton s1 = null, s2 = null;

            t1 = new Thread(() =>
            {
                s1 = ThreadSingleton.GetInstance();
            }
                );
            t2 = new Thread(() =>
            {
                s2 = ThreadSingleton.GetInstance();
            }
                );

            t1.Start();
            t2.Start();
            t1.Join();
            t2.Join();


            Assert.IsNotNull(s1);
            Assert.IsNotNull(s2);
            Assert.AreNotSame(s1, s2);
        }

        [Test]
        public void TestSingleton3()
        {
            FiveSecondSingleton s1, s2, s3;

            s1 = FiveSecondSingleton.GetInstance();
            Thread.Sleep(TimeSpan.FromSeconds(4));
            s2 = FiveSecondSingleton.GetInstance();
            Thread.Sleep(TimeSpan.FromSeconds(2));
            s3 = FiveSecondSingleton.GetInstance();

            Assert.AreSame(s1, s2);
            Assert.AreNotSame(s1, s3);
            Assert.AreNotSame(s2, s3);
        }
    }
}
