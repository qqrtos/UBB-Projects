using CmsTraining.Features.Shared.Blocks;
using CmsTraining.Models.Blocks;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Pages {

    [ContentType(DisplayName = "Home Page",
        GUID = "8727b794-70fc-47e0-9b1e-65bda6b8e2a3",
        Description = "")]
    public class HomePage : SitePage 
    {
        [Display(
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public override string Title { get; set; }

        [Display(
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public virtual HeaderBlock HeaderBl { get; set; }

        [Display(
            GroupName = SystemTabNames.Content,
            Order = 20)]
        public virtual ContentArea MainContentArea { get; set; }
        
        [AllowedTypesAttribute(new []{ typeof(FooterBlock)})]
        public virtual ContentArea Footer { get; set; }

        #region Settings
        [Display(
            GroupName = "Settings",
            Order = 500)]
        public virtual SiteSettingsBlock SettingsBlock { get; set; }
        #endregion
    }
}