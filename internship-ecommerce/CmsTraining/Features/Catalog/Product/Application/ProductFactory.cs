using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Catalog.Product.Presentation.ViewModels;
using CmsTraining.Features.Shared.Services;
using System;
using System.Linq;

namespace CmsTraining.Features.Catalog.Product.Application
{
    public class ProductFactory
    {
        private readonly PriceService _priceService;
        private readonly InventoryService _inventoryService;

        public ProductFactory(PriceService priceService, InventoryService inventoryService)
        {
            _priceService = priceService;
            _inventoryService = inventoryService;
        }

        public VariantItemViewModel BuildVariantItem(GenericVariant variant)
        {
            var viewModel = new VariantItemViewModel(variant);

            viewModel.Price = _priceService
                .GetPrices(variant)
                .OrderBy(x => x.UnitPrice.Amount)
                .FirstOrDefault(x => x.ValidFrom.Date <= DateTime.Now)
                ?.UnitPrice ?? new Mediachase.Commerce.Money(0, "USD");

            viewModel.Inventory = _inventoryService
                .GetInventory(variant)
                .OrderBy(x => x.PurchaseAvailableQuantity)
                .FirstOrDefault()
                ?.PurchaseAvailableQuantity ?? decimal.Zero;

            return viewModel;
        }
    }
}