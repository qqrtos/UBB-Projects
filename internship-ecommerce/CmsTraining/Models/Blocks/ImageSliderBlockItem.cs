using CmsTraining.Static;
using EPiServer;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Shell.ObjectEditing;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks
{
    [ContentType(DisplayName = "Image Slider Block Item",
                 GUID = "34a6c75a-380d-4cd3-b592-ab1bf79d2808",
                 Description = "Represents an item of the image slider.")]
    [AvailableContentTypes(Availability.Specific, IncludeOn = new[] { typeof(ImageSliderBlock) })]
    public class ImageSliderBlockItem : BlockData
    {
        [CultureSpecific]
        [Display(
            Name = "Category",
            GroupName = SystemTabNames.Content,
            Order = 5)]
        [SelectOne(SelectionFactoryType = typeof(CategoryListSelectionFactory))]
        public virtual string Category { get; set; }

        [Display(
            Name = "Main image",
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public virtual ContentReference ImageData { get; set; }

        [CultureSpecific]
        [Display(
            Name = "Title",
            GroupName = SystemTabNames.Content,
            Order = 20)]
        public virtual XhtmlString TitleField { get; set; }

        [CultureSpecific]
        [Display(
            Name = "Description",
            GroupName = SystemTabNames.Content,
            Order = 30)]
        public virtual string Description { get; set; }

        [CultureSpecific]
        [Display(
            Name = "Link",
            GroupName = SystemTabNames.Content,
            Order = 40)]
        public virtual Url Link { get; set; }
    }
}