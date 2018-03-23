using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Text;

namespace Konferencja
{
    class Output
    {
        public string status;
        public Data[] data;

        public Output(string status, Data[] data)
        {
            this.status = status;
            this.data = data;
        }

        public Output(string status)
        {
            this.status = status;
            this.data = null;
        }

        public string CreateJson()
        {
           return JsonConvert.SerializeObject(this, Newtonsoft.Json.Formatting.None,
                                    new JsonSerializerSettings
                                    {
                                        NullValueHandling = NullValueHandling.Ignore
                                    }).Replace("\"_event\":", "\"event\":");
            //Replace bo nie mogę mieć zmiennej event
        }
    }
}
