using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Commerce.Catalog.DataAnnotations;
using EPiServer.DataAbstraction;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Features.Catalog.Product.Domain
{
    [CatalogContentType(
        GUID = "a0b9bb5f-3d8f-4ba5-a137-0d6afcdd3047",
        DisplayName = "Simple Variant")]
    public class GenericVariant : VariationContent
    {
        [Display(
            Name = "Color",
            Order = 50)]
        public virtual string Color { get; set; }

        [Display(
            Name = "Size",
            Order = 75)]
        public virtual string Size { get; set; }

        public override void SetDefaultValues(ContentType contentType)
        {
            base.SetDefaultValues(contentType);

            MinQuantity = 1;
            MaxQuantity = 100;
        }
    }
}