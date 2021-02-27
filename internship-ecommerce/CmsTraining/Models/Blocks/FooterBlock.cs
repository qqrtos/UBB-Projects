using CmsTraining.Models.CustomEntities;
using DotLiquid.Tags;
using EPiServer.Cms.Shell.UI.ObjectEditing.EditorDescriptors;
using EPiServer.Core;
using EPiServer.DataAbstraction;
using EPiServer.DataAnnotations;
using EPiServer.Shell.ObjectEditing;
using EPiServer.SpecializedProperties;
using FluentNHibernate.Conventions.Inspections;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;

namespace CmsTraining.Models.Blocks {
    [ContentType(DisplayName = "Footer",
        GUID = "f7a5859a-7eb0-4870-a1db-b0000b2efffb",
        Description = "The footer for a page.")]
    public class FooterBlock : BlockData {
        [CultureSpecific]
        [Display(
            Name = "Copyright Text",
            Description = "A text field to input copyright information.",
            GroupName = SystemTabNames.Content,
            Order = 10)]
        public virtual string CopyrightText { get; set; }

        [CultureSpecific]
        [Display(
            Name = "Reference Icons",
            Description = "A list of icons that redirect users.",
            GroupName = SystemTabNames.Content,
            Order = 20)]
        [EditorDescriptor(EditorDescriptorType = typeof(CollectionEditorDescriptor<ReferenceIcon>))]
        public virtual IList<ReferenceIcon> SocialMediaIcons { get; set; }

        /*[CultureSpecific]
        [Display(
            Name = "CategoriesContentArea",
            Description = "A list of categories.",
            GroupName = SystemTabNames.Content,
            Order = 30)]
        //[AvailableContentTypes(Include = new[] { typeof(LinkBlock) })]
        public virtual ContentArea CategoriesContentArea { get; set; }*/

        [CultureSpecific]
        [Display(
            Name = "CategoriesContentArea",
            Description = "A list of categories.",
            GroupName = SystemTabNames.Content,
            Order = 30)]
        public virtual LinkItemCollection CategoryLinks { get; set; }

        [CultureSpecific]
        [Display(
            Name = "InformationContentArea",
            Description = "A list of information.",
            GroupName = SystemTabNames.Content,
            Order = 40)]
        //[AvailableContentTypes(Include = new[] { typeof(LinkBlock) })]
        public virtual ContentArea InformationContentArea { get; set; }

        [CultureSpecific]
        [Display(
            Name = "SubscribeContentArea",
            Description = "A subscription area.",
            GroupName = SystemTabNames.Content,
            Order = 50)]
        public virtual ContentArea SubscribeContentArea { get; set; }


    }
}