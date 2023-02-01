#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int socket_desc, client_sock, c, read_size;
  struct sockaddr_in server, client;
  int first_number, second_number, result;
  char client_message[2000];

  // Create socket
  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  // Prepare the sockaddr_in structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8888);

  // Bind
  if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) < 0) {
    perror("bind failed. Error");
    return 1;
  }
  puts("bind done");

  // Listen
  listen(socket_desc, 3);

  // Accept and incoming connection
  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);

  client_sock = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c);
  if (client_sock < 0) {
    perror("accept failed");
    return 1;
  }
  puts("Connection accepted");

  // Receive a message from client
  while ((read_size = recv(client_sock, client_message, 2000, 0)) > 0) {
    first_number = rand() % 100;
    second_number = rand() % 100;
    result = first_number + second_number;
    write(client_sock, &result, sizeof(result));
    write(client_sock, &first_number, sizeof(first_number));
    write(client_sock, &second_number, sizeof(second_number));
    memset(client_message, 0, sizeof(client_message));
  }

  if (read_size == 0) {
    puts("Client disconnected");
    fflush(stdout);
  } else if (read_size == -1) {
    perror("recv failed");
  }

  return 0;
}
