using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks
{
    [ContentType(
        DisplayName = "Image Slider Block",
        GUID = "fb352c6a-08c4-4334-b4cb-fe7e193176bd",
        Description = "Use to display an image slider.")]
    public class ImageSliderBlock : BlockData
    {
        [Display(
            Name = "Image slider item",
            GroupName = SystemTabNames.Content,
            Order = 10)]
        [AllowedTypes(typeof(ImageSliderBlockItem))]
        public virtual ContentArea Items { get; set; }
    }
}