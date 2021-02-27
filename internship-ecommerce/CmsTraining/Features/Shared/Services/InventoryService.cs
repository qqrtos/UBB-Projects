using CmsTraining.Features.Catalog.Product.Domain;
using EPiServer;
using EPiServer.Commerce.Catalog.ContentTypes;
using Mediachase.Commerce.InventoryService;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;

namespace CmsTraining.Features.Shared.Services
{
    public class InventoryService
    {
        private readonly IInventoryService _inventoryService;
        private readonly IContentLoader _contentLoader;

        public InventoryService(IInventoryService inventoryService, IContentLoader contentLoader)
        {
            _inventoryService = inventoryService;
            _contentLoader = contentLoader;
        }

        public List<InventoryRecord> GetInventory(GenericProduct product)
        {
            var variantRefs = product.GetVariants().ToList();
            var variants = _contentLoader.GetItems(variantRefs, CultureInfo.CurrentUICulture)
                .OfType<GenericVariant>()
                .ToList();
            var variantCodes = variants.Select(x => x.Code);

            IList<InventoryRecord> inventoryRecords = _inventoryService.QueryByEntry(variantCodes);
            return inventoryRecords.ToList();
        }

        public List<InventoryRecord> GetInventory(GenericVariant variant)
        {
            IList<InventoryRecord> inventoryRecords = 
                _inventoryService.QueryByEntry(new string[] { variant.Code });

            return inventoryRecords.ToList();
        }
    }
}