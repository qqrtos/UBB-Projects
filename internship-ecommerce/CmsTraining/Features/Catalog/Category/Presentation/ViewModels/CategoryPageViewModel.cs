using System.Collections.Generic;

namespace CmsTraining.Features.Catalog.Category.Presentation.ViewModels
{
    //TODO: implement pagination
    public class CategoryPageViewModel
    {
        public string CategoryName { get; }
        public List<CategoryItemViewModel> Categories { get; set; }
        public List<ProductItemViewModel> Products { get; set; }
        public BreadCrumbViewModel Breadcrumb { get; set; }
        public CategoryPageViewModel(Domain.Category category)
        {
            CategoryName = category.DisplayName;
        }
    }
}