using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Framework.Blobs;
using EPiServer.Framework.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Media {
    [ContentType(DisplayName = "Image File",
        GUID = "223105F9-5484-4DF2-91D6-FAB497CBAEFA",
        Description = "Use this to upload an image")]
    [MediaDescriptor(ExtensionString = "png,jpg,jpeg,gif")]
    public class ImageFileData : ImageData {
        [CultureSpecific]
        [Editable(true)]
        [Display(
            Name = "Description",
            Description = "Add description to your image",
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public virtual string Description { get; set; }

        [Display(
            Name = "Description",
            Description = "Thumbnail for your image",
            GroupName = SystemTabNames.Content,
            Order = 20)]
        public override Blob Thumbnail { get; set; }
    }
}