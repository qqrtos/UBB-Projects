using System.Configuration;
using L8_ASP.Entities;
using Microsoft.EntityFrameworkCore;

namespace L8_ASP.Repository {
    public class RepositoryContext : DbContext {
        public DbSet<User> Users { get; set; }

        public DbSet<Log> Logs { get; set; }

        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder) =>
            optionsBuilder.UseSqlServer(@"Data Source=LAPTOP-A2LRJ4VG;Initial Catalog=LogsWP;Integrated Security=True");
    }
}
