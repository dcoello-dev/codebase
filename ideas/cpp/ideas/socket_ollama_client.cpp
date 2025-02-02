// sandbox_idea: cpp/ideas
// sandbox_name: socket_ollama_client
// sandbox_description:
// sandbox_env: cpp

#include <arpa/inet.h> //inet_addr
#include <iostream>
#include <netdb.h> //hostent
#include <netinet/in.h>
#include <stdio.h>  //printf
#include <string.h> //strlen
#include <string>   //string
#include <sys/socket.h>
#include <unistd.h>

class SimpleClient {
public:
  int connect_c(const std::string &address, int port) {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
      std::cout << "error on socket creation" << std::endl;
      return 1;
    }
    if (inet_addr(address.c_str()) == -1) {
      struct hostent *he;
      struct in_addr **addr_list;

      if ((he = gethostbyname(address.c_str())) == NULL) {
        std::cout << "Failed to resolve hostname\n";
        return 1;
      }

      addr_list = (struct in_addr **)he->h_addr_list;
      for (int i = 0; addr_list[i] != NULL; i++) {
        server.sin_addr = *addr_list[i];
        std::cout << address << " resolved to " << inet_ntoa(*addr_list[i])
                  << std::endl;
        break;
      }
    } else {
      server.sin_addr.s_addr = inet_addr(address.c_str());
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
      perror("connect failed. Error");
      std::cout << "connection failed" << std::endl;
      return 1;
    }

    std::cout << "Connected\n";
    return 0;
  }

  bool send_data(const std::string &data) {
    // Send some data
    if (send(sock, data.c_str(), strlen(data.c_str()), 0) < 0) {
      perror("Send failed : ");
      return false;
    }
    std::cout << "Data send\n";
    return true;
  }

  std::string receive(int size = 100) {
    int n;
    char buffer[size];
    char c = '\0';
    std::string line;
    while ((n = recv(sock, &c, 1, 0)) > 0) {
      if (c == '\r') {
        if (true) {
          line += c;
        }
        // peak for \n
        n = recv(sock, &c, 1, MSG_PEEK);

        if ((n > 0) && (c == '\n')) {
          n = recv(sock, &c, 1, 0);
          if (true) {
            line += c;
          }
          break; // end of line
        }
      }
      line += c;
    }
    return line;
  }

private:
  std::string m_address{};
  int m_port;
  int sock;
  struct sockaddr_in server;
};

int main(void) {
  SimpleClient client{};

  int port = 11434;
  std::string payload{
      "{ \"model\": \"deepseek-r1:7b\", \"prompt\": \"Why is the sky blue?\"}"};
  std::string request{
      "POST /api/generate HTTP/1.1\r\nHost: localhost:11434\r\n"};
  std::string content_lenght{"Content-Length: "};
  std::string content_type{
      "Content-Type: application/x-www-form-urlencoded\r\n"};

  if (client.connect_c("localhost", port) == 0) {
    request.append(content_type);
    request.append(content_lenght);
    request.append(std::to_string(payload.size()));
    request.append("\r\n\r\n");
    request.append(payload);
    request.append("\r\n\r\n");

    std::cout << request << std::endl;

    client.send_data(request);
    while (true) {
      std::cout << client.receive();
    }
  }

  std::cout << "stop" << std::endl;

  return 0;
}
