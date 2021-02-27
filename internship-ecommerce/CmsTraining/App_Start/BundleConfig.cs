using System.Web.Optimization;

namespace CmsTraining.App_Start {
    public class BundleConfig {
        public static void RegisterBundles(BundleCollection bundles) {
            bundles.Add(new ScriptBundle("~/bundles/js").Include(
                    "~/Scripts/logoutHandler.js"
                )
            );

            bundles.Add(new StyleBundle("~/bundles/css").Include(
                    "~/Content/RegisterLogin/registerlogin-page.style.css",
                    "~/Content/NavbarStyle/navbar.style.css",
                    "~/Content/ShoppingCartStyle.css"
                )
            );

            bundles.Add(new StyleBundle("~/bundles/minicart-css").Include(
                    "~/Content/MiniCart/minicart.style.css"
                )
            );

            bundles.Add(new StyleBundle("~/bundles/css-blogpost").Include(
                    "~/Content/BlogPostStyle/blogpost.style.css"
                )
            );
            bundles.Add(new StyleBundle("~/bundles/css-category").Include(
                   "~/Content/CategoryLPage/categoryLPage.style.css"
               )
           );
        }
    }
}