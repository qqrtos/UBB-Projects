using CmsTraining.App_Start;
using System.Web.Http;
using System.Web.Mvc;
using System.Web.Optimization;
using System.Web.Routing;

namespace CmsTraining {
    public class EPiServerApplication : EPiServer.Global
    {
        protected void Application_Start()
        {
            AreaRegistration.RegisterAllAreas();

            //Tip: Want to call the EPiServer API on startup? Add an initialization module instead (Add -> New Item.. -> EPiServer -> Initialization Module)

            BundleConfig.RegisterBundles(BundleTable.Bundles);
            //WebApiConfig.Register(GlobalConfiguration.Configuration);
            ViewEngines.Engines.Insert(0, new CustomRazorViewEngine());
            
            RouteTable.Routes.MapHttpRoute(
               "Api", // Route name 
               "api/{controller}/{action}/{id}", // URL with parameters 
               new { id = RouteParameter.Optional } // Parameter defaults 
               );



            RouteTable.Routes.MapHttpRoute(
                "LanguageAwareApi", // Route name 
                "{language}/api/{controller}/{action}/{id}", // URL with parameters 
                new { id = RouteParameter.Optional } // Parameter defaults
                );



            RouteTable.Routes.MapRoute("defaultRoute", "{controller}/{action}");
            RouteTable.Routes.MapRoute("defaultRouteWithLanguage", "{language}/{controller}/{action}");
        }
    }
}