using EPiServer.Shell.ObjectEditing;
using System.Collections;
using System.Collections.Generic;

namespace CmsTraining.Static
{
    public class CategoryListSelectionFactory : ISelectionFactory
    {
        public IEnumerable<ISelectItem> GetSelections(ExtendedMetadata metadata)
        {
            return new List<SelectItem>
            {
                new SelectItem { Text = "Animals", Value = "ANIMALS"},
                new SelectItem { Text = "Business", Value = "BUSINESS"},
                new SelectItem { Text = "Design", Value = "DESIGN"},
                new SelectItem { Text = "Guide", Value = "GUIDE"},
                new SelectItem { Text = "Interior", Value = "INTERIOR"},
                new SelectItem { Text = "Motivation", Value = "MOTIVATION"}
            };
        }
    }
}