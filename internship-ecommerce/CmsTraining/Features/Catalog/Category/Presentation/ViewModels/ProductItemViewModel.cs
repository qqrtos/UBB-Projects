using Castle.Core.Internal;
using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Shared.Extensions;
using Mediachase.Commerce;

namespace CmsTraining.Features.Catalog.Category.Presentation.ViewModels
{
    public class ProductItemViewModel
    {
        public string DisplayName { get; set; }
        public string BrandName { get; set; }
        public string ShortDescription { get; set; }
        public string Image { get; set; }
        public decimal MinPrice { get; set; }
        public decimal MaxPrice { get; set; }
        public string MinPriceFormatted => new Money(MinPrice, Currency.USD).ToString();
        public string MaxPriceFormatted => new Money(MaxPrice, Currency.USD).ToString();

        public string Link { get; set; }

        public ProductItemViewModel(GenericProduct product)
        {
            DisplayName = product.DisplayName;
            BrandName = product.BrandName;
            ShortDescription = GetShortDescription(product.Description);
            Link = product.ContentLink.ContentUrl();
        }

        private string GetShortDescription(string description)
        {
            if (description.IsNullOrEmpty())
                return string.Empty;

            var shortDescription = description.Substring(0, 50);
            var lastIndexOfSpace = shortDescription.LastIndexOf(" ");
            return shortDescription.Substring(0, lastIndexOfSpace - 1); 
        }
    }
}