using CmsTraining.Business;
using EPiServer.Framework;
using EPiServer.Framework.Initialization;
using EPiServer.ServiceLocation;
using System.Web.Mvc;

namespace CmsTraining {
    [InitializableModule]
    [ModuleDependency(typeof(EPiServer.Web.InitializationModule))]
    public class RegisterDependencyResolverInitializationModule : IConfigurableModule {
        public void ConfigureContainer(ServiceConfigurationContext context) {
            DependencyResolver.SetResolver(
                new StructureMapDependencyResolver(context.StructureMap()));
            //Implementations for custom interfaces can be registered here.
            context.ConfigurationComplete += (o, e) => {
                //Register custom implementations that should be used in favour of the
            };
        }
        public void Initialize(InitializationEngine context) {
        }

        public void Uninitialize(InitializationEngine context) {
        }
    }
}