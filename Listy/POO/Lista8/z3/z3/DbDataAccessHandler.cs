using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z3
{
    class DbDataAccessHandler : Strategy
    {
        private NpgsqlConnection connection;
        List<Users> users = new List<Users>();

        public override void CloseConnection()
        {
            connection.Close();
        }

        public override void Connect()
        {
            connection = new NpgsqlConnection("Server=localhost;User Id=test;Password=cos;Database=ludzie;");
            connection.Open();
        }

        public override void GetData()
        {
            NpgsqlCommand command = new NpgsqlCommand("SELECT * FROM uzytkownik", connection);
            NpgsqlDataReader dr = command.ExecuteReader();
            while (dr.Read())
            {
                users.Add(new Users(dr.GetInt32(0), dr.GetString(1), dr.GetString(2), dr.GetInt32(3)));
            }
        }

        public override void ProcessData()
        {
            int suma = 0;
            foreach (Users user in users)
            {
                suma += user.getsemestr();
            }

            Console.WriteLine("Suma semestrów wynosi " + suma);
        }
    }
}
