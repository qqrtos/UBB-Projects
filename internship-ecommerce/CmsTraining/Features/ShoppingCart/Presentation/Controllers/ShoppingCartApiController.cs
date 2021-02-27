using CmsTraining.Features.ShoppingCart.Application;
using CmsTraining.Features.ShoppingCart.Presentation.ViewModels;
using EPiServer.Core;
using EPiServer.ServiceLocation;
using Mediachase.Commerce.Catalog;
using System.Web.Http;
using System.Web.Mvc;


namespace CmsTraining.Features.ShoppingCart.Presentation.Controllers
{
    public class ShoppingCartApiController : ApiController
    {
        private readonly ICartRepository _cartRepository;
        private readonly ReferenceConverter _referenceConverter;
        private readonly ShoppingCartValidator _shoppingCartValidator;

        public ShoppingCartApiController()
        {
            _cartRepository = ServiceLocator.Current.GetInstance<CartRepository>();
            _referenceConverter = ServiceLocator.Current.GetInstance<ReferenceConverter>();
            _shoppingCartValidator = ServiceLocator.Current.GetInstance<ShoppingCartValidator>();

        }

        [System.Web.Http.HttpPost]
        public IHttpActionResult AddItemToCart([Bind(Include = "Code,Quantity")] CodeAndQuantityViewModel codeAndQuantityViewModel) 
        {
            var code = codeAndQuantityViewModel.Code;
            var quantity = codeAndQuantityViewModel.Quantity;
            //Validation

            var variantRef = _referenceConverter.GetContentLink(code);
            if (variantRef == null || variantRef == ContentReference.EmptyReference)
                return Ok(new { hasError = true, message = "some message"});

            var cart = _cartRepository.LoadCart(true);
            if (cart == null)
                return Ok(new { hasError = true, message = "Cart misssing" });

            try
            {
                cart.AddItemToCart(code, quantity);
                _shoppingCartValidator.ValidateCartItems(cart.ShoppingCart);
                _cartRepository.Save(cart);
            }
            catch (System.Exception)
            {
                return Ok(new { hasError = true, message = "Item could not be added" });
            }

            MiniCartViewModel miniCart = new MiniCartViewModel{ Quantity = quantity };

            return Ok(new { miniCart });
        }

        [System.Web.Http.HttpPost]
        public IHttpActionResult UpdateQuantity([Bind(Include = "Code,Quantity")] CodeAndQuantityViewModel codeAndQuantityViewModel)
        {
            var code = codeAndQuantityViewModel.Code;
            var quantity = codeAndQuantityViewModel.Quantity;
            //Validation

            var variantRef = _referenceConverter.GetContentLink(code);
            if (variantRef == null || variantRef == ContentReference.EmptyReference)
                return Ok(new { hasError = true, message = "some message" });

            var cart = _cartRepository.LoadCart(true);
            if (cart == null)
                return Ok(new { hasError = true, message = "Cart misssing" });

            try
            {
                cart.UpdateItemQuantity(code, quantity);
                _cartRepository.Save(cart);
            }
            catch (System.Exception)
            {
                return Ok(new { hasError = true, message = "Item could not be updated" });
            }

            MiniCartViewModel miniCart = new MiniCartViewModel { Quantity = quantity };

            return Ok(new { miniCart });
        }

        [System.Web.Http.HttpGet]
        public IHttpActionResult GetCartTotal()
        {
            var shoppingCart = _cartRepository.LoadCart(true);          
            var price = shoppingCart.Total.Amount.ToString()+'$';
            return Ok(price);
        }

        [System.Web.Http.HttpGet]
        public decimal GetQuantity()
        {
            var shoppingCart = _cartRepository.LoadCart(false);
            if (shoppingCart != null)
            {
                decimal quantity = 0;
                foreach(var item in shoppingCart.LineItems)
                {
                    quantity += item.Quantity;
                }
                return quantity;
            }
            return 0;
        }
    }
}