using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Core;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Features.Shared.Blocks
{
    [ContentType(GUID = "d4a61e49-e112-4478-8ccf-c4181bfdeb5a",
        DisplayName = "Site Settings Block",
        AvailableInEditMode = false)]
    public class SiteSettingsBlock : BlockData
    {
        [Searchable(false)]
        [Display(
            Name = "Catalog Anchor Link",
            Order = 25)]
        [AllowedTypes(typeof(CatalogContent))]
        public virtual ContentReference CatalogStartLink { get; set; }
    }
}