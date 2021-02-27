using Castle.Core.Internal;
using CmsTraining.Features.Catalog.Category.Presentation.ViewModels;
using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Shared.Extensions;
using CmsTraining.Features.Shared.Services;
using EPiServer;
using EPiServer.Commerce.Catalog.ContentTypes;
using System.Globalization;
using System.Linq;

namespace CmsTraining.Features.Catalog.Category.Application
{
    public class CategoryFactory
    {
        private readonly PriceService _priceService;
        private readonly IContentLoader _contentLoader;
        private const string ImagePlaceHolderUrl = "";
        
        public CategoryFactory(PriceService priceService, IContentLoader contentLoader)
        {
            _priceService = priceService;
            _contentLoader = contentLoader;
        }

        public ProductItemViewModel BuildProductItem(GenericProduct product)
        {
            var viewModel = new ProductItemViewModel(product);

            PopulatePrices(product, viewModel);
            PopulateImage(product, viewModel);

            return viewModel;
        }

        private void PopulatePrices(GenericProduct product, ProductItemViewModel viewModel)
        {
            var prices = _priceService.GetPrices(product)
                .OrderBy(x => x.UnitPrice.Amount);

            if (!prices.Any())
                return;

            var minPrice = prices.First();
            var maxPrice = prices.Last();

            viewModel.MinPrice = minPrice.UnitPrice.Amount;
            viewModel.MaxPrice = maxPrice.UnitPrice.Amount;
        }

        private void PopulateImage(GenericProduct product, ProductItemViewModel viewModel)
        {
            var image = product.DefaultImage();
            if (image == null)
            {
                var variants = _contentLoader.GetItems(product.GetVariants().ToList(), CultureInfo.CurrentUICulture)
                    .OfType<GenericVariant>()
                    .ToList();

                image = variants
                    .Select(x => x.DefaultImage())
                    .Where(x => !x.IsNullOrEmpty())
                    .FirstOrDefault();
            }

            if (image == null)
                image = ImagePlaceHolderUrl;

            viewModel.Image = image;
        }
    }
}