using System;
using System.ComponentModel.DataAnnotations;

namespace L8_ASP.Entities {
    public class User {
        [Key]
        public int Id { get; set; }

        [Required]
        [MinLength(4)]
        public string Username { get; set; }

        [Required]
        [MinLength(5)]
        public string Password { get; set; }

        public DateTime BirthDay { get; set; }

        public User() { }

        public User(string username, string password, DateTime birthday) {
            this.Username = username;
            this.Password = password;
            this.BirthDay = birthday;
        }
    }
}
