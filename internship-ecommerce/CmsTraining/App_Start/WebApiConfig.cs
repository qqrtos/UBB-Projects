using System.Web.Http;

namespace CmsTraining.App_Start {
    public class WebApiConfig {

        public static void Register(HttpConfiguration configuration) {
            configuration.Routes.MapHttpRoute("App API Default", "api/{controller}/{action}/{id}", new { id = RouteParameter.Optional });
        }
    }
}