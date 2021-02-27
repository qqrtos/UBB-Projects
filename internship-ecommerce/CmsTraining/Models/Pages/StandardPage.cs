using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Pages
{
    [ContentType(DisplayName = "StandardPage", 
        GUID = "f2eadb18-f7e8-4ea3-82b6-0c7836c1264b", 
        Description = "Use this page type unless you need a more specialized one.")]
    public class StandardPage : SitePage
    {
        [CultureSpecific]
        [Display(
            Name = "Main body",
            Description = "The main body will be shown in the main content area of the page, using the XHTML-editor you can insert for example text, images and tables.",
            GroupName = SystemTabNames.Content,
            Order = 150)]
        public virtual ContentArea MainContentArea { get; set; }

    }
}