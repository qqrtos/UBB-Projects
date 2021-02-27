using CmsTraining.Models.Pages;
using EPiServer.Web.Mvc;
using System.Web.Mvc;
namespace CmsTraining.Controllers
{
    public class BlogPostPageController : PageController<BlogPostPage>
    {
        public ActionResult Index(BlogPostPage currentPage)
        {
            return View(currentPage);
        }
    }
}