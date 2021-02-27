using Castle.Core.Internal;
using EPiServer.Core;
using EPiServer.ServiceLocation;
using EPiServer.Web.Routing;

namespace CmsTraining.Features.Shared.Extensions
{
    public static class UrlExtensions
    {
        private static Injected<UrlResolver> UrlResolver { get; set; }

        public static string ContentUrl(this ContentReference contentRef)
        {
            if (contentRef == null)
                return "#";
            
            var url = UrlResolver.Service.GetUrl(contentRef);
            if (url.IsNullOrEmpty())
                url = "#";

            return url;
        }
    }
}