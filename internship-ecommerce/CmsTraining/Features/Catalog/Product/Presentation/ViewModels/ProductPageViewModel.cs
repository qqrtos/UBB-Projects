using CmsTraining.Features.Catalog.Category.Presentation.ViewModels;
using System.Collections.Generic;

namespace CmsTraining.Features.Catalog.Product.Presentation.ViewModels
{
    public class ProductPageViewModel
    {
        public ProductItemViewModel Product { get; set; }

        public List<VariantItemViewModel> Variants { get; set; }
        public BreadCrumbViewModel Breadcrumb { get; set; }

        public ProductPageViewModel(ProductItemViewModel product, List<VariantItemViewModel> variants)
        {
            Product = product;
            Variants = variants;
        }

    }
}