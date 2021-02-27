using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using Remotion.Linq.Parsing.Structure.NodeTypeProviders;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Pages {
    [ContentType(DisplayName = "Register Login Page",
        GUID = "66081ea0-783e-4f3b-91e4-0215a19dc9d6",
        Description = "The page on which the users registers or logs in if he already has an account.")]
    public class RegisterLoginPage : SitePage {
        [CultureSpecific]
        [Display(Name = "Register Login Title",
            Description = "Heading of the register login page.",
            Order = 10)]
        public override string Title { get; set; } = "Register Page";

        [CultureSpecific]
        [Display(Name = "Main body",
            Description = "Paragraph shown above the register/login form.",
            Order = 20)]
        public virtual XhtmlString MainBody { get; set; }

        [CultureSpecific]
        [Display(Name = "Main content area",
            Description = "Area where blocks of information are placed",
            Order = 30)]
        public virtual ContentArea MainContentArea { get; set; }
    }
}