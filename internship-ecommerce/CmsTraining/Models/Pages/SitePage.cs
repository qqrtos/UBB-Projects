using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Pages {

    [ContentType(DisplayName = "SitePage", 
        GUID = "a8792007-28d7-482a-9f06-54243a72c838", 
        Description = "The base page",
        AvailableInEditMode = false)]
    public abstract class SitePage : PageData
    {
        [CultureSpecific]
        [Display(Name = "Title",
         Description = "The title of the page",
         GroupName = SystemTabNames.Content,
         Order = 150)]
        public virtual string Title { get; set; }

        [CultureSpecific]
        [Display(Name = "Menu name",
         Description = "The name of the menu",
         GroupName = SystemTabNames.Content,
         Order = 200)]
        public virtual string MenuName { get; set; }

        [CultureSpecific]
        [Display(Name = "Display in menu",
         Description = "Checkbox for displaying in menu",
         GroupName = SystemTabNames.Content,
         Order = 250)]
        public virtual bool DisplayInMenu  { get; set; }

        public override void SetDefaultValues(ContentType contentType)
        {
            base.SetDefaultValues(contentType);

            //Set up your defaults here 
            MenuName = Name;
            DisplayInMenu = false;
        }
    }
}