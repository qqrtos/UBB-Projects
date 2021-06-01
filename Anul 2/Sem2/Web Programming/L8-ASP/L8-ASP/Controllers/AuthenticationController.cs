using Microsoft.AspNetCore.Mvc;
using System;
using L8_ASP.Entities;
using L8_ASP.Models;
using L8_ASP.Services;

namespace L8_ASP.Controllers {
    public class AuthenticationController : Controller {
        private readonly AuthenticationService _authenticationService;
        public AuthenticationController(AuthenticationService authenticationService) {
            _authenticationService = authenticationService;
        }

        [HttpGet]
        public IActionResult Login() {
            return View();
        }

        [HttpPost]
        public IActionResult Login(User user) {
            
            var cookieData = _authenticationService.Authenticate(user.Username, user.Password);

            if (cookieData == null) {
                return View("Error", new ErrorViewModel());
            }

            Response.Cookies.Append(cookieData.Value.Key, cookieData.Value.Value, cookieData.Value.options);

            return Redirect("/Home/Index");
        }

        [HttpGet]
        public IActionResult Logout() {
            Response.Cookies.Delete("loginCookie");

            return Redirect("/");
        }

        [HttpGet]
        public IActionResult Register() {
            return View();
        }

        [HttpPost]
        public IActionResult Register(User user) {
            try {
                _authenticationService.Register(user.Username, user.Password, user.BirthDay);
            }
            catch (Exception) {
                return View("Error", new ErrorViewModel());
            }

            return Redirect("/Authentication/Login");
        }
    }
}
