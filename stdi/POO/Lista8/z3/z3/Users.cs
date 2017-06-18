using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z3
{
    class Users
    {
        private int kod_uz, semestr;
        private String imie, nazwisko;

        public Users(int kod_uz, String imie, String nazwisko, int semestr)
        {
            this.kod_uz = kod_uz;
            this.imie = imie;
            this.nazwisko = nazwisko;
            this.semestr = semestr;
        }

        public String getImie()
        {
            return imie;
        }

        public int getkod_uz()
        {
            return kod_uz;
        }

        public int getsemestr()
        {
            return semestr;
        }

        public String getNazwisko()
        {
            return nazwisko;
        }
    }
}
