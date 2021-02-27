using System;
using System.ComponentModel.DataAnnotations;
using EPiServer;
using EPiServer.Web;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.SpecializedProperties;

namespace CmsTraining.Models.Pages
{
    [ContentType(DisplayName = "Shopping Cart Page",
        GUID = "a95055de-84d3-45c0-937f-73ff5a2c058a", 
        Description = "This page contains the summary of the chosen products")]
    public class ShoppingCartPage : SitePage
    {
        [CultureSpecific]
        [Display(Name = "Sum",
         Description = "The sum of the cart",
         GroupName = SystemTabNames.Content,
         Order = 150)]
        public virtual double Sum { get; set; }

        [CultureSpecific]
        [Display(Name = "HTMLTextField",
         Description = "A HTML text field for data/ info output",
         GroupName = SystemTabNames.Content,
         Order = 200)]
        public virtual string HTMLTextField { get; set; }

        [CultureSpecific]
        [Display(
           GroupName = SystemTabNames.Content,
           Order = 350)]
        public virtual ContentArea MainContentArea { get; set; }

        [CultureSpecific]
        [Display(Name = "isEmpty",
        Description = "The flag of the cart whether it is empty or not",
        GroupName = SystemTabNames.Content,
        Order = 0)]
        public virtual bool isEmpty { get; set; }

        [CultureSpecific]
        [Display(Name = "RedirectUrl",
        Description = "The url for redirection when the car is empty",
        GroupName = SystemTabNames.Content,
        Order = 1)]
        public virtual Url RedirectUrl { get; set; }


        [CultureSpecific]
        [UIHint(UIHint.Image)]
        [Display(Name = "Cart img",
        Description = "The image for the cart",
        GroupName = SystemTabNames.Content,
        Order = 0)]
        public virtual ContentReference Image { get; set; }

    }

}