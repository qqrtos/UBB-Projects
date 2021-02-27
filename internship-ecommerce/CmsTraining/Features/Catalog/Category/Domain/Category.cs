using EPiServer.Commerce.Catalog.ContentTypes;
using EPiServer.Commerce.Catalog.DataAnnotations;

namespace CmsTraining.Features.Catalog.Category.Domain
{
    [CatalogContentType(GUID = "809295be-1034-4722-939e-697fb441cc6e",
        DisplayName = "Category")]
    public class Category : NodeContent
    {
    }
}