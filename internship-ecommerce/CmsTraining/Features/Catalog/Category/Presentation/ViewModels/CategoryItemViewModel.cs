using CmsTraining.Features.Shared.Extensions;

namespace CmsTraining.Features.Catalog.Category.Presentation.ViewModels
{
    public class CategoryItemViewModel
    {
        public string Image { get; set; }

        public string DisplayName { get; set; }

        public string Link { get; set; }

        public CategoryItemViewModel(Domain.Category category)
        {
            Image = category.DefaultImage() ?? string.Empty;
            DisplayName = category.DisplayName;
            Link = category.ContentLink.ContentUrl();
        }
    }

}