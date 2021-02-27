using EPiServer.Commerce.Order;
using Mediachase.Commerce.Customers;
using System.Collections.Generic;

namespace CmsTraining.Features.ShoppingCart.Application
{
    public class ShoppingCartValidator
    {
        private readonly CustomerContext _customerContext;
        private readonly ILineItemValidator _lineItemValidator;
        private readonly IPlacedPriceProcessor _placedPriceProcessor;
        private readonly IInventoryProcessor _inventoryProcessor;


        public ShoppingCartValidator(ILineItemValidator lineItemValidator, IPlacedPriceProcessor placedPriceProcessor,
            IInventoryProcessor inventoryProcessor, CustomerContext customerContext)
        {
            _lineItemValidator = lineItemValidator;
            _placedPriceProcessor = placedPriceProcessor;
            _customerContext = customerContext;
            _inventoryProcessor = inventoryProcessor;
        }


        public Dictionary<ILineItem, IList<ValidationIssue>> ValidateCartItems(ICart cart)
        {
            var validationIssues = new Dictionary<ILineItem, IList<ValidationIssue>>();

            cart.ValidateOrRemoveLineItems(
                (item, issue) => validationIssues.Add(item, new[] { issue }),
                _lineItemValidator);

            cart.UpdatePlacedPriceOrRemoveLineItems(
                _customerContext.GetContactById(cart.CustomerId),
                (item, issue) => validationIssues.Add(item, new[]{issue}),
                _placedPriceProcessor);

            cart.UpdateInventoryOrRemoveLineItems(
                (item, issue) => validationIssues.Add(item, new[] { issue }),
                _inventoryProcessor);

            return validationIssues;
        }
    }
}








