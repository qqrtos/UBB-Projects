using CmsTraining.Models.Blocks;
using EPiServer.Web.Mvc;
using System.Web.Mvc;

namespace CmsTraining.Controllers
{
    public class BlogPostBlockController : BlockController<BlogPostBlock>
    {
        public override ActionResult Index(BlogPostBlock currentBlock)
        {
            return PartialView(currentBlock);
        }
    }
}
