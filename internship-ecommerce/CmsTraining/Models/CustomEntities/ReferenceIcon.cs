using EPiServer.Core;
using EPiServer.Web;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.CustomEntities {
    public class ReferenceIcon {
        [Display(Name ="Icon")]
        [UIHint(UIHint.Image)]
        public virtual ContentReference Image { get; set; }

        [Display(Name = "Redirect to this URL")]
        public virtual string ReferenceUrl { get; set; }
    }
}