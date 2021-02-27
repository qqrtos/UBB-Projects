using CmsTraining.Models.Blocks;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Pages
{
    [ContentType(DisplayName = "BlogPostPage", GUID = "18d47fba-378f-4fcf-ad5d-fc50d0d78925", Description = "")]

    [AvailableContentTypes(Include = new[] { typeof(BlogPostBlock) })]
    public class BlogPostPage : SitePage
    {
        [Display(Name = "Main content area",
            Description = "The main content area contains an ordered collection to blog post blocks",
            GroupName = SystemTabNames.Content, Order = 30)]
        public virtual ContentArea MainContentArea { get; set; }
    }
}