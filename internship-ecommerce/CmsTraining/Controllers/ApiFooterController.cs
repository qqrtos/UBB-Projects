using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Net.Http;
using System.Web;
using System.Web.Http;

namespace CmsTraining.Controllers
{
    public class ApiFooterController : ApiController
    {

        [HttpGet]
        public bool HasSubscribedCookie()
        {
            if (HttpContext.Current.Request.Cookies.AllKeys.Contains("is-subscribed"))
            {
                return true;
            }
            return false;
        }
        [HttpGet]
        public IHttpActionResult SubmitSubscription(string mail)
        {
            if (this.HasSubscribedCookie())
            {
                return Ok();
            }

            HttpCookie subscribedCookie = new HttpCookie("is-subscribed", "true");
            subscribedCookie.Domain = Request.RequestUri.Host;
            subscribedCookie.Path = "/";
            HttpContext.Current.Response.SetCookie(subscribedCookie);

          /*  var uniqueUser = database.Subscribers.FirstOrDefault(s => s.Email == mail);
            if (uniqueUser == null)
            {
                database.Subscribers.Add(new NewsletterSubscriberModel { Email = mail });
            }*/

            return Ok();
        }
    }
}
