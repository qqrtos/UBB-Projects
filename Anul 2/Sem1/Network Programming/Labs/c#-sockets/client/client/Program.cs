using System;
using System.Net;
using System.Net.Sockets;
using System.Text.Json;
using System.Threading.Tasks;

namespace server {
    class Program {
        static void Main(string[] args) {
            Server server = new Server();
            server.RunServer();
        }
    }
}
