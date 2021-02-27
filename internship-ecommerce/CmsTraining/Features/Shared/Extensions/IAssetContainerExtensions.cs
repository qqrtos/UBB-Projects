using CmsTraining.Models.Media;
using EPiServer;
using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Core;
using EPiServer.ServiceLocation;
using System.Collections.Generic;
using System.Linq;

namespace CmsTraining.Features.Shared.Extensions
{
    public static class IAssetContainerExtensions
    {
        private static Injected<IContentLoader> ContentLoader;

        public static string DefaultImage(this IAssetContainer container)
        {
            return container.GetImages().FirstOrDefault();
        }

        public static List<string> GetImages(this IAssetContainer container)
        {
            return GetAssets<ImageFile>(container)
                .Select(x => x.ContentLink.ContentUrl())
                .ToList();
        }

        private static List<T> GetAssets<T>(this IAssetContainer container) 
            where T: MediaData
        {
            var result = new List<T>();
            if (container?.CommerceMediaCollection == null)
                return result;

            var mediaCollection = container.CommerceMediaCollection;
            foreach(var media in mediaCollection)
            {
                if (ContentLoader.Service.TryGet<T>(media.AssetLink, out var asset))
                    result.Add(asset);
            }

            return result;
        }
    }
}