using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Zadanie3
{
    class Zad3
    {
        static void Main(string[] args)
        {
            Item[] items = new Item[]
            {
                new Item("Mleko", 3.00),
                new Item("Woda", 1.50),
                new Item("Chleb", 2.00),
                new Item("Sok", 2.50)
            };

            OldCashRegister old = new OldCashRegister();
            Console.WriteLine("Sumeryczna cena: {0}", old.CalculatePrice(items));
            old.PrintBill(items);

            Console.WriteLine();

            CashRegister newc = new CashRegister();
            Console.WriteLine("Podatek {1} - sumaryczna cena: {0}", newc.CalculatePrice(items), newc.Tax);
            newc.Tax = new Decimal(0.27);
            Console.WriteLine("Podatek {1} - sumaryczna cena: {0}", newc.CalculatePrice(items), newc.Tax);

            Console.WriteLine("Bez sortowania");
            newc.PrintBill(items);
            Console.WriteLine("Alfabetycznie");
            newc.PrintBill(items, new AlphabeticalSort());
            Console.WriteLine("Cenowo");
            newc.PrintBill(items, new PriceSort());

            Console.ReadLine();
        }
    }

    /* 
        Ta sama klasa Item dla obu wersji
    */

    public class Item
    {
        Decimal _price;
        string _name;

        public Item(string name, Decimal price)
        {
            _price = price;
            _name = name;
        }

        public Item(string name, double price)
        {
            _price = new Decimal(price);
            _name = name;
        }

        public Decimal Price
        {
            get { return _price; }
            set { _price = value; }
        }
        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }
    }

    public class OldTaxCalculator
    {
        public static Decimal tax = new Decimal(0.22);
        public Decimal CalculateTax(Decimal Price) { return Price * tax; }
    }

   
    public class OldCashRegister
    {
        public OldTaxCalculator taxCalc = new OldTaxCalculator();
        public Decimal CalculatePrice(Item[] Items)
        {
            Decimal _price = 0;
            foreach (Item item in Items)
            {
                _price += item.Price + taxCalc.CalculateTax(item.Price);
            }
            return _price;
        }

        public void PrintBill(Item[] Items)
        {
            foreach (var item in Items)
                Console.WriteLine("towar {0} : cena {1} + podatek {2}",
                    item.Name, item.Price, taxCalc.CalculateTax(item.Price));
        }
    }

    /*
        Wersja poprawiona - interfejs do sortowania przedmiotów daje możliwość dodania nowych sposobów sortowania
                            bez wpływania na kod pozostałych sortowań
    */

    public interface IItemSort
    {
        Item[] SortItems(Item[] items);
    }

    public class AlphabeticalSort : IItemSort
    {
        public Item[] SortItems(Item[] items)
        {
            int length = items.Length;
            for (int i = 1; i < length; i++)
            {
                for (int j = 1; j < length; j++)
                {
                    if (String.Compare(items[j - 1].Name, items[j].Name) > 0)
                    {
                        Item it = items[j];
                        items[j] = items[j - 1];
                        items[j - 1] = it;

                    }
                }
            }

            return items;
        }

    }

    public class PriceSort : IItemSort
    {
        public Item[] SortItems(Item[] items)
        {
            int length = items.Length;
            for (int i = 1; i < length; i++)
            {
                for (int j = 1; j < length; j++)
                {
                    if (items[j - 1].Price > items[j].Price)
                    {
                        Item it = items[j];
                        items[j] = items[j - 1];
                        items[j - 1] = it;
                    }
                }
            }

            return items;

        }

    }

    /*
        TaxCalculatror umożliwiający klientowi zmianę podatku bez wpływania na kod
    */

    public class TaxCalculator
    {
        private Decimal tax = new Decimal(0.22);

        public TaxCalculator() { }

        public TaxCalculator(double tax)
        {
            this.tax = new Decimal(tax);
        }

        public Decimal Tax
        {
            get { return tax; }
            set { tax = value; }

        }

        public Decimal CalculateTax(Decimal Price) { return Price * tax; }
    }

    /*
        CashRegister - liczenie ceny takie samo, dodaję możliwość ustawienia podatku za pomocą getów i setów
                        Drukowanie paragonu umożliwia dodanie sposobu sortowania
    */

    public class CashRegister
    {
        public TaxCalculator taxCalculator = new TaxCalculator();

        public Decimal Tax
        {
            get { return taxCalculator.Tax; }
            set { taxCalculator.Tax = value; }
        }

        public Decimal CalculatePrice(Item[] Items)
        {
            Decimal _price = 0;
            foreach (Item item in Items)
                _price += item.Price + taxCalculator.CalculateTax(item.Price);

            return _price;
        }

        public void PrintBill(Item[] Items, IItemSort Sort)
        {

            Item[] Sorted = Sort.SortItems(Items);

            foreach (var item in Sorted)
                Console.WriteLine("towar {0} : cena {1} + podatek {2}",
                    item.Name, item.Price, taxCalculator.CalculateTax(item.Price));

        }

        public void PrintBill(Item[] Items)
        {
            foreach (var item in Items)
                Console.WriteLine("towar {0} : cena {1} + podatek {2}",
                    item.Name, item.Price, taxCalculator.CalculateTax(item.Price));

        }

    }

}
