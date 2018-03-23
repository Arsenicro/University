using Dapper;
using Npgsql;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace Konferencja
{
    class Database
    {
        NpgsqlConnection conn;

        public Database(string database, string login, string password)
        {
            string connstring = $"Server=localhost;User Id={login};Password={password};Database={database}";
            this.conn = new NpgsqlConnection(connstring);
            conn.Open();
        }

        public void CloseConn()
        {
            this.conn.Close();
        }

        public bool InsertUser(string login, string passwd, string role = "u")
        {

            string command = "SELECT * FROM wstaw_uczestnika(@login,@passwd,@role)";
            try
            {
                conn.Execute(command,
                    new
                    {
                        login = login,
                        passwd = passwd,
                        role = role
                    });

            }
            catch
            {
                return false;
            }

            return true;

        }   
 
        public bool RegisterEvent(string name, DateTime start, DateTime end)
        {

            string command = "SELECT * FROM  rejestracja_wydarzenia(@name,@start,@end)";
            try
            {
                conn.Execute(command, 
                    new
                    {
                        name = name,
                        start = start,
                        end = end
                    });
            }
            catch
            {
                return false;
            }

            return true;
        }

        public bool Talk(string login, string speakerlogin, string talk, string title, DateTime start, string room, int init, string eventname)
        {

            string command = "SELECT * FROM wstaw_referat(@login,@speakerlogin,@talk,@title,@start,@room,@init,@eventname)";

            try
            {
                conn.Execute(command,
                    new
                    {
                        login = login,
                        speakerlogin = speakerlogin,
                        talk = talk,
                        title = title,
                        start = start,
                        room = room,
                        init = init,
                        eventname = eventname
                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public bool RegisterForEvent(string login, string eventname)
        {

            string command = "SELECT * FROM rejestracja_na_wydarzenie(@login,@eventname)";

            try
            {
                conn.Execute(command,
                    new
                    {
                        login = login,
                        eventname = eventname
                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public bool Attendance(string login, string talk)
        {

            string command = $"SELECT * FROM odnotuj_obecnosc(@login,@talk)";

            try
            {
                conn.Execute(command,
                    new
                    {
                        login = login,
                        talk = talk
                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public bool Evaluation(string login, string talk, int rating)
        {

            string command = $"SELECT * FROM ocen_referat(@login,@talk,@rating)";

            try
            {
                conn.Execute(command,
                    new
                    {
                        login = login,
                        talk = talk,
                        rating = rating
                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public bool Reject(string talk)
        {

            string command = "SELECT * FROM odrzuc_referat(@talk)";

            try
            {
                conn.Execute(command, 
                    new
                    {
                        talk = talk
                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public bool Proposal(string talk, string login, string title, DateTime start)
        {

            string command = $"SELECT * FROM proponuj_referat(@talk,@login,@title,@start)";

            try
            {
                conn.Execute(command,
                    new
                    {
                        talk = talk,
                        login = login,
                        title = title,
                        start = start

                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public bool Friend(string login1, string login2)
        {

            string command = $"SELECT * FROM proponuj_znajomosc(@login1,@login2)";
            try
            {
                conn.Execute(command,
                    new
                    {
                        login1 = login1,
                        login2 = login2
                    });
            }
            catch
            {
                return false;
            }

            return true;

        }

        public Data[] UserPlan(string login, int limit)
        {
            string command;
            if (limit == 0)
                command = $"SELECT * FROM plan(@login)";
            else
                command = $"SELECT * FROM plan(@login,@limit)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        login = login,
                        limit = limit
                    }).ToArray();
                return data;
            }
            catch
            {
                return null;
            }

        }

        public Data[] DayPlan(DateTime day)
        {
            string command = $"SELECT * FROM plan_dnia(@day)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        day = day
                    }).ToArray();
                return data;
            }
            catch
            {
                return null;
            }

        }

        public Data[] BestTalk(DateTime start, DateTime end, int limit, bool all)
        {
            string command = "SELECT * FROM ";

            if (all)
                command += "wszystkie_";
            command += $"najlepsze_referaty(@start,@end";
            if (limit != 0)
                command += $",@limit";
            command += ")";
                
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        start = start,
                        end = end,
                        limit = limit
                    }).ToArray();
                return data;
            }
            catch
            {
                return null;
            }

        }

        public Data[] MostPopularTalk(DateTime start, DateTime end, int limit)
        {
            string command;
            if (limit == 0)
                command = $"SELECT * FROM najpopularniejsze_referaty(@start,@end)";
            else
                command = $"SELECT * FROM najpopularniejsze_referaty(@start,@end,@limit)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        start = start,
                        end = end,
                        limit = limit
                    }).ToArray();
                return data;
            }
            catch 
            {
                return null;
            }

        }

        public Data[] AttendedTalk(string login)
        {
            string command =$"SELECT * FROM referaty_uczestnika(@login)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        login = login
                    }).ToArray();
                return data;
            }
            catch
            {
                return null;
            }
        }
        
        public Data[] RejectedTalks(string login, bool organizer)
        {
            string command;
            if(organizer)
                command = $"SELECT * FROM wszystkie_odrzucone()";
            else
                command = $"SELECT * FROM moje_odrzucone(@login)";
            try
            {
                Data[] data = conn.Query<Data>(command,
                    new
                    {
                        login = login
                    }).ToArray();
                return data;
            }
            catch

            {
                return null;
            }

        }

        public Data[] Proposals()
        {
            string command;
            command = $"SELECT * FROM propozycje()";
            try
            {
                Data[] data = conn.Query<Data>(command).ToArray();
                return data;
            }
            catch

            {
                return null;
            }

        }

        public Data[] AbandonedTalk(int limit)
        {
            string command;
            if (limit == 0)
                command = $"SELECT * FROM porzucone_referaty()";
            else
                command = $"SELECT * FROM porzucone_referaty(@limit)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        limit = limit
                    }).ToArray();
                return data;
            }
            catch
            {
                return null;
            }

        }

        public Data[] FriendsTalk(string login, DateTime start, DateTime end, int limit)
        {
            string command;
            if (limit == 0)
                command = $"SELECT * FROM referaty_znajomych(@login,@start,@end)";
            else
                command = $"SELECT * FROM referaty_znajomych(@login,@start,@end,@limit)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        login = login,
                        start = start,
                        end = end,
                        limit = limit
                    }).ToArray();
                return data;
            }
            catch

            {
                return null;
            }

        }

        public Data[] FriendsEvents(string login, string name)
        {
            string command;
            command = $"SELECT * FROM znajomi_na_wydarzeniach(@login,@name)";
            try
            {
                Data[] data = conn.Query<Data>(command, 
                    new
                    {
                        login = login,
                        name = name
                    }).ToArray();
                return data;
            }
            catch

            {
                return null;
            }

        }

        //Wyjasnienie:
        //-2 - Użytkownik nie istnieje
        //-1 - Złe hasło
        //0 - Zwykły uczestnik
        //1 - Organizator
        public int CheckUser(string login, string passwd)
        {
            bool exist, logged, organizer;
            string command = $"SELECT * FROM uczestnik WHERE login = @login";
            NpgsqlCommand cmd = new NpgsqlCommand(command, conn);
            cmd.Parameters.AddWithValue("login",login);
            NpgsqlDataReader reader = cmd.ExecuteReader();

            exist = (reader.Read());
            
            logged = (exist && reader[1].ToString() == passwd);
            
            organizer = (logged && reader[2].ToString() == "o");

            reader.Close();

            if (!exist)
                return -2;
            if (!logged)
                return -1;
            if (!organizer)
                return 0;
            return 1;
        }

        public void CreateIfNotExist()
        {
            bool test = false;
            string command = $"SELECT * FROM pg_tables WHERE tablename='uczestnik'";
            try
            {
                NpgsqlCommand cmd = new NpgsqlCommand(command, conn);
                NpgsqlDataReader reader = cmd.ExecuteReader();
                test = (!reader.Read()) ? true : false;
                reader.Close();
            }
            catch
            {
                return;
            }

            if (test)
            {
                command = File.ReadAllText(@"fizyczny.sql");
                try
                {
                    NpgsqlCommand cmd = new NpgsqlCommand(command, conn);
                    NpgsqlDataReader reader = cmd.ExecuteReader();
                    reader.Close();
                }
                catch 
                {
                }
            }
        }
    }
}
