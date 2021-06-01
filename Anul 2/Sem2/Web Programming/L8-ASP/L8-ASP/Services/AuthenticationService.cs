using System;
using System.Linq;
using L8_ASP.Entities;
using L8_ASP.Repository;
using Microsoft.AspNetCore.Http;

namespace L8_ASP.Services {
    public class AuthenticationService {
        private readonly RepositoryContext _repository;

        public AuthenticationService(RepositoryContext repository) {
            _repository = repository;
        }

        public void Register(string username, string password, DateTime birthday) {
            _repository.Users.Add(new User(username, password, birthday));
            _repository.SaveChanges();
        }

        public (string Key, string Value, CookieOptions options)? Authenticate(string username, string password) {
            var user = _repository.Users.FirstOrDefault(u => u.Username == username && u.Password == password);

            if (user == null)
                return null;

            var cookieOptions = new CookieOptions {
                Expires = DateTime.Now.AddHours(8),
                Secure = true
            };

            return ("loginCookie", user.Id.ToString(), cookieOptions);
        }

        public bool IsAuthenticated(HttpContext context) {
            return context.Request.Cookies.ContainsKey("loginCookie");
        }
    }
}
