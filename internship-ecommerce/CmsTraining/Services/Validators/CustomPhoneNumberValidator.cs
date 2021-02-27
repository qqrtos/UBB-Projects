using System.ComponentModel.DataAnnotations;
using System.Text.RegularExpressions;

namespace CmsTraining.Services.Validators {
    public class CustomPhoneNumberValidator : ValidationAttribute{
        private readonly string DefaultErrorMessage = "This is not a valid phone number.";

        public string FieldEmptyErrorMessage { get; set; }
        public string InvalidPhoneNumberErrorMessage { get; set; }

        protected override ValidationResult IsValid(object value, ValidationContext validationContext) {
            Regex phonenumberValidator = new Regex(@"^\(?([0-9]{3})\)?([ .-]?)([0-9]{3})\2([0-9]{4})$");

            if (value == null) {
                return new ValidationResult(this.FieldEmptyErrorMessage ?? this.DefaultErrorMessage);
            }

            if (!phonenumberValidator.IsMatch(value.ToString())) {
                return new ValidationResult(this.InvalidPhoneNumberErrorMessage ?? this.DefaultErrorMessage);
            }

            return ValidationResult.Success;
        }
    }
}