using System;
using System.Collections.Concurrent;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading.Tasks;

namespace server {
    class Server {
        bool TestParallel { get; set; } = true;

        ConcurrentBag<Socket> Clients { get; set; }

        public Server() {
            Clients = new ConcurrentBag<Socket>();
        }

        private void MessageSent(IAsyncResult result) {
            Socket client = (Socket)result.AsyncState;
            Console.WriteLine("Broadcasted to " + client.RemoteEndPoint.ToString());
            client.EndSend(result);
        }

        private void BroadcastMessage(string message) {
            var encodedMessage = Encoding.ASCII.GetBytes(message);
            foreach (var client in Clients) {
                try {
                    client.BeginSend(
                        encodedMessage,
                        0,
                        encodedMessage.Length,
                        SocketFlags.None,
                        new AsyncCallback(MessageSent),
                        client
                    );
                }
                catch (Exception e) {
                    Console.WriteLine("Broadcasting failed for client " + client.RemoteEndPoint.ToString());
                }
            }
        }

        private void SolveRequest(Socket clientSocket) {
            Console.WriteLine("Server accepted connection from " + clientSocket.RemoteEndPoint.ToString());

            Clients.Add(clientSocket);

            //var message = Console.ReadLine();
            var message = "hiiiiii";
            byte[] data = /*System.Text.*/Encoding.ASCII.GetBytes(message);

            clientSocket.Send(data, data.Length, SocketFlags.None);

            Console.WriteLine("Sent: {0}", message);

            byte[] response = new byte[128];
            clientSocket.Receive(response, 128, SocketFlags.None);
        
            var decodedString = Encoding.UTF8.GetString(response);

            BroadcastMessage(decodedString);

            TestParallel = false;

            Console.WriteLine("Responded: {0}", decodedString);
        }

        public void RunServer() {
            string serverAddress = "0.0.0.0";
            int port = 6767;

            Socket s;
            try {
                s = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
                s.Bind(new IPEndPoint(IPAddress.Parse(serverAddress), port));
                Console.WriteLine("Server bound to {0}:{1}", serverAddress, port.ToString());

                s.Listen(4);
                
                while (true) {
                    Socket clientSocket = s.Accept();

                    //s.EnableBroadcast = true; ??

                    TestParallel = true;
                    Task.Run(() => SolveRequest(clientSocket)); // run in parallel
                    Console.WriteLine("The server ran in parallel: {0}", TestParallel);
                }

                s.Close();
            }
            catch (Exception e){
                Console.WriteLine(e.Message);
            }
        }
    }
}
