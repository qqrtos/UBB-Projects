using CmsTraining.Static;
using EPiServer;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Shell.ObjectEditing;
using EPiServer.Web;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks
{
    [ContentType
        (DisplayName = "HeroBlock",
        GUID = "72f346b5-ffad-4ace-b04f-a2677198a3fb",
        Description = "Use this for Hero Blocks")]
    public class HeroBlock : BlockData
    {
        [CultureSpecific]
        [Display(
            Name = "Category",
            GroupName = SystemTabNames.Content,
            Order = 5)]
        [SelectOne(SelectionFactoryType = typeof(CategoryListSelectionFactory))]
        public virtual string Category { get; set; }

        [Display(
           GroupName = SystemTabNames.Content,
           Order = 10)]
        [CultureSpecific]
        public virtual XhtmlString Title { get; set; }

        [Display(
           GroupName = SystemTabNames.Content,
           Order = 20)]
        [CultureSpecific]
        [UIHint(UIHint.Image)]
        public virtual ContentReference Image { get; set; }

        [Display(
           GroupName = SystemTabNames.Content,
           Order = 30)]
        [CultureSpecific]
        public virtual string Description { get; set; }

        [Display(
           GroupName = SystemTabNames.Content,
           Order = 40)]
        [CultureSpecific]
        public virtual Url LinkUrl { get; set; }
    }
}