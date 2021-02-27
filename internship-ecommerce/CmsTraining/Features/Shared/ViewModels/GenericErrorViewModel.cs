using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CmsTraining.Features.ShoppingCart.Presentation.ViewModels
{
    public class GenericErrorViewModel
    {
        public bool hasError { get; set; }
        public string errorMessage { get; set; }
    }
}