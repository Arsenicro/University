using System;
using z2;
using NUnit.Framework;

namespace UnitTestProject1
{
    [TestFixture]
    public class UnitTest1
    {
        [Test]
        public void Test1()
        {
            ShapeFactory factory = new ShapeFactory();

            IShape square = factory.CreateShape("Square", 2);
            IShape triangle = factory.CreateShape("Triangle", 2, 3, 4);

            Assert.IsNotNull(square);
            Assert.IsNull(triangle);

        }

        [Test]
        public void Test2()
        {
            ShapeFactory factory = new ShapeFactory();

            IShape square = factory.CreateShape("Square", 2);
            factory.AddWorker(new TriangleWorker());
            IShape triangle = factory.CreateShape("Triangle", 2, 3, 4);

            Assert.IsNotNull(square);
            Assert.IsNotNull(triangle);
            Assert.AreNotEqual(triangle, square);

        }

    }
}
