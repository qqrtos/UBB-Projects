using System.ComponentModel.DataAnnotations;
using System.Text.RegularExpressions;

namespace CmsTraining.Services.Validators {
    public class CustomEmailValidator : ValidationAttribute {
        private readonly string DefaultErrorMessage = "[CustomValidator] Email is invalid.";

        public string InvalidErrorMessage { get; set; }
        public string FieldEmptyErrorMessage { get; set; }

        protected override ValidationResult IsValid(object value, ValidationContext validationContext) {
            Regex emailValidator = new Regex(@"^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$");

            if (value == null) {
                return new ValidationResult(this.FieldEmptyErrorMessage ?? this.DefaultErrorMessage); 
            }

            if (!emailValidator.IsMatch(value.ToString())) {
                return new ValidationResult(this.InvalidErrorMessage ?? this.DefaultErrorMessage);
            }

            return ValidationResult.Success;
        }
    }
}