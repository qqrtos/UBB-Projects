using System;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;

namespace L8_ASP.Entities {
    public class Log {
        [Key]
        public int Id { get; set; }

        [Required]
        public string  Type { get; set; }

        [Required]
        public string Severity { get; set; }

        [Required]
        public DateTime Date { get; set; }

        [Required]
        public int UserId { get; set; } // Foreign Key to table User

        [Required]
        public string Description { get; set; }

        public Log() { }

        public Log(string type, string severity, DateTime date, int userId, string description) {
            this.Type = type;
            this.Severity = severity;
            this.Date = date;
            this.UserId = userId;
            this.Description = description;
        }
    }
}
