using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Web;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks
{
    [ContentType(DisplayName = "BlogPostBlock", 
        GUID = "63491671-bfc3-4716-86ce-afd9c520de51", 
        Description = "USe this to create a blog post block")]
    public class BlogPostBlock : BlockData
    {
        [CultureSpecific]
        [Display(Name = "Title",
         Description = "Use this to set the title of the block",
         GroupName = SystemTabNames.Content,
         Order = 150)]
        public virtual XhtmlString Title { get; set; }

        [CultureSpecific]
        [Display(Name = "Description",
         Description = "Use this to set the description of the block",
         GroupName = SystemTabNames.Content,
         Order = 200)]

        public virtual string Description { get; set; }
        [CultureSpecific]
        [Display(Name = "Blog Post Category",
         Description = "Use this to set the category of the block",
         GroupName = SystemTabNames.Content,
         Order = 400)]
        public virtual string Category { get; set; }

        [Display(Name = "Page image",
            Description = "Use this to set the image of the block",
            GroupName = SystemTabNames.Content, 
            Order = 300)]
        [UIHint(UIHint.Image)] // filters to only show images
        public virtual ContentReference PageImage { get; set; }

        [Display(Name = "Page Link",
           Description = "Use this to set the link of the read more button",
           GroupName = SystemTabNames.Content,
           Order = 500)]
        public virtual ContentReference Link { get; set; }

    }
}