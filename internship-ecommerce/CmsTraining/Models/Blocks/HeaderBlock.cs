using System;
using System.ComponentModel.DataAnnotations;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Web;

namespace CmsTraining.Models.Blocks
{
    [ContentType(DisplayName = "Header", GUID = "4fa90c1d-d150-4c61-a941-f8f1a98d1096", Description = "This is the header of the page")]
    public class HeaderBlock : BlockData
    {
        [Display(
           GroupName = SystemTabNames.Content,
           Order = 30)]
        [CultureSpecific]
        [UIHint(UIHint.Image)]
        public virtual ContentReference Image { get; set; }

        //[CultureSpecific]
        //[Display(Name = "MainContentArea",
        // Description = "Put here the navigation bar or other important stuff",
        // GroupName = SystemTabNames.Content,
        // Order = 150)]
        //public virtual ContentArea MainContentArea { get; set; }


    }
}