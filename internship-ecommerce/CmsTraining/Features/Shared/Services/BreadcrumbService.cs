using CmsTraining.Features.Catalog.Category.Domain;
using CmsTraining.Features.Catalog.Category.Presentation.ViewModels;
using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Models.Pages;
using EPiServer;
using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Core;
using EPiServer.Web.Routing;
using System.Collections.Generic;

namespace CmsTraining.Features.Shared.Services
{
    public class BreadcrumbService
    {
        private readonly IContentRepository _contentRepository;
        public BreadcrumbService(IContentRepository contentRepository)
        {
            _contentRepository = contentRepository;
        }

        public BreadCrumbViewModel GenerateBreadCrumb(Category currentContent)
        {
            CatalogContentBase content = currentContent;
            var models = new List<CatalogContentModel>();
            while (!(content is CatalogContent))
            {
                var parentContent = _contentRepository.Get<CatalogContentBase>(content.ParentLink);
                var model = new CatalogContentModel()
                {
                    DisplayName = parentContent is NodeContent ? ((NodeContent)parentContent).DisplayName : parentContent.Name,
                    Url = UrlResolver.Current.GetUrl(parentContent)
                };
                models.Add(model);
                content = parentContent;
            }

            models.Reverse();
            models.RemoveAt(0);
            models.Add(new CatalogContentModel { DisplayName = currentContent.DisplayName });

            var startPage = _contentRepository.Get<HomePage>(ContentReference.StartPage);

            return new BreadCrumbViewModel() { Models = models, HomepageUrl = startPage.LinkURL };
        }

        public BreadCrumbViewModel GenerateBreadCrumb(GenericProduct currentContent)
        {
            CatalogContentBase content = currentContent;
            var models = new List<CatalogContentModel>();
            while (!(content is CatalogContent))
            {
                var parentContent = _contentRepository.Get<CatalogContentBase>(content.ParentLink);
                var model = new CatalogContentModel()
                {
                    DisplayName = parentContent is NodeContent ? ((NodeContent)parentContent).DisplayName : parentContent.Name,
                    Url = UrlResolver.Current.GetUrl(parentContent)
                };
                models.Add(model);
                content = parentContent;
            }

            models.Reverse();
            models.RemoveAt(0);
            models.Add(new CatalogContentModel { DisplayName = currentContent.DisplayName });

            var startPage = _contentRepository.Get<HomePage>(ContentReference.StartPage);

            return new BreadCrumbViewModel() { Models = models , HomepageUrl = startPage.LinkURL};
        }
    }
}