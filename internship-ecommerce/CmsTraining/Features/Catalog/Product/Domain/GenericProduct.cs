using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Commerce.Catalog.DataAnnotations;
using EPiServer.DataAbstraction;
using EPiServer.Web;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Features.Catalog.Product.Domain
{
    [CatalogContentType(GUID = "193e6c0c-6184-43fb-8e20-7d427bed3a46",
        DisplayName = "Simple Product")]
    public class GenericProduct : ProductContent
    {
        [Display(
            Name = "Product Description",
            Description = "Description for the product",
            GroupName = SystemTabNames.Content,
            Order = 50)]
        [UIHint(UIHint.Textarea)]
        public virtual string Description { get; set; }

        [Display(
            Name = "Product Brand Name",
            Description = "Brand name for product",
            GroupName = SystemTabNames.Content,
            Order = 150)]
        public virtual string BrandName { get; set; }
    }
}