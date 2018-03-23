using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Konferencja
{
    class Input
    {
        public string name;
        public JObject jobject;

        public Input(string json)
        {
            try
            {
                JObject parse = JObject.Parse(json);
                this.name = parse.Properties().Select(p => p.Name).FirstOrDefault();
                this.jobject = JObject.Parse(parse[this.name].ToString());
            }
            catch
            {
                this.name = null;
                this.jobject = null;
            }
        }

        public string GetValue(string name)
        {
            try
			{
				return this.jobject[name].ToString();
			}
			catch
			{
				return null;
			}
        }
    }
}
