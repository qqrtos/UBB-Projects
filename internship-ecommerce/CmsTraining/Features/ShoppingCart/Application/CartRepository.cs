using CmsTraining.Features.ShoppingCart.Domain;
using EPiServer.Commerce.Order;
using Mediachase.Commerce.Customers;
using Mediachase.Commerce.Orders;
using System;

namespace CmsTraining.Features.ShoppingCart.Application
{
    public interface ICartRepository
    {
        ShoppingCartWrapper LoadCart(bool createIfNotExists = false);
        ShoppingCartWrapper LoadCart(Guid customerId, bool createIfNotExists = false);
        ShoppingCartWrapper LoadCart(Guid customerId, string cartName, bool createIfNotExists = false);

        void Save(ShoppingCartWrapper cart);

        void Delete(string cartName);
        void Delete(Guid customerId, string cartName);
    }

    public class CartRepository : ICartRepository
    {
        private readonly IOrderRepository _orderRepository;
        public CartRepository(IOrderRepository orderRepository)
        {
            _orderRepository = orderRepository;
        }

        public void Delete(string cartName)
        {
            Delete(CustomerContext.Current.CurrentContactId, cartName);
        }

        public void Delete(Guid customerId, string cartName)
        {
            var cart = _orderRepository.LoadCart<ICart>(customerId, cartName);
            if (cart == null)
                return;

            _orderRepository.Delete(cart.OrderLink);
        }

        public ShoppingCartWrapper LoadCart(bool createIfNotExists = false)
        {
            return LoadCart(CustomerContext.Current.CurrentContactId, Cart.DefaultName, createIfNotExists);
        }

        public ShoppingCartWrapper LoadCart(Guid customerId, bool createIfNotExists = false)
        {
            return LoadCart(customerId, Cart.DefaultName, createIfNotExists);
        }

        public ShoppingCartWrapper LoadCart(Guid customerId, string cartName, bool createIfNotExists = false)
        {
            ShoppingCartWrapper shoppingCartWrapper = null;
            ICart cart;
            if (!createIfNotExists)
            {
                cart = _orderRepository.LoadCart<ICart>(customerId, cartName);
            }
            else
            {
                cart = _orderRepository.LoadOrCreateCart<ICart>(customerId, cartName);
            }

            if(cart != null)
            {
                shoppingCartWrapper = new ShoppingCartWrapper(cart);
            }

            return shoppingCartWrapper;
        }

        public void Save(ShoppingCartWrapper cart)
        {
            _orderRepository.Save(cart.ShoppingCart);
        }
    }
}