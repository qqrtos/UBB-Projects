using Mediachase.Commerce;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

namespace CmsTraining.Features.ShoppingCart.Presentation.ViewModels
{
    public class ShoppingCartViewModel
    {
        public string TotalFormatted { get; }

        public string SubTotalFormatted { get; }
        public string ShippingTotalFormatted { get; }

        public int Count { get; }

        public List<ShoppingCartLineItemViewModel> LineItems;
    }
}