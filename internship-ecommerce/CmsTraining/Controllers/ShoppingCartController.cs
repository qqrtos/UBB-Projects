using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Shared.Extensions;
using CmsTraining.Features.ShoppingCart.Application;
using CmsTraining.Features.ShoppingCart.Presentation.ViewModels;
using CmsTraining.Models.Pages;
using EPiServer;
using EPiServer.Commerce.Order;
using EPiServer.ServiceLocation;
using EPiServer.Web.Mvc;
using Mediachase.Commerce.Catalog;
using System.Linq;
using System.Web.Mvc;

namespace CmsTraining.Controllers
{
    public class ShoppingCartController : PageController<ShoppingCartPage>
    {
        private readonly ICartRepository _cartRepository;

        public ShoppingCartController(ICartRepository cartRepository)
        {
            _cartRepository = cartRepository;
        }

        public ActionResult Index(ShoppingCartPage currentPage)
        {
            var shoppingCart = _cartRepository.LoadCart(true);
            var lineItems = new LineItemsViewModel(new System.Collections.Generic.List<ShoppingCartLineItemViewModel>());
            foreach (ILineItem lineitem in shoppingCart.LineItems)
            {
                var contentLoader = ServiceLocator.Current.GetInstance<IContentLoader>();
                var referenceConverter = ServiceLocator.Current.GetInstance<ReferenceConverter>();
                var variantLink = referenceConverter.GetContentLink(lineitem.Code);
                var variant = contentLoader.Get<GenericVariant>(variantLink);

                var shoppingCartLineItemViewModel = new ShoppingCartLineItemViewModel(variant.DisplayName, lineitem.PlacedPrice, lineitem.PlacedPrice.ToString("0.00")+'$', variant.Color, variant.Size, variant.GetImages().FirstOrDefault(), lineitem.Quantity, lineitem.Code);
                lineItems.Items.Add(shoppingCartLineItemViewModel);
            }
            lineItems.shoppingCartPage = currentPage;
            lineItems.Price = shoppingCart.Total.Amount.ToString("0.00") +'$';
            return View(lineItems);
        }
    }
}