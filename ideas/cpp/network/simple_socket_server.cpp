// sandbox_idea: cpp/network
// sandbox_name: simple_socket_server
// sandbox_description: socket server
// sandbox_env: cpp

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>
#include <vector>

class SimpleServer {
public:
  SimpleServer(int port) {
    m_stop = false;
    m_socket = socket(AF_INET, SOCK_STREAM, 0);

    m_server_address.sin_family = AF_INET;
    m_server_address.sin_port = htons(port);
    m_server_address.sin_addr.s_addr = INADDR_ANY;
  }

  ~SimpleServer() { close(m_socket); }

  void start() {
    if (bind(m_socket, (struct sockaddr *)&m_server_address,
             sizeof(m_server_address)) == 0) {
      listen(m_socket, 5);
      while (!m_stop) {
        int client_socket = accept(m_socket, nullptr, nullptr);
        clients.push_back(std::thread([client_socket]() {
          char buffer[1024] = {0};
          recv(client_socket, buffer, sizeof(buffer), 0);
          std::cout << "Message from client: " << buffer << std::endl;
          close(client_socket);
        }));
      }
    }
  }

  void stop() {
    m_stop = true;
    for (auto &client : clients) {
      if (client.joinable()) {
        client.join();
      }
    }
  }

private:
  std::vector<std::thread> clients;
  sockaddr_in m_server_address;
  int m_socket;
  bool m_stop;
};

int main(void) {
  std::cout << "hello world!" << std::endl;
  SimpleServer server(8080);
  server.start();
  return 0;
}
