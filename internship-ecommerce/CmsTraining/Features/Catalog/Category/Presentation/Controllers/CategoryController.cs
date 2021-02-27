using CmsTraining.Features.Catalog.Category.Application;
using CmsTraining.Features.Catalog.Category.Presentation.ViewModels;
using CmsTraining.Features.Catalog.Product.Domain;
using CmsTraining.Features.Shared.Services;
using EPiServer;
using EPiServer.Web.Mvc;
using System.Linq;
using System.Web.Mvc;


namespace CmsTraining.Features.Catalog.Category.Presentation
{
    public class CategoryController : ContentController<Domain.Category>
    {
        private readonly IContentLoader _contentLoader;
        private readonly CategoryFactory _categoryFactory;
        private readonly BreadcrumbService _breadcrumbService;

        public CategoryController(IContentLoader contentLoader, CategoryFactory categoryFactory, BreadcrumbService breadcrumbService)
        {
            _contentLoader = contentLoader;
            _categoryFactory = categoryFactory;
            _breadcrumbService = breadcrumbService;
        }

        public ActionResult Index(Domain.Category currentContent)
        {
            var breadcrumb =  _breadcrumbService.GenerateBreadCrumb(currentContent);
            var categories = _contentLoader.GetChildren<Domain.Category>(currentContent.ContentLink)
                .ToList();

            if (categories.Any())
            {
                var categoryItems = categories
                    .Select(x => new CategoryItemViewModel(x))
                    .ToList();

                var categoryViewModel = new CategoryPageViewModel(currentContent) {
                    Categories = categoryItems
                };

                categoryViewModel.Breadcrumb = breadcrumb;
                //TODO: Add view path
                return View("~/Features/Catalog/Category/Presentation/Views/Index.cshtml",
                    categoryViewModel);
            }

            var products = _contentLoader.GetChildren<GenericProduct>(currentContent.ContentLink)
                .Select(_categoryFactory.BuildProductItem)
                .Where(x => x.MinPrice != 0)
                .ToList();
            
         

            var viewModel = new CategoryPageViewModel(currentContent) {
                Products = products
            };
            viewModel.Breadcrumb = breadcrumb;


            return View("~/Features/Catalog/Category/Presentation/Views/Index.cshtml",
                viewModel);

        }
        
    }
}