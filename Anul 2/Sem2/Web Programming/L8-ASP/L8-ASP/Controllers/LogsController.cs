using System;
using Microsoft.AspNetCore.Mvc;
using System.Linq;
using L8_ASP.Entities;
using L8_ASP.Models;
using L8_ASP.Services;

namespace L8_ASP.Controllers {
    public class LogsController : Controller {
        private readonly LogsService _logsService;

        public LogsController(LogsService logsService) {
            _logsService = logsService;
        }

        public IActionResult GetAll() {
            var model = new LogArrayViewModel {
                Logs = _logsService.GetAll().ToList()
            };

            return View(model);
        }

        public IActionResult GetAllForUser() {
            var userId = Int32.Parse(Request.Cookies.FirstOrDefault(c => c.Key == "loginCookie").Value);

            var model = new LogArrayViewModel {
                Logs = _logsService.GetAllForUser(userId).ToList()
            };

            return View(model);
        }

        [HttpGet]
        public IActionResult AddLog() {
            return View();
        }

        [HttpPost]
        public IActionResult AddLog(Log log) {
            var userId = Int32.Parse(Request.Cookies.FirstOrDefault(c => c.Key == "loginCookie").Value);
            _logsService.AddLog(log.Type,log.Severity,log.Date, userId, log.Description);
            return Redirect("/Home/Index");
        }

        [HttpGet]
        public IActionResult DeleteLog() {
            return View();
        }

        [HttpPost]
        public IActionResult DeleteLog(int id) {
            var userId = Int32.Parse(Request.Cookies.FirstOrDefault(c => c.Key == "loginCookie").Value);

            try {
                _logsService.DeleteLog(userId, id);
            }
            catch (Exception) {
                return View("Error", new ErrorViewModel());
            }

            return Redirect("/Home/Index");
        }
    }
}
