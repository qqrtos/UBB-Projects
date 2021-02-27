using System;
using System.ComponentModel.DataAnnotations;
using EPiServer;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;

namespace CmsTraining.Models.Blocks
{
    [ContentType(DisplayName = "LinkBlock", GUID = "a6f0ca28-1a18-43e9-aeee-ed6c26a8439b", Description = "Use this for a link")]
    public class LinkBlock : BlockData
    {
        [Display(
           GroupName = SystemTabNames.Content,
           Order = 40)]
        [CultureSpecific]
        public virtual Url LinkUrl { get; set; }

        [Display(
           GroupName = SystemTabNames.Content,
           Order = 50)]
        [CultureSpecific]
        public virtual string UrlName { get; set; }

    }
}