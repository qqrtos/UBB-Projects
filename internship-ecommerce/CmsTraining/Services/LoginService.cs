using CmsTraining.Models.ViewModels;
using Mediachase.Commerce.Customers;
using System;
using System.Web;
using System.Web.Http.ModelBinding;
using System.Web.Security;
using System.Web.SessionState;

namespace CmsTraining.Services {
    public class LoginService {
        public LoginService() { }

        public bool IsAuthenticated() {
            return HttpContext.Current.User.Identity.IsAuthenticated;
        }

        public bool RegisterUser(RegisterViewModel registerViewModel, out string errorMessage) {
            try {
                var user = Membership.CreateUser(registerViewModel.Email, registerViewModel.Password, registerViewModel.Email);

                CustomerContact customerContact = CustomerContact.CreateInstance(user);

                customerContact.FirstName = registerViewModel.FirstName;
                customerContact.LastName = registerViewModel.LastName;
                customerContact.Email = registerViewModel.Email;
                customerContact["PhoneNumber"] = registerViewModel.PhoneNumber;
                customerContact["State"] = registerViewModel.SelectedState;
                customerContact["Gender"] = registerViewModel.Gender;

                customerContact.SaveChanges();

                errorMessage = null;
                return true;
            }
            catch (Exception e) {
                errorMessage = e.Message;
                return false;
            }
        }

        public void AuthenticateUser(string email) {
            ///HttpContext.Current.Session["UserData"] = email;
            FormsAuthentication.SetAuthCookie(email, true);
        }

        internal void LogOutUser() {
            HttpContext.Current.User = null;
            FormsAuthentication.SignOut();
        }
    }
}