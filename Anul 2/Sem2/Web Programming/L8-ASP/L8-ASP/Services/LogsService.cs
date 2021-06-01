using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using L8_ASP.Entities;
using L8_ASP.Repository;

namespace L8_ASP.Services {
    public class LogsService {
        private readonly RepositoryContext _repository;

        public LogsService(RepositoryContext repository) {
            _repository = repository;
        }

        public IEnumerable<Log> GetAll() {
            return _repository.Logs;
        }

        public IEnumerable<Log> GetAllForUser(int userId) {
            return _repository.Logs.Where(l => l.UserId == userId);
        }

        public IEnumerable<Log> GetAllBySeverity(string severity) {
            return _repository.Logs.Where(l => l.Severity == severity);
        }

        public void AddLog(string type, string severity, DateTime date, int userId, string description) {
            var log = new Log(type, severity, date, userId, description);
            _repository.Logs.Add(log);
            _repository.SaveChanges();
        }

        public void DeleteLog(int userId, int logId) {
            var log = _repository.Logs.FirstOrDefault(l => l.Id == logId && l.UserId == userId);
            _repository.Logs.Remove(log);
            _repository.SaveChanges();
        }
    }
}
