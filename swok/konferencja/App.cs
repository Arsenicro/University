using System;
using System.Collections;
using System.Collections.Generic;
using System.Text;

namespace Konferencja
{
    class App
    {
        Database db;
        private string secret = "d8578edf8458ce06fbc5bb76a58c5ca4";

        public void Run()
        {
            bool connected = true;
            Queue<string> response = new Queue<string>();
            Output output = OpenResponse((new Input(Console.ReadLine())));
            response.Enqueue(output.CreateJson());
            if (output.status == "ERROR")
                connected = false;

            if(connected) db.CreateIfNotExist();

            while (connected)
            {
                Input input = new Input(Console.ReadLine());
                if (input.name == null)
                    break;
                output = Response(input);
                response.Enqueue(output.CreateJson());

            }

            foreach (string s in response)
            {
                Console.WriteLine(s);
            }

            if(connected) db.CloseConn();

        }

        public Output Response(Input input)
        {
            switch (input.name)
            {
                case "organizer":
                    return OrganizerResponse(input);
                case "event":
                    return EventResponse(input);
                case "user":
                    return UserResponse(input);
                case "talk":
                    return TalkResponse(input);
                case "register_user_for_event":
                    return RegisterForEventResponse(input);
                case "attendance":
                    return AttendanceResponse(input);
                case "evaluation":
                    return EvaluationResponse(input);
                case "reject":
                    return RejectResponse(input);
                case "proposal":
                    return ProposalResponse(input);
                case "friends":
                    return FriendsResponse(input);
                case "user_plan":
                    return UserPlanResponse(input);
                case "day_plan":
                    return DayPlanResponse(input);
                case "best_talks":
                    return BestTalkResponse(input);
                case "most_popular_talks":
                    return MostPopularTalkResponse(input);
                case "attended_talks":
                    return AttendedTalkResponse(input);
                case "abandoned_talks":
                    return AbandonedTalkResponse(input);
                case "recently_added_talks":
                    return NotImplementedResponse();
                case "rejected_talks":
                    return RejectedResponse(input);
                case "proposals":
                    return ProposalsResponse(input);
                case "friends_talks":
                    return FriendsTalkResponse(input);
                case "friends_events":
                    return FriendsEventsResponse(input);
                case "recommended_talks":
                    return NotImplementedResponse();
                default:
                    return NotImplementedResponse();
            }

        }

        //Dodane założenie - organizator nie jest uczestnikiem (zapytania uczestnika nie działają z loginem i hasłem organizatora)

        public Output OpenResponse(Input input)
        {
            try
            {
                this.db = new Database(input.GetValue("baza"), input.GetValue("login"), input.GetValue("password"));
            }
            catch
            {
                return new Output("ERROR");
            }
            return new Output("OK");
        }

        public Output OrganizerResponse(Input input)
        {
            if (input.GetValue("secret") != secret)
                return new Output("ERROR");

            if (db.InsertUser(input.GetValue("newlogin"), input.GetValue("newpassword"), "o"))
                return new Output("OK");

            return new Output("ERROR");
        }

        public Output EventResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 1)
                return new Output("ERROR");
            if (db.RegisterEvent(input.GetValue("eventname"), 
                DateTime.Parse(input.GetValue("start_timestamp")), 
                DateTime.Parse(input.GetValue("end_timestamp"))))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output UserResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 1)
                return new Output("ERROR");
            if (db.InsertUser(input.GetValue("newlogin"), input.GetValue("newpassword")))
                return new Output("OK");
            return new Output("ERROR");
        }

        //Dodajemy referat i pierwszą ocenę. 
        //Przyjmuję konwencję, że zatwierdzający musi być na referacie, żeby uniknąć konsekwencji z zapytaniem best_talks
        public Output TalkResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 1)
                return new Output("ERROR");
            if (db.Talk(input.GetValue("login"), input.GetValue("speakerlogin"),
                input.GetValue("talk"), input.GetValue("title"), DateTime.Parse(input.GetValue("start_timestamp")),
                input.GetValue("room"), Int32.Parse(input.GetValue("initial_evaluation")), input.GetValue("eventname")))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output RegisterForEventResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            if (db.RegisterForEvent(input.GetValue("login"), input.GetValue("eventname")))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output AttendanceResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            if (db.Attendance(input.GetValue("login"), input.GetValue("talk")))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output EvaluationResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            if (db.Evaluation(input.GetValue("login"), input.GetValue("talk"), Int32.Parse(input.GetValue("rating"))))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output RejectResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 1)
                return new Output("ERROR");
            if (db.Reject(input.GetValue("talk")))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output ProposalResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            if (db.Proposal(input.GetValue("talk"), input.GetValue("login"), 
                input.GetValue("title"), DateTime.Parse(input.GetValue("start_timestamp"))))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output FriendsResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login1"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            if (db.Friend(input.GetValue("login1"), input.GetValue("login2")))
                return new Output("OK");
            return new Output("ERROR");
        }

        public Output UserPlanResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), "") != -1)
                return new Output("ERROR");
            Data[] data = db.UserPlan(input.GetValue("login"), Int32.Parse(input.GetValue("limit")));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output DayPlanResponse(Input input)
        {
            Data[] data = db.DayPlan(DateTime.Parse(input.GetValue("timestamp")));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output BestTalkResponse(Input input)
        {
            Data[] data = db.BestTalk(DateTime.Parse(input.GetValue("start_timestamp")), DateTime.Parse(input.GetValue("end_timestamp")),
                                        Int32.Parse(input.GetValue("limit")), (input.GetValue("all") == "1"));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output MostPopularTalkResponse(Input input)
        {
            Data[] data = db.MostPopularTalk(DateTime.Parse(input.GetValue("start_timestamp")), 
                DateTime.Parse(input.GetValue("end_timestamp")), Int32.Parse(input.GetValue("limit")));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output AttendedTalkResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            Data[] data = db.AttendedTalk(input.GetValue("login"));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output AbandonedTalkResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 1)
                return new Output("ERROR");
            Data[] data = db.AbandonedTalk(Int32.Parse(input.GetValue("limit")));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output FriendsTalkResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            Data[] data = db.FriendsTalk(input.GetValue("login"),DateTime.Parse(input.GetValue("start_timestamp")),
                DateTime.Parse(input.GetValue("end_timestamp")), Int32.Parse(input.GetValue("limit")));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output ProposalsResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 1)
                return new Output("ERROR");
            Data[] data = db.Proposals();
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output FriendsEventsResponse(Input input)
        {
            if (db.CheckUser(input.GetValue("login"), input.GetValue("password")) != 0)
                return new Output("ERROR");
            Data[] data = db.FriendsEvents(input.GetValue("login"), input.GetValue("event"));
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output RejectedResponse(Input input)
        {
            int user = db.CheckUser(input.GetValue("login"), input.GetValue("password"));
            if (user < 0)
                return new Output("ERROR");
            Data[] data = db.RejectedTalks(input.GetValue("login"), user==1);
            if (data != null)
                return new Output("OK", data);
            return new Output("ERROR");
        }

        public Output NotImplementedResponse()
        {
            return new Output("NOT IMPLEMENTED");
        }

    }
}
