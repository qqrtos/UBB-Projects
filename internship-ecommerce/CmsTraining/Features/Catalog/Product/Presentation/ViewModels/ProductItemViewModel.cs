using Castle.Core.Internal;
using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Shared.Extensions;
using NHibernate.Mapping;
using System.Collections.Generic;

namespace CmsTraining.Features.Catalog.Product.Presentation.ViewModels
{
    public class ProductItemViewModel
    {
        public string DisplayName { get; set; }

        public string BrandName { get; set; }

        public string Description { get; set; }

        public List<string> Images { get; set; }

        public ProductItemViewModel(GenericProduct genericProduct)
        {
            DisplayName = genericProduct.DisplayName;
            BrandName = genericProduct.BrandName;
            Description = genericProduct.Description;
            Images = genericProduct.GetImages();
        }
    }
}