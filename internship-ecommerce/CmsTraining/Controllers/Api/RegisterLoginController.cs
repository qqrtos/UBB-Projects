using CmsTraining.Models.CustomEntities;
using CmsTraining.Models.ViewModels;
using CmsTraining.Services;
using EPiServer.ServiceLocation;
using System;
using System.Linq;
using System.Web;
using System.Web.Http;
using System.Web.Mvc;
using System.Web.Security;
using System.Web.Services;

namespace CmsTraining.Controllers.Api
{
    public class RegisterLoginController : ApiController {
        private readonly LoginService _loginService;

        public RegisterLoginController() { //LoginService loginService) {
            //_loginService = loginService;
            _loginService = ServiceLocator.Current.GetInstance<LoginService>();
        }

        [System.Web.Http.HttpGet]
        public bool IsAuthenticated() {
            return _loginService.IsAuthenticated();
        }

        [System.Web.Http.HttpGet]
        public string GetStartPageUrl() {
            return System.Web.HttpContext.Current.Request.Url.GetLeftPart(UriPartial.Authority);
        }

        [System.Web.Http.HttpPost]
        public ValidationModel Register([Bind(Include = "FirstName,LastName,PhoneNumber,Email,Gender,State,Password,ConfirmPassword")]RegisterViewModel registerViewModel) {
            if (ModelState.IsValid) {
                if (_loginService.RegisterUser(registerViewModel, out var errorMessage)) {
                    _loginService.AuthenticateUser(registerViewModel.Email);
                    return new ValidationModel { IsValid = true };
                }
                else {
                    ModelState.AddModelError("", errorMessage);
                    return new ValidationModel { IsValid = false, ErrorMessage = errorMessage };
                }
            }

            var errorList = ModelState.Values.SelectMany(m => m.Errors)
                                 .Select(e => e.ErrorMessage)
                                 .ToList();
            return new ValidationModel { IsValid = false, ErrorMessage = errorList.First() };
        }

        [System.Web.Http.HttpPost]
        public ValidationModel Login([Bind(Include = "Email,Password")] LoginViewModel loginViewModel)
        {
            if (ModelState.IsValid) {
                if (Membership.ValidateUser(loginViewModel.Email, loginViewModel.Password)) {
                    _loginService.AuthenticateUser(loginViewModel.Email);
                    return new ValidationModel { IsValid = true };
                }

                ModelState.AddModelError("", "Invalid email or password");
                return new ValidationModel { IsValid = false, ErrorMessage = "Invalid email or password" };
            }

            var errorList = ModelState.Values.SelectMany(m => m.Errors)
                                 .Select(e => e.ErrorMessage)
                                 .ToList();
            return new ValidationModel { IsValid = false, ErrorMessage = errorList.First() };
        }

        [System.Web.Http.HttpPost]
        public bool LogOut() {
            _loginService.LogOutUser();
            return true;
        }
    }
}
