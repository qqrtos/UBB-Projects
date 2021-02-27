using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Shared.Extensions;
using Mediachase.Commerce;
using Mediachase.Commerce.InventoryService;
using System.Collections.Generic;

namespace CmsTraining.Features.Catalog.Product.Presentation.ViewModels
{
    public class VariantItemViewModel
    {
        public string Name { get; }
        
        public Money Price { get; set; }

        public string PriceFormatted => new Money(Price, Currency.USD).ToString();

        public decimal Inventory { get; set; }

        public string Color { get; }
        public string Size { get; }

        public List<string> Images { get; }

        public string Code { get; set; }

        public VariantItemViewModel(GenericVariant variant)
        {
            Name = variant.Name;
            // Price = GetPrice(variant);
            Color = variant.Color;
            Size = variant.Size;
            Images = variant.GetImages();
            Code = variant.Code;
        }
    }
}