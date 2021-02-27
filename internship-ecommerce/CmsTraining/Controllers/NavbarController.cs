using CmsTraining.Models.Pages;
using CmsTraining.Models.ViewModels;
using EPiServer;
using EPiServer.Core;
using EPiServer.Filters;
using EPiServer.ServiceLocation;
using EPiServer.Web.Routing;
using System.Collections.Generic;
using System.Linq;
using System.Web.Mvc;
using System.Web.UI;

namespace CmsTraining.Controllers
{
    public class NavbarController : Controller
    {
        private readonly IContentRepository _contentRepository;

        public NavbarController(IContentRepository contentRepository)
        {
            _contentRepository = contentRepository;
        }
        
        // GET: Navbar
        public ActionResult Index()
        {
            var loader = ServiceLocator.Current.GetInstance<IContentLoader>();
            IEnumerable<SitePage> pages = FilterForVisitor.Filter(loader.GetChildren<SitePage>
                (ContentReference.StartPage)).Cast<SitePage>()
                .Where(page => page.DisplayInMenu && !(page is RegisterLoginPage));
            var startPage = _contentRepository.Get<HomePage>(ContentReference.StartPage);

            RegisterLoginPage registerPage = FilterForVisitor
                .Filter(loader.GetChildren<SitePage>(ContentReference.StartPage))
                .Where(page => page is RegisterLoginPage).FirstOrDefault() as RegisterLoginPage;

            var image = _contentRepository.Get<ImageData>(startPage.HeaderBl.Image);

            var imageUrl = string.Empty;
            if (!ContentReference.IsNullOrEmpty(image.ContentLink))
            {
                imageUrl = UrlResolver.Current.GetUrl(image);
            }
            var link = startPage.LinkURL;
            IPageRouteHelper pageRouteHelper = ServiceLocator.Current.GetInstance<IPageRouteHelper>();
            var currentPage = pageRouteHelper.Content ?? pageRouteHelper.Page;
            var model = new NavbarViewModel { RegisterPage = registerPage, Children = pages, Image = imageUrl, Link = link, CurrentPage = currentPage as SitePage };
            return PartialView("_Navbar", model);
        }
    }
}