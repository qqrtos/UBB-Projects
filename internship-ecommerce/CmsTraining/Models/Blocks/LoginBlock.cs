using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks {
    [ContentType(DisplayName = "Login Block",
        GUID = "f4a9f1c5-66b6-420a-baaa-8128fd319815",
        Description = "A block for users to input their login credentials")]
    public class LoginBlock : BlockData {
        [CultureSpecific]
        [Display(
            Name = "Heading",
            Description = "The title of the login block.",
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public virtual string Heading { get; set; }

        [CultureSpecific]
        [Display(Name = "Email text",
            Description = "The text above the emails input field.",
            Order = 20)]
        public virtual string EmailLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "Email placeholder text",
            Description = "The text that sshows when no email is typed yet.",
            Order = 25)]
        public virtual string EmailPlaceholder { get; set; }

        [CultureSpecific]
        [Display(Name = "Password text",
            Description = "The text above the password input field.",
            Order = 30)]
        public virtual string PasswordLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "Submit button text",
            Description = "The text displayed on the submit button",
            Order =40)]
        public virtual string SubmitButtonText { get; set; }

    }
}