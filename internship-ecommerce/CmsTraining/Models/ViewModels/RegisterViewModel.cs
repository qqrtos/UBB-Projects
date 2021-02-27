using CmsTraining.Services.Validators;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.ViewModels {
    public class RegisterViewModel {
        [Required(ErrorMessage = "First name is required")]
        public string FirstName { get; set; }

        [Required(ErrorMessage = "Last name is required")]
        public string LastName { get; set; }

        [CustomEmailValidator(
            InvalidErrorMessage = "Oopsie, this is not a valid email address.",
            FieldEmptyErrorMessage = "Bruh, can't leave this empty.")]
        public string Email { get; set; }

        [CustomPhoneNumberValidator(
            FieldEmptyErrorMessage = "Gimme your phone number (;",
            InvalidPhoneNumberErrorMessage = "Not really your phone number, is it? );")]
        public string PhoneNumber { get; set; }

        [Required(ErrorMessage = "A gender is required")]
        public string Gender { get; set; }

        public string SelectedState { get; set; }

        [DataType(DataType.Password)]
        [Required(ErrorMessage = "Input the Password")]
        public string Password { get; set; }

        [DataType(DataType.Password)]
        [Required(ErrorMessage = "Confirm your Password")]
        [System.ComponentModel.DataAnnotations.Compare("Password")]
        public string ConfirmPassword { get; set; }

        public IEnumerable<string> StateList { get; set; }
    }
}