using CmsTraining.Models.Blocks;
using CmsTraining.Models.Pages;
using EPiServer;
using EPiServer.Core;
using EPiServer.Web;
using EPiServer.Web.Mvc;
using System.Linq;
using System.Web.Mvc;
using CmsTraining.Features.Catalog.Category.Domain;

namespace CmsTraining.Controllers
{
    public class FooterBlockController : BlockController<FooterBlock>
    {
        private readonly IContentLoader _contentLoader;

        public FooterBlockController(IContentLoader contentLoader)
        {
            _contentLoader = contentLoader;
        }
       
        public ActionResult GetFooter()
        {
            var HomePage = _contentLoader.Get<HomePage>(ContentReference.StartPage);
            var Block = HomePage.Footer.Items.FirstOrDefault().GetContent() as FooterBlock;

            return PartialView(Block);
        }
    }
}
