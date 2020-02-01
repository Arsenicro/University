using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace z2
{
    class DbDataAccessHandler : DataAccessHandler
    {
        private NpgsqlConnection connection;
        List<Users> users = new List<Users>();

        protected override void CloseConnection()
        {
            connection.Close();
        }

        protected override void Connect()
        {
            connection = new NpgsqlConnection("Server=localhost;User Id=test;Password=cos;Database=ludzie;");
            connection.Open();
        }

        protected override void GetData()
        {
            NpgsqlCommand command = new NpgsqlCommand("SELECT * FROM uzytkownik", connection);
            NpgsqlDataReader dr = command.ExecuteReader();
            while (dr.Read())
            {
                users.Add( new Users(dr.GetInt32(0), dr.GetString(1), dr.GetString(2), dr.GetInt32(3) ) );
            }
        }

        protected override void ProcessData()
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
