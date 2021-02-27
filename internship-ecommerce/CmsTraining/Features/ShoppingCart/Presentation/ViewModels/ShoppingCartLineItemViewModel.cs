using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CmsTraining.Features.ShoppingCart.Presentation.ViewModels
{
    public class ShoppingCartLineItemViewModel
    {
        public string DisplayName { get; }

        public decimal PlacedPrice { get; }

        public string PlacedPriceFormatted { get; }

        public string Color { get; }

        public string Size { get; }

        public string Image { get; }

        public decimal Quantity { get; }

        public string Code { get; }

        public ShoppingCartLineItemViewModel(string displayName, decimal placedPrice, string placedPriceFormatted, 
            string color, string size, string image, decimal quantity, string code)
        {
            DisplayName = displayName;
            PlacedPrice = placedPrice;
            PlacedPriceFormatted = placedPriceFormatted;
            Image = image;
            Color = color;
            Size = size;
            Quantity = quantity;
            Code = code;
        }
    }
}