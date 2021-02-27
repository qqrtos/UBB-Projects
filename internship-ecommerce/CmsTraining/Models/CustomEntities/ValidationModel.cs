namespace CmsTraining.Models.CustomEntities {
    public class ValidationModel {
        public bool IsValid { get; set; }

        public string ErrorMessage { get; set; } = null;
    }
}