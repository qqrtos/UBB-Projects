using System.Linq;
using System.Web.Mvc;

namespace CmsTraining {
    public class CustomRazorViewEngine : RazorViewEngine {
        public CustomRazorViewEngine() {
            PartialViewLocationFormats = PartialViewLocationFormats.Union(new[] {
                "~/Views/Shared/Blocks/{0}.cshtml",
                "~/Views/Blocks/{0}.cshtml"
            }).ToArray();
        }
    }
}