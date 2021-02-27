using CmsTraining.Models.CustomEntities;
using EPiServer.Cms.Shell.UI.ObjectEditing.EditorDescriptors;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Shell.ObjectEditing;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks {
    [ContentType(DisplayName = "Register Block",
        GUID = "d990e7cc-aec1-46aa-999e-b0b10724bcd5",
        Description = "A block for users to input their register credentials")]
    public class RegisterBlock : BlockData {
        [CultureSpecific]
        [Display(
            Name = "Heading",
            Description = "The title of the login block.",
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public virtual string Heading { get; set; }

        [CultureSpecific]
        [Display(
            Name = "First name label",
            Description = "The text above the First Name input field.",
            GroupName = SystemTabNames.Content,
            Order = 12)]
        public virtual string FirstNameLabel { get; set; }

        [CultureSpecific]
        [Display(
            Name = "Last name label",
            Description = "The text above the Last Name input field.",
            GroupName = SystemTabNames.Content,
            Order = 15)]
        public virtual string LastNameLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "Email Label",
            Description = "The text above the email input field.",
            Order = 20)]
        public virtual string EmailLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "Gender label",
            Description = "The text above the gender selection field.",
            Order = 30)]
        public virtual string GenderLabel { get; set; }

        [Display(
            Name = "Phone number label",
            Description = "The text above the phone number input field",
            Order = 40)]
        public virtual string PhoneNumberLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "States label",
            Description = "The text above the states dropdown field.",
            Order = 45)]
        public virtual string StatesLabel { get; set; }

        [EditorDescriptor(EditorDescriptorType = typeof(CollectionEditorDescriptor<StateFieldEntry>))]
        public virtual IList<StateFieldEntry> StatesList { get; set; }

        [CultureSpecific]
        [Display(Name = "Password Label",
            Description = "The text above the password input field.",
            Order = 50)]
        public virtual string PasswordLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "Confirm password Label",
            Description = "The text above the password confirmation input field.",
            Order = 55)]
        public virtual string ConfirmPasswordLabel { get; set; }

        [CultureSpecific]
        [Display(Name = "Submit button text",
            Description = "The text above the submit button",
            Order = 60)]
        public virtual string SubmitButtonText { get; set; }
    }
}