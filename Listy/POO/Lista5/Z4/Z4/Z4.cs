using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Z4
{
    class Z4
    {
        static int IntComparer(int x, int y)
        {
            return x.CompareTo(y);
        }

        static void Main(string[] args)
        {
            ArrayList a = new ArrayList() { 1, 5, 3, 3, 2, 4, 3 };

            /* the ArrayList's Sort method accepts ONLY an IComparer */
            a.Sort(new ComparisonToComparerAdapter(IntComparer));
            foreach(int i in a)
            {
                Console.Write(i + " ");
            }
            Console.WriteLine("");

            Console.ReadLine();
        }
        public class ComparisonToComparerAdapter : IComparer
        {
            Func<int, int, int> comparison;

            public ComparisonToComparerAdapter(Func<int, int, int> comparison)
            {
                this.comparison = comparison;
            }

            public int Compare(object x, object y)
            {
                return comparison((int)x, (int)y);
            }
        }
    }
}
