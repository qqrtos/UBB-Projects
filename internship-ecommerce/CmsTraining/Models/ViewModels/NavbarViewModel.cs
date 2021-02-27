using CmsTraining.Models.Pages;
using EPiServer.Core;
using System.Collections.Generic;
using System.Web.UI;

namespace CmsTraining.Models.ViewModels
{
    public class NavbarViewModel
    {
       
        public NavbarViewModel()//IEnumerable<SitePage> children, string image, string link)
        {
            /*this.Children = children;
            Image = image;
            Link = link;*/
        }

        public RegisterLoginPage RegisterPage { get; set; }

        public IEnumerable<SitePage> Children { get; set; }
  
        public string Image { get; set; }
        
        public string Link { get; set; }

        public SitePage CurrentPage { get; set; }
    }
}