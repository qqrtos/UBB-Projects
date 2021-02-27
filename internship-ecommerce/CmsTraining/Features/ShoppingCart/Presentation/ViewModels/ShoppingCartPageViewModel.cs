using CmsTraining.Features.ShoppingCart.Domain;
using CmsTraining.Models.Pages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CmsTraining.Features.ShoppingCart.Presentation.ViewModels
{
    public class ShoppingCartPageViewModel
    {
        public readonly ShoppingCartPage _shoppingCartPage;
        public readonly ShoppingCartWrapper _shoppingCartWrapper;

        public ShoppingCartPageViewModel(ShoppingCartPage shoppingCartPage, ShoppingCartWrapper shoppingCartWrapper)
        {
            _shoppingCartPage = shoppingCartPage;
            _shoppingCartWrapper = shoppingCartWrapper;
        }
    }
}