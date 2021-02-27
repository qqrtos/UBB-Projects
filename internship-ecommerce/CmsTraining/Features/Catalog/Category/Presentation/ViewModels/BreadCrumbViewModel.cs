using CmsTraining.Features.Catalog.Category.Domain;
using System.Collections.Generic;

namespace CmsTraining.Features.Catalog.Category.Presentation.ViewModels
{
    public class BreadCrumbViewModel
    {
        public IList<CatalogContentModel> Models;
        public string HomepageUrl { get; set; }
    }
}