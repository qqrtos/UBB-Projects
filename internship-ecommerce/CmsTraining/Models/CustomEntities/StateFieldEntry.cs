using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.CustomEntities {
    public class StateFieldEntry {
        [CultureSpecific]
        [Display(Name = "State field entry",
            Description = "Select field for a state",
            Order = 10)]
        public string Name { get; set; }
    }
}