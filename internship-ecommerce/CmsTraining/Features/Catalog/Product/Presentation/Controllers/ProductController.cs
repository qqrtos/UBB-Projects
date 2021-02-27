using CmsTraining.Features.Catalog.Product.Application;
using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Catalog.Product.Presentation.ViewModels;
using CmsTraining.Features.Shared.Services;
using EPiServer;
using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Web.Mvc;
using System.Globalization;
using System.Linq;
using System.Web.Mvc;
using ProductItemViewModel = CmsTraining.Features.Catalog.Product.Presentation.ViewModels.ProductItemViewModel;

namespace CmsTraining.Features.Catalog.Category.Presentation
{
    public class ProductController : ContentController<GenericProduct>
    {
        private readonly IContentLoader _contentLoader;
        private readonly ProductFactory _productFactory;
        private readonly BreadcrumbService _breadcrumbService;


        public ProductController(IContentLoader contentLoader, ProductFactory productFactory, BreadcrumbService breadcrumbService)
        {
            _contentLoader = contentLoader;
            _productFactory = productFactory;
            _breadcrumbService = breadcrumbService;
        }

        public ActionResult Index(GenericProduct currentContent)
        {
            var breadcrumb = _breadcrumbService.GenerateBreadCrumb(currentContent);
            var variantRefs = currentContent.GetVariants().ToList();
            var variants = _contentLoader.GetItems(variantRefs, CultureInfo.CurrentUICulture)
                .OfType<GenericVariant>()
                .Select(_productFactory.BuildVariantItem)
                .ToList();

            var viewModel = new ProductPageViewModel(new ProductItemViewModel(currentContent), variants);
            viewModel.Breadcrumb = breadcrumb;
            return View("~/Features/Catalog/Product/Presentation/Views/Index.cshtml", viewModel);
            //return View();
        }
    }
}