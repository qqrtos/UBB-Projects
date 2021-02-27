using Newtonsoft.Json;
using Newtonsoft.Json.Serialization;
using System.IO;
using System.Web;

namespace CmsTraining.Services {
    public class JavaScriptConverter {
        [System.Diagnostics.CodeAnalysis.SuppressMessage("Microsoft.Usage", "CA2202:Do not dispose objects multiple times")]
        public static IHtmlString SerializeObject(object value) {
            using (var stringWriter = new StringWriter())
            using (var jsonWriter = new JsonTextWriter(stringWriter)) {
                Newtonsoft.Json.JsonSerializer serializer = new Newtonsoft.Json.JsonSerializer {
                    ContractResolver = new CamelCasePropertyNamesContractResolver()
                };
                jsonWriter.QuoteName = false;
                serializer.Serialize(jsonWriter, value);



                return new HtmlString(stringWriter.ToString());
            }
        }
    }
}