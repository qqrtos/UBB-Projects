using CmsTraining.Models.Pages;
using EPiServer.Web.Mvc;
using System.Web.Mvc;

namespace CmsTraining.Controllers {
    public class RegisterLoginController : PageController<RegisterLoginPage> {
        // GET: RegisterLogin
        public ActionResult Index(RegisterLoginPage currentPage) {
            return View(currentPage);
        }
    }
}