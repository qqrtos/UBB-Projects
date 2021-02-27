using CmsTraining.Models.Pages;
using System.Collections.Generic;

namespace CmsTraining.Features.ShoppingCart.Presentation.ViewModels
{
    public class LineItemsViewModel
    {
        public List<ShoppingCartLineItemViewModel> Items { get; set; }

        public ShoppingCartPage shoppingCartPage { get; set; }

        public string Price { get; set; }

        public LineItemsViewModel(List<ShoppingCartLineItemViewModel> items)
        {
            Items = items;
        }
    }
}