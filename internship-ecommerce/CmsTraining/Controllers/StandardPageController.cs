using CmsTraining.Models.Pages;
using EPiServer.Web.Mvc;
using System.Web.Mvc;

namespace CmsTraining.Controllers
{
    public class StandardPageController : PageController<StandardPage>
    {
        public ActionResult Index(StandardPage currentPage)
        {
            return View(currentPage);
        }
    }
}