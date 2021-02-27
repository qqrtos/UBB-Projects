using EPiServer.Commerce.Order;
using EPiServer.ServiceLocation;
using Mediachase.Commerce;
using System;
using System.Collections.Generic;
using System.Linq;

namespace CmsTraining.Features.ShoppingCart.Domain
{
    public class ShoppingCartWrapper
    {
        private readonly IOrderGroupFactory _orderGroupFactory;
        public ShoppingCartWrapper(ICart shoppingCart)
        {
            ShoppingCart = shoppingCart ?? throw new ArgumentNullException("Cart is empty");
            _orderGroupFactory = ServiceLocator.Current.GetInstance<IOrderGroupFactory>();
        }

        public ICart ShoppingCart { get; set; }

        public List<ILineItem> LineItems => ShoppingCart.GetAllLineItems().ToList();

        public Money Total => ShoppingCart.GetTotal();
        public Money SubTotal => new Money(LineItems.Sum(x => x.PlacedPrice * x.Quantity), ShoppingCart.Currency);
        public Money ShippingTotal => ShoppingCart.GetShippingTotal();

        public Currency Currency => ShoppingCart.Currency;
        public int TotalCount => LineItems.Count();

        public ILineItem LineItemByCode(string code)
        {
            var lineItem = LineItems.FirstOrDefault(x =>
                x.Code.Equals(code, StringComparison.OrdinalIgnoreCase));

            return lineItem;
        }

        public ILineItem AddItemToCart(string code, int quantity)
        {
            var lineItem = LineItemByCode(code);
            if (lineItem == null)
            {
                lineItem = _orderGroupFactory.CreateLineItem(code, ShoppingCart);
                lineItem.Quantity = quantity;
                ShoppingCart.AddLineItem(lineItem);
            }
            else
            {
                var shipment = ShoppingCart.GetFirstShipment();
                ShoppingCart.UpdateLineItemQuantity(shipment, lineItem, lineItem.Quantity + quantity);
            }

            return lineItem;
        }

        public ILineItem UpdateItemQuantity(string code, int quantity)
        {
            if(quantity <= 0)
            {
                RemoveLineItem(code);
                return null;
            }

            var lineItem = LineItemByCode(code);
            if (lineItem == null)
                return null;

            var shipment = ShoppingCart.GetFirstShipment();
            ShoppingCart.UpdateLineItemQuantity(shipment, lineItem, quantity);
            return lineItem;
        }   

        private void RemoveLineItem(string code)
        {
            var lineItem = LineItemByCode(code);
            if (lineItem == null)
                return;

            var shipment = ShoppingCart.GetFirstShipment();
            shipment.LineItems.Remove(lineItem);
        }
    }
}