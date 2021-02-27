using CmsTraining.Models.Pages;
using EPiServer.Web.Mvc;
using System.Web.Mvc;

namespace CmsTraining.Controllers {
    public class HomeController : PageController<HomePage> {
        public ActionResult Index(HomePage currentPage) {
            return View(currentPage);
        }
    }
}