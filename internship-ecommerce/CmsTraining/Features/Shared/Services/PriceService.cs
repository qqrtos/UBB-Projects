using CmsTraining.Features.Catalog.Product.Domain;
using Mediachase.Commerce;
using Mediachase.Commerce.Pricing;
using System.Collections.Generic;
using System.Linq;

namespace CmsTraining.Features.Shared.Services
{
    public class PriceService
    {
        private readonly IPriceDetailService _priceService;

        public PriceService(IPriceDetailService priceService, ICurrentMarket currentMarket)
        {
            _priceService = priceService;
        }

        public List<IPriceDetailValue> GetPrices(GenericProduct product)
        {
            IList<IPriceDetailValue> prices = _priceService.List(product.ContentLink);
            return prices.ToList();
        }

        public List<IPriceDetailValue> GetPrices(GenericVariant variant)
        {
            IList<IPriceDetailValue> prices = _priceService.List(variant.ContentLink);
            return prices.ToList();
        }
    }
}